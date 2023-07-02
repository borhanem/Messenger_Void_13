#include "channelchat.h"
#include "ui_channelchat.h"
#include "msgBaseReceive.h"
#include "msgBaseSend.h"
ChannelChat::ChannelChat(QString chatName, QWidget *parent) :
    QDialog(parent),
    AbstractChat(chatName,AbstractChat::Channel),
    ui(new Ui::ChannelChat),
    controller(new ControllerRefresher(WorkerRefresher::MSGList,User::Channel,0,this->mp_user->getUserName(),chatName,this))

{
    qDebug() << "this is running\n";
    ui->setupUi(this);
    ui->sendResult_lbl->clear();
    ui->send_pbn->setDefault(true);
    ui->channelname_led->setDisabled(true);
    ui->channelname_led->setText(this->m_chat_name);
    this->setWindowTitle(this->m_chat_name);
    qDebug() << " this is still running [1]";

    ui->channel_scroll_area->setWidget(ui->scrollAreaWidgetContents);
    messagesLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(messagesLayout);
    messagesLayout->setAlignment(Qt::AlignTop);
    //    connect(mp_user,&User::SuccessOnSendMessage,this,&ChannelChat::success_on_send_message);
    connect(mp_user,&User::Failure,this,&ChannelChat::failure_on_send_message);
    //    //connect(mp_user,&User::SuccessOnGetMessage,this,&GroupChat::Refresh_handler);
    //    connect(mp_user,&User::FailureOnGetMessage,this,&ChannelChat::failure_on_send_message);
    connect(controller,&ControllerRefresher::msgResultReady,this,&ChannelChat::Refresh_Handler);
    connect(mp_user,&User::SuccessOnSendMessage,this,&ChannelChat::success_on_send_message);
    connect(mp_user,&User::Failure,this,&ChannelChat::failure_on_send_message);

    ////////////////////////////////////////////////////////////////////////
    // sending a experimental message to determine the user is admin or not
    this->mp_user->sendMessage(Message((""),mp_user->getUserName(),this->m_chat_name),User::Channel);
    ////////////////////////////////////////////////////////////////////////

    // making the refresher
//    refresher = new refresherChannel(chatName);
//    refresher->start();
//    connect(refresher,&refresherChannel::channelRefreshSignal,this,&ChannelChat::Refresh_Handler);
    ///////////////////
    this->loadFromFile();
    qDebug() << "this is still running[2]";
    controller->setPreSize(this->m_message_list.size());
    controller->operate();
}

ChannelChat::~ChannelChat()
{
    delete ui;
    delete messagesLayout;
    delete controller;
}

int ChannelChat::loadFromFile()
{
    qDebug() << "ChannelChat::loadFromFile => loadFromFile is running";
    QFile logFile("vdata/MsgData/Channels/"+this->m_chat_name+".dat");
    if(!logFile.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    this->m_message_list.clear();
    QDataStream user_ds(&logFile);
    user_ds.setVersion(QDataStream::Qt_6_5);
    Message *temp = new Message();
    Message* msg;
        while(!logFile.atEnd())
        {
            user_ds >> *temp;
            if(temp->sender()==mp_user->getUserName())
            {
                msg = new msgBaseSend(temp->body(),temp->sender(),temp->receiver(),temp->time(),this);
            }
            else
            {
                msg = new msgBaseReceiver(temp->body(),temp->sender(),temp->receiver(),temp->time(),this);
            }
            this->m_message_list.push_back(msg);
        }
    delete temp;
    logFile.close();
    this->updateList();
    return 0;
}

int ChannelChat::saveToFile()
{
    QDir LogDir;
    if(!LogDir.exists("vdata/MsgData/Channels"))
    {
        LogDir.mkpath("vdata/MsgData/Channels");
    }
    QFile logFile("vdata/MsgData/Channels/"+this->m_chat_name+".dat");
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return -1;
    }
    QDataStream user_ds(&logFile);
    user_ds.setVersion(QDataStream::Qt_6_5);
    //user_ds << this->m_message_list;
    for(auto& i : this->m_message_list)
    {
        user_ds << *i;
    }

    logFile.close();
    return 0;
}

void ChannelChat::updateList()
{
    for(auto& i : this->m_message_list)
    {
        if(!i->isEmpty()){
        if(i->sender() == mp_user->getUserName())
        {
            msgBaseSend* msg = dynamic_cast<msgBaseSend*>(i);
            msg->setFixedSize(500,60);
            messagesLayout->addWidget(msg);
        }
        else{
            msgBaseReceiver* msg = dynamic_cast<msgBaseReceiver*>(i);
            msg->setFixedSize(500,60);
            messagesLayout->addWidget(msg);
        }
        }
    }
}

void ChannelChat::on_send_pbn_clicked()
{
    qDebug("on_send_pbn_clicked from ChannelChat class\n");
    QString body = ui->messagebar_led->text();
    if(body.isEmpty())
    {
        ui->sendResult_lbl->setText("No message to send");
        return;
    }
    QString sender = mp_user->getUserName();
    Message msg(body,sender,m_chat_name);
    mp_user->sendMessage(msg,User::Channel);
    ui->sendResult_lbl->setText("trying to Send Message\n");
}
void ChannelChat::success_on_send_message()
{
    ui->sendResult_lbl->setText("Message Send Successfuly");
    ui->messagebar_led->clear();
}

void ChannelChat::failure_on_send_message(QString Error)
{
    // if current user is not admin
    if(Error == "You are not Admin of This Channel")
    {
        ui->send_pbn->setDisabled(true);
        ui->messagebar_led->setDisabled(true);
        ui->send_pbn->hide();
        ui->messagebar_led->hide();
        return;
    }
    ui->sendResult_lbl->setText(Error);
}

void ChannelChat::Refresh_Handler(QList<Message *> newList)
{
    qDebug() << "ChannelChat::Refresh_Handler called\n";
    this->m_message_list += newList;
    ui->sendResult_lbl->setText("Refreshed Successfully!\n");
    //ui->message_layout.
    this->updateList();
    this->saveToFile();
}



