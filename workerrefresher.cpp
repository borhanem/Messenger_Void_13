#include "workerrefresher.h"
#include "msgBaseReceive.h"
#include "msgBaseSend.h"
#include "abstractchat.h"
#include "groupchat.h"
#include "channelchat.h"
WorkerRefresher::WorkerRefresher(const RefresherType& rt,const User::ChatType& ct,size_t preSize,const QString& chatname,QObject *parent)
    : QObject{parent},
    mp_currUser(new User()),
    mp_timer(new QTimer()),
    m_refresher_type(rt),
    m_chat_type(ct),
    m_chat_name(chatname),
    m_pre_size(preSize)
{
    if(mp_currUser->loadFromFile())
    {
        qDebug("WorkerRefresher::WorkerRefresher : Cannot Load User From File\n");
    }
    mp_timer->setInterval(PAUSETIME);
    connect(mp_timer,&QTimer::timeout,this,&WorkerRefresher::sendRefreshRequest);
    connect(mp_currUser,&User::SuccessOnGetMessage,this,&WorkerRefresher::handleRespond);
    connect(mp_currUser,&User::SuccessOnGetChatList,this,&WorkerRefresher::handleRespond);
}

WorkerRefresher::~WorkerRefresher()
{

    delete mp_currUser;
    delete mp_timer;
}

void WorkerRefresher::run()
{
    mp_timer->start();
}

void WorkerRefresher::setPreSize(size_t new_size)
{
    this->m_pre_size = new_size;
}

void WorkerRefresher::sendRefreshRequest()
{
    qDebug() << "WorkerRefresher::sendRefreshRequest called";
    switch(m_refresher_type)
    {
    case(MSGList):
        mp_currUser->getMsg(this->m_chat_name,this->m_chat_type);
        break;
    case(ChatList):
        mp_currUser->getChatList(this->m_chat_type);
        break;
    }
}

void WorkerRefresher::handleRespond(QJsonObject Respond,size_t new_size)
{
    if(new_size > this->m_pre_size)
    {
        if(this->m_refresher_type == WorkerRefresher::MSGList)
        {
            this->handleMsgs(Respond,new_size);
        }
        else{
        switch(this->m_chat_type)
        {
        case(User::Private):
            this->handleUsers(Respond,new_size);
            break;
        case(User::Group):
            this->handleGroups(Respond,new_size);
            break;
        case(User::Channel):
            this->handleChannels(Respond,new_size);
            break;
        default:
            qDebug() << " WorkerRefresher::handleRespond => No match Found for Chat Type";
            break;
        }
        }
        this->m_pre_size = new_size;
    }
    else{
        qDebug() << "WorkerRefresher::handleRespond => No difference in number of Objects\n";
    }

}

void WorkerRefresher::handleMsgs(QJsonObject Respond,size_t new_size)
{
    QList<Message*> messageContent;
    for (size_t jsonIter = this->m_pre_size; jsonIter < new_size; ++jsonIter){
        QString blockIter = "block " + QString::number(jsonIter);
        QJsonValue blockVal = Respond.value(blockIter);
        if(blockVal.isObject()){
        QJsonObject blockObj = blockVal.toObject();
        QString text = blockObj.value("body").toString();
        QString time = blockObj.value("date").toString();
        QString sender = blockObj.value("src").toString();
        QString receiver = blockObj.value("dst").toString();
        qDebug() << blockIter << " body: " << text << " -time: " << time << "-sender: "<<sender <<"-reciver: " << receiver;
        Message* tempMsg;
        if(sender == this->mp_currUser->getUserName() )
        {
            tempMsg = new msgBaseSend(text,sender,receiver,QDateTime::fromString(time,"yyyy-MM-dd HH:mm:ss"));
        }
        else{
            tempMsg = new msgBaseReceiver(text,sender,receiver,QDateTime::fromString(time,"yyyy-MM-dd HH:mm:ss"));
        }
        messageContent.push_back(tempMsg);
        }
        else
        {
        qDebug() << "WorkerRefresher::handleMsgs : blockVal is not Object\n";
        }
    }
    emit msgResultReady(messageContent);
}

void WorkerRefresher::handleGroups(QJsonObject Respond,size_t new_size)
{
    QList<AbstractChat*> ChatList;
    for (size_t jsonIter = this->m_pre_size; jsonIter < new_size; ++jsonIter){
        QString blockIter = "block " + QString::number(jsonIter);
        QJsonValue blockVal = Respond.value(blockIter);
        if(blockVal.isObject()){
        QJsonObject blockObj = blockVal.toObject();
        QString ChatName = blockObj.value("group_name").toString();
        qDebug() << blockIter << " ChatName: " << ChatName;
        AbstractChat* tempMsg = new GroupChat(ChatName);
        ChatList.push_back(tempMsg);
        }
        else
        {
        qDebug() << " WorkerRefresher::handleGroups : blockVal is not Object\n";
        }
    }
    emit chatResultReady(ChatList);
}

void WorkerRefresher::handleChannels(QJsonObject Respond,size_t new_size)
{
    QList<AbstractChat*> ChatList;
    for (size_t jsonIter = this->m_pre_size; jsonIter < new_size; ++jsonIter){
        QString blockIter = "block " + QString::number(jsonIter);
        QJsonValue blockVal = Respond.value(blockIter);
        if(blockVal.isObject()){
        QJsonObject blockObj = blockVal.toObject();
        QString ChatName = blockObj.value("channel_name").toString();
        qDebug() << blockIter << " ChatName: " << ChatName;
        AbstractChat* tempMsg = new ChannelChat(ChatName);
        ChatList.push_back(tempMsg);
        }
        else
        {
        qDebug() << " WorkerRefresher::handleChannels : blockVal is not Object\n";
        }
    }
    emit chatResultReady(ChatList);
}

void WorkerRefresher::handleUsers(QJsonObject Respond,size_t new_size)
{

}
