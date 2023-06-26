#ifndef REFRESHERGROUP_H
#define REFRESHERGROUP_H

#include <QObject>
#include "refresherabstract.h"
class refresherGroup : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherGroup( QObject *parent = nullptr,const QString& argDst = "");
    void refresherMain() override;
    void msgCountInit() override;
private:
    QString dstGroup;
    int msgCount;
    User* currUser;
signals:
    void groupRefreshSignal();
private slots:


};

#endif // REFRESHERGROUP_H
