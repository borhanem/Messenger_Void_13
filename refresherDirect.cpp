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
        emit directRefreshSignal();
        msgCount = countTemp;
    }
}

void refresherDirect::msgCountInit()
{
    msgCount = currUser->msgCountGetterDm(dstDirect);
}


