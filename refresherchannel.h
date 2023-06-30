#ifndef REFRESHERCHANNEL_H
#define REFRESHERCHANNEL_H

#include <QObject>
#include "refresherabstract.h"

class refresherChannel : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherChannel(const QString& argDst = "",QObject *parent = nullptr);
//    explicit refresherChannel(QObject *parent = nullptr,const QString& argDst = "",User* argUser = nullptr);
    void refresherMain() override;
    void msgCountInit() override;
    void jsonHandle() override;
    void userMalloc() override;
private:
    QString dstChannel;
    int msgCount;
    User* currUser;
signals:
    void channelRefreshSignal(QList<Message*>);
private slots:


};

#endif // REFRESHERCHANNEL_H
