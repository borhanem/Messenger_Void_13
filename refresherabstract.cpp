#include "refresherabstract.h"

refresherAbstract::refresherAbstract(QObject *parent)
{

}

void refresherAbstract::run()
{
    int msgCount = 0;
    msgCount = msgCountInit();
    while(true){
        QThread::sleep(FREEZEDURATION);
        jSonChecker(msgCount);
    }
}

int refresherAbstract::msgCountInit()
{

}
