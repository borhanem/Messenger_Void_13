#include "refresherabstract.h"

refresherAbstract::refresherAbstract(QObject *parent)
{

}

void refresherAbstract::run()
{
    while(true){
        QThread::sleep(FREEZEDURATION * 2);
        qDebug() <<  QThread::currentThreadId() << ": abstractThread::run\n";
        refresherMain();
    }
}

// create map of users chats or groups map<username-groupname-channelname,int msgCount>
