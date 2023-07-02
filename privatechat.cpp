#include "privatechat.h"
#include "ui_privatechat.h"
#include "msgBaseReceive.h"
#include "msgBaseSend.h"
PrivateChat::PrivateChat(QString chatName,QWidget *parent) :
    QDialog(parent),
    AbstractChat(chatName,AbstractChat::Private),
    ui(new Ui::PrivateChat),
    controller(new ControllerRefresher(WorkerRefresher::MSGList,User::Private,0,this->mp_user->getUserName(),chatName))
{
    ui->setupUi(this);
    ui->sendResult_lbl->clear();
    ui->send_pbn->setDefault(true);
    ui->groupname_led->setDisabled(true);
    ui->groupname_led->setText(this->m_chat_name);
    this->setWindowTitle(this->m_chat_name);
    ui->group_scroll_area->setWidget(ui->scrollAreaWidgetContents);
    messagesLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(messagesLayout);
    messagesLayout->setAlignment(Qt::AlignTop);
    connect(mp_user,&User::SuccessOnSendMessage,this,&PrivateChat::success_on_send_message);
    connect(mp_user,&User::Failure,this,&PrivateChat::failure_on_send_message);
    //connect(mp_user,&User::SuccessOnGetMessage,this,&GroupChat::Refresh_handler);
    //connect(mp_user,&User::FailureOnGetMessage,this,&GroupChat::failure_on_send_message);
    connect(controller,&ControllerRefresher::msgResultReady,this,&PrivateChat::Refresh_handler);
    this->loadFromFile();
    /* ---show all messages---
    for(auto&i : this->m_message_list)
    {
        ui->message_lstwdgt->addItem(i.body());
    }
    *
    */
    controller->setPreSize(this->m_message_list.size());
    controller->operate();
}

PrivateChat::~PrivateChat()
{
    delete ui;
    delete messagesLayout;
    delete controller;
}

int PrivateChat::saveToFile()
{
    QDir LogDir;
    qDebug() << "GroupChat::saveToFile is  running";
    if(!LogDir.exists("vdata/MsgData/Privates"))
    {
        LogDir.mkpath("vdata/MsgData/Privates");
    }
    QFile logFile("vdata/MsgData/Privates/"+this->m_chat_name+".dat");
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

int PrivateChat::loadFromFile()
{
    QFile logFile("vdata/MsgData/Privates/"+this->m_chat_name+".dat");
    qDebug() << "PrivateChat::loadFromFile is  running";
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

void PrivateChat::updateList()
{
    for(auto& i : this->m_message_list)
    {
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

void PrivateChat::on_send_pbn_clicked()
{
    qDebug("on_send_pbn_clicked from PrivateChat class\n");
    QString body = ui->messagebar_led->text();
    if(body.isEmpty())
    {
        ui->sendResult_lbl->setText("No message to send");
        return;
    }
    QString sender = mp_user->getUserName();
    Message msg(body,sender,this->m_chat_name);
    mp_user->sendMessage(msg,User::Private);
    ui->sendResult_lbl->setText("trying to Send Message\n");
}

void PrivateChat::success_on_send_message()
{
    ui->sendResult_lbl->setText("Message Send Successfuly");
    ui->messagebar_led->clear();
}

void PrivateChat::failure_on_send_message(QString Error)
{
    ui->sendResult_lbl->setText(Error);
}

void PrivateChat::Refresh_handler(QList<Message *> newList)
{
    qDebug() << "GroupChat::Refresh_handler called\n";
    this->m_message_list += newList;
    ui->sendResult_lbl->setText("Refreshed Successfully!\n");
    //ui->message_layout.
    this->updateList();
    this->saveToFile();
}

