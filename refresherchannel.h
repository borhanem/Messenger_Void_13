#ifndef REFRESHERCHANNEL_H
#define REFRESHERCHANNEL_H

#include <QObject>
#include "refresherabstract.h"

class refresherChannel : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherChannel(QObject *parent = nullptr,const QString& argDst = "");
    explicit refresherChannel(QObject *parent = nullptr,const QString& argDst = "",User* argUser = nullptr);
    void refresherMain(User* argUser) override;
    void msgCountInit() override;
    void jsonHandle() override;
private:
    QString dstChannel;
    int msgCount;
    User* currUser;

signals:
    void channelRefreshSignal(QList<Message*>);
private slots:


};

#endif // REFRESHERCHANNEL_H
