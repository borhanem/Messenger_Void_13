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

refresherDirect::refresherDirect(const QString &argDst, User *argUser,QObject *parent)
{
    dstDirect = argDst;
    currUser = argUser;
    currUser->msgCountDmReinit(dstDirect);
    msgCountInit();
}

void refresherDirect::refresherMain()
{
//    User tempUser(QString("receive"),QString::number(1234),QString("dea1fd09fab4c03974c2b0b2e0e37b59"),QString("vdata/UserInfo/userLog.dat"));

    qDebug() <<  QThread::currentThreadId() << ": directthread::refresher main\n";
//    tempUser->msgCountDmReinit(dstDirect);
    currUser->msgCountDmReinit(dstDirect);
//    msgCountInit();
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

void refresherDirect::testInit(User &argUser)
{
    msgCount = argUser.msgCountGetterDm(dstDirect);
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
    qDebug() <<  QThread::currentThreadId() << ": directThread::jsonHandle\n";
    emit directRefreshSignal(messageContent);

}


