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
        emit channelRefreshSignal();
        msgCount = countTemp;
    }
}

void refresherChannel::msgCountInit()
{
    msgCount = currUser->msgCountGetterDm(dstChannel);
}

