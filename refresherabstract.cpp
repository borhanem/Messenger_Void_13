#include "refresherabstract.h"
#include <QCoreApplication>
refresherAbstract::refresherAbstract(QObject *parent)
{

}

void refresherAbstract::run()
{
    userMalloc();
    while(true){
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
//        qDebug() <<  QThread::currentThreadId() << ": abstractThread::run\n";
        refresherMain();
    }
}

// create map of users chats or groups map<username-groupname-channelname,int msgCount>
