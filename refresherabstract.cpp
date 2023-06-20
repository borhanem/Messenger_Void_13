#include "refresherabstract.h"

refresherAbstract::refresherAbstract(QObject *parent)
{
    currUser = new User();
    if(currUser->loadFromFile()){
        // file no exist
        qDebug() << "file problem refresher constructor";
    }
}

void refresherAbstract::run()
{
    int msgCount = 0;

//    msgCount = msgCountInit();
    while(true){
        QThread::sleep(FREEZEDURATION);
        jSonChecker(msgCount);
    }
}


