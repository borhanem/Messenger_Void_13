#ifndef REFRESHERGROUP_H
#define REFRESHERGROUP_H

#include <QObject>
#include "refresherabstract.h"
class refresherGroup : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherGroup(QObject *parent = nullptr);
    void jSonChecker(int argMsgCount);
signals:
    void groupRefreshSignal();
};

#endif // REFRESHERGROUP_H
