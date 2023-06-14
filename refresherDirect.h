#ifndef REFRESHERDIRECT_H
#define REFRESHERDIRECT_H

#include <QObject>
#include "refresherabstract.h"

class refresherDirect : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherDirect(QObject *parent = nullptr);
    void jSonChecker(int argMsgCount);
signals:
    void directRefreshSignal();
};

#endif // REFRESHERDIRECT_H
