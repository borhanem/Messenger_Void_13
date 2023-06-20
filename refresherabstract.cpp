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
<<<<<<< HEAD
    msgCount = msgCountInit();
=======
//    msgCount = msgCountInit();
>>>>>>> b4fcbc2ff6a80bfd461b9bf5c48b9a0ea95ee8b5
    while(true){
        QThread::sleep(FREEZEDURATION);
        jSonChecker(msgCount);
    }
}


