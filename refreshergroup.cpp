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
    currUser->msgCountGroupReinit(dstGroup);
    int countTemp = currUser->msgCountGetterGroup(dstGroup);
    if(msgCount != countTemp){
        emit groupRefreshSignal();
        msgCount = countTemp;
    }
}

void refresherGroup::msgCountInit()
{
    msgCount = currUser->msgCountGetterDm(dstGroup);
}

