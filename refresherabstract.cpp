#include "refresherabstract.h"

refresherAbstract::refresherAbstract(QObject *parent)
{

}

void refresherAbstract::run()
{
    User tempUser(QString("receive"),QString::number(1234),QString("dea1fd09fab4c03974c2b0b2e0e37b59"),QString("vdata/UserInfo/userLog.dat"));
    while(true){
        QThread::sleep(FREEZEDURATION * 2);
        qDebug() <<  QThread::currentThreadId() << ": abstractThread::run\n";
        refresherMain(tempUser);
    }
}

// create map of users chats or groups map<username-groupname-channelname,int msgCount>
