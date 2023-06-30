#include "groupchat.h"
#include "ui_groupchat.h"

GroupChat::GroupChat(QString chatName,QWidget *parent) :
    QDialog(parent),
    AbstractChat(chatName,AbstractChat::Group),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);
    ui->sendResult_lbl->clear();
    ui->send_pbn->setDefault(true);
    ui->groupname_led->setDisabled(true);
    ui->groupname_led->setText(this->m_chat_name);
    this->setWindowTitle(this->m_chat_name);
    connect(mp_user,&User::SuccessOnSendMessage,this,&GroupChat::success_on_send_message);
    connect(mp_user,&User::Failure,this,&GroupChat::failure_on_send_message);
    connect(mp_user,&User::SuccessOnGetMessage,this,&GroupChat::Refresh_handler);
    connect(mp_user,&User::FailureOnGetMessage,this,&GroupChat::failure_on_send_message);
    /* ---show all messages---
    for(auto&i : this->m_message_list)
    {
        ui->message_lstwdgt->addItem(i.body());
    }
    */
}


GroupChat::~GroupChat()
{
    delete ui;
}

int GroupChat::saveToFile()
{
    QDir LogDir;
    if(!LogDir.exists("vdata/MsgData/Groups"))
    {
        LogDir.mkpath("vdata/MsgData/Groups");
    }
    QFile logFile("vdata/MsgData/Groups/"+this->m_chat_name+".dat");
    if(!logFile.open(QIODevice::WriteOnly))
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

int GroupChat::loadFromFile()
{
    QFile logFile("vdata/MsgData/Groups/"+this->m_chat_name+".dat");
    if(!logFile.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    QDataStream user_ds(&logFile);
    user_ds.setVersion(QDataStream::Qt_6_5);
    while(!logFile.atEnd())
    {
        Message *temp = new Message(this);
        user_ds >> *temp;
        this->m_message_list.push_back(temp);
    }

    logFile.close();
    return 0;
}

void GroupChat::on_send_pbn_clicked()
{
    qDebug("on_send_pbn_clicked from GroupChat class\n");
    QString body = ui->messagebar_led->text();
    if(body.isEmpty())
    {
        ui->sendResult_lbl->setText("No message to send");
        return;
    }
    QString sender = mp_user->getUserName();
    Message msg(body,sender,m_chat_name);
    mp_user->sendMessage(msg,User::Group);
    ui->sendResult_lbl->setText("trying to Send Message\n");
}

void GroupChat::success_on_send_message()
{
    ui->sendResult_lbl->setText("Message Send Successfuly");
}

void GroupChat::failure_on_send_message(QString Error)
{
    ui->sendResult_lbl->setText(Error);
}


void GroupChat::on_refresh_pbn_clicked()
{
    mp_user->getMsg(this->m_chat_name,User::Group);
    ui->sendResult_lbl->setText("Refreshing");
}

void GroupChat::Refresh_handler(QList<Message *> newList)
{
    this->m_message_list = newList;
    ui->sendResult_lbl->setText("Refreshed Successfully!\n");
}

