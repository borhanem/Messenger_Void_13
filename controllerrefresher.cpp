#include "controllerrefresher.h"
#include "msgBaseReceive.h"
#include "msgBaseSend.h"
#include "privatechat.h"
#include "GroupChat.h"
#include "channelchat.h"
ControllerRefresher::ControllerRefresher(const WorkerRefresher::RefresherType &refType, const User::ChatType& chatType, const size_t &preSize,const QString& CurrUserName, const QString &chatName, QObject *parent)
    : QObject{parent},
    mp_worker(new WorkerRefresher(refType,chatType,preSize,chatName)),
    m_refresher_type(refType),
    m_chat_type(chatType),
    m_curr_username(CurrUserName)
{
    mp_worker->moveToThread(&m_workerThread);
    connect(&m_workerThread,&QThread::started,mp_worker,&WorkerRefresher::run);
//    connect(&m_workerThread,&QThread::finished,mp_worker,&WorkerRefresher::deleteLater);
    connect(mp_worker,&WorkerRefresher::NewChats,this,&ControllerRefresher::HandleNewChats);
    connect(mp_worker,&WorkerRefresher::NewMessages,this,&ControllerRefresher::handleNewMsg);
//    m_workerThread.start();
}

ControllerRefresher::~ControllerRefresher()
{
    m_workerThread.quit();
    m_workerThread.wait();
    delete mp_worker;
}

void ControllerRefresher::setPreSize(size_t new_pre_size)
{
    this->mp_worker->setPreSize(new_pre_size);
}

void ControllerRefresher::operate()
{
    this->m_workerThread.start();
}

void ControllerRefresher::handleGroups(QJsonObject Respond, size_t new_size ,size_t pre_size)
{
    QList<AbstractChat*> ChatList;
    for (size_t jsonIter = pre_size; jsonIter < new_size; ++jsonIter){
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

void ControllerRefresher::handleChannels(QJsonObject Respond, size_t new_size,size_t pre_size)
{
    QList<AbstractChat*> ChatList;
    for (size_t jsonIter = pre_size; jsonIter < new_size; ++jsonIter){
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

void ControllerRefresher::handleUsers(QJsonObject Respond, size_t new_size,size_t pre_size)
{
    QList<AbstractChat*> ChatList;
    for (size_t jsonIter = pre_size; jsonIter < new_size; ++jsonIter){
        QString blockIter = "block " + QString::number(jsonIter);
        QJsonValue blockVal = Respond.value(blockIter);
        if(blockVal.isObject()){
            QJsonObject blockObj = blockVal.toObject();
            QString ChatName = blockObj.value("src").toString();
            qDebug() << blockIter << " ChatName: " << ChatName;
            AbstractChat* tempMsg = new PrivateChat(ChatName);
            ChatList.push_back(tempMsg);
        }
        else
        {
            qDebug() << " WorkerRefresher::handleChannels : blockVal is not Object\n";
        }
    }
    emit chatResultReady(ChatList);
}

void ControllerRefresher::HandleNewChats(QJsonObject Respond, size_t new_size,size_t pre_size )
{
            switch(this->m_chat_type)
            {
            case(User::Private):
                this->handleUsers(Respond,new_size,pre_size);
                break;
            case(User::Group):
                this->handleGroups(Respond,new_size,pre_size);
                break;
            case(User::Channel):
                this->handleChannels(Respond,new_size,pre_size);
                break;
            default:
                qDebug() << " WorkerRefresher::handleRespond => No match Found for Chat Type";
                break;
            }
}

void ControllerRefresher::handleNewMsg(QJsonObject Respond, size_t new_size, size_t pre_size)
{
    QList<Message*> messageContent;
    for (size_t jsonIter =pre_size; jsonIter < new_size; ++jsonIter){
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
            if(sender == this->m_curr_username )
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
