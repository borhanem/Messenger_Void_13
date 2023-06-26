#ifndef REFRESHERCHANNEL_H
#define REFRESHERCHANNEL_H

#include <QObject>
#include "refresherabstract.h"

class refresherChannel : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherChannel(QObject *parent = nullptr,const QString& argDst = "");
    void refresherMain() override;
    void msgCountInit() override;
private:
    QString dstChannel;
    int msgCount;
    User* currUser;

signals:
    void channelRefreshSignal();
private slots:


};

#endif // REFRESHERCHANNEL_H
