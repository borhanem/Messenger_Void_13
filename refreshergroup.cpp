#include "refreshergroup.h"

refresherGroup::refresherGroup(QObject *parent,const QString& argDst)
{
    dstGroup = argDst;
    currUser = new User();
    if(currUser->loadFromFile()){
        // file no exist
        qDebug() << "file problem abstract refresher constructor";
    }
    currUser->msgCountGroupReinit(dstGroup);
    msgCountInit();
}

void refresherGroup::refresherMain()
{
    qDebug() <<  QThread::currentThreadId() << ": groupThread::refresherMain\n";
    currUser->msgCountGroupReinit(dstGroup);
    int countTemp = currUser->msgCountGetterGroup(dstGroup);
    if(msgCount != countTemp){
        jsonHandle();
        msgCount = countTemp;
    }
}

void refresherGroup::msgCountInit()
{
    msgCount = currUser->msgCountGetterDm(dstGroup);
}

void refresherGroup::jsonHandle()
{
    QList<Message*> messageContent;
    QJsonObject msgContent = currUser->msgContentGetterGroup(dstGroup);
    for (int jsonIter = 0; jsonIter < msgCount; ++jsonIter){
        QString blockIter = "block " + QString::number(jsonIter);
        QJsonValue blockVal = msgContent.value(blockIter);
        if(blockVal.isObject()){
            QJsonObject blockObj = blockVal.toObject();
            QString text = blockObj.value("body").toString();
            QString time = blockObj.value("date").toString();
            QString sender = blockObj.value("src").toString();
            Message* tempMsg = new Message(text,time,sender);
            messageContent.append(tempMsg);
        }
    }
    emit groupRefreshSignal(messageContent);
    qDebug() <<  QThread::currentThreadId() << ": groupThread::jsonHandle\n";
}

