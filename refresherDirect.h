#ifndef REFRESHERDIRECT_H
#define REFRESHERDIRECT_H

#include <QObject>
#include "refresherabstract.h"

class refresherDirect : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherDirect(QObject *parent = nullptr);
    void jSonChecker(int& argMsgCount);
    int msgCountInit(const QString& responseMsg);
signals:
    void DMRefreshSignal();
};


#endif // REFRESHERDIRECT_H
