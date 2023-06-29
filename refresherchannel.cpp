#include "refresherchannel.h"

refresherChannel::refresherChannel(QObject *parent,const QString& argDst)
{
    dstChannel = argDst;
    currUser = new User();
    if(currUser->loadFromFile()){
        // file no exist
        qDebug() << "file problem abstract refresher constructor";
    }
    currUser->msgCountChannelReinit(dstChannel);
    msgCountInit();
}


void refresherChannel::refresherMain()
{
    currUser->msgCountChannelReinit(dstChannel);
    int countTemp = currUser->msgCountGetterChannel(dstChannel);
    if(msgCount != countTemp){
        jsonHandle();
        msgCount = countTemp;
    }
}

void refresherChannel::msgCountInit()
{
    msgCount = currUser->msgCountGetterDm(dstChannel);
}

void refresherChannel::jsonHandle()
{
    QList<Message*> messageContent;
    QJsonObject msgContent = currUser->msgContentGetterChannel(dstChannel);
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
    emit channelRefreshSignal(messageContent);
}

