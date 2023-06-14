#include "refresherabstract.h"

refresherAbstract::refresherAbstract(QObject *parent)
{

}

void refresherAbstract::run()
{
    int msgCount = 0;
    while(true){
        QThread::sleep(FREEZEDURATION);
        jSonChecker(msgCount);
    }
}
