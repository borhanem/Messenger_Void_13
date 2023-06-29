#include "refresherabstract.h"
#include <QCoreApplication>
refresherAbstract::refresherAbstract(QObject *parent)
{

}

void refresherAbstract::run()
{
    User* tempUser = new User(QString("receive"),QString::number(1234),QString("dea1fd09fab4c03974c2b0b2e0e37b59"),QString("vdata/UserInfo/userLog.dat"));
    while(true){
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qDebug() <<  QThread::currentThreadId() << ": abstractThread::run\n";
        refresherMain(tempUser);
    }
}

// create map of users chats or groups map<username-groupname-channelname,int msgCount>
