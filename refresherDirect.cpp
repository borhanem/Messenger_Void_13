#include "refresherDirect.h"

refresherDirect::refresherDirect(QObject *parent,const QString& argDst)
{
    dstDirect = argDst;
    currUser = new User();
    if(currUser->loadFromFile()){
        // file no exist
        qDebug() << "file problem abstract refresher constructor";
    }
    currUser->msgCountGroupReinit(dstDirect);
    msgCountInit();
}

void refresherDirect::refresherMain()
{
    currUser->msgCountGroupReinit(dstDirect);
    int countTemp = currUser->msgCountGetterDm(dstDirect);
    if(msgCount != countTemp){
        jsonHandle();
        msgCount = countTemp;
    }
}

void refresherDirect::msgCountInit()
{
    msgCount = currUser->msgCountGetterDm(dstDirect);
}

void refresherDirect::jsonHandle()
{
    QList<Message*> messageContent;
    QJsonObject msgContent = currUser->msgContentGetterDm(dstDirect);
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
    emit directRefreshSignal(messageContent);

}


