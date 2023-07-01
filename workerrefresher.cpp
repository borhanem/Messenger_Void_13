#include "workerrefresher.h"

WorkerRefresher::WorkerRefresher(const RefresherType& rt,const User::ChatType& ct,const QString& chatname,QObject *parent)
    : QObject{parent},
    mp_currUser(new User()),
    mp_timer(new QTimer()),
    m_refresher_type(rt),
    m_chat_type(ct),
    m_chat_name(chatname)
{
    if(mp_currUser->loadFromFile())
    {
        qDebug("WorkerRefresher::WorkerRefresher : Cannot Load User From File\n");
    }
    mp_timer->setInterval(PAUSETIME);
    connect(mp_timer,&QTimer::timeout,this,&WorkerRefresher::sendRefreshRequest);
    connect(mp_currUser,&User::SuccessOnGetMessage,this,&WorkerRefresher::resultReady);
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

void WorkerRefresher::sendRefreshRequest()
{
    qDebug() << "WorkerRefresher::sendRefreshRequest called";
    switch(m_refresher_type)
    {
    case(MSGList):
        mp_currUser->getMsg(m_chat_name,m_chat_type);
        break;
    case(ChatList):
    //  will request the server for ChatList
        break;
    }
}
