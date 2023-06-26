#include "refresherabstract.h"

refresherAbstract::refresherAbstract(QObject *parent)
{

}

void refresherAbstract::run()
{

    while(true){
        QThread::sleep(FREEZEDURATION);
        refresherMain();
    }
}





