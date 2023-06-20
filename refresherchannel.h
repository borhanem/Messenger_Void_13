#ifndef REFRESHERCHANNEL_H
#define REFRESHERCHANNEL_H

#include <QObject>
#include "refresherabstract.h"
class refresherChannel : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherChannel(QObject *parent = nullptr);
    void jSonChecker(int& argMsgCount);
signals:
    void channelRefreshChecker();
};

#endif // REFRESHERCHANNEL_H
