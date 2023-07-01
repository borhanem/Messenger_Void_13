#ifndef REFRESHERCHANNELLIST_H
#define REFRESHERCHANNELLIST_H

#include <QObject>
#include "refresherabstract.h"
class refresherChannelList : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherChannelList(QObject *parent = nullptr);
    void refresherMain() override;
    void jsonHandle() override;
    void userMalloc() override;
    void channelCountInit();
public:
    int channelCount;
    User* currUser;
signals:
    void newChannelFound(QList<QString>);
};

#endif // REFRESHERCHANNELLIST_H
