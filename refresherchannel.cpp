#include "refresherchannel.h"

refresherChannel::refresherChannel(QObject *parent,const QString& argDst)
{
    dstChannel = argDst;
    currUser = new User();
    if(currUser->loadFromFile()){
        // file no exist
        qDebug() << "file problem abstract refresher constructor";
    }
    currUser->allMsgCountsReInit(dstChannel);
    msgCountInit();
}


void refresherChannel::refresherMain()
{
    int countTemp = currUser->msgCountGetterChannel();
    if(msgCount != countTemp){
        emit channelRefreshSignal();
        msgCount = countTemp;
    }
}

void refresherChannel::msgCountInit()
{
    msgCount = currUser->msgCountGetterDm();
}

