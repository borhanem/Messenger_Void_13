#ifndef REFRESHERGROUPLIST_H
#define REFRESHERGROUPLIST_H

#include <QObject>
#include "refresherabstract.h"
class refresherGroupList : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherGroupList(QObject *parent = nullptr);
    void refresherMain() override;
    void jsonHandle() override;
    void userMalloc() override;
    void groupCountInit();
private:
    int groupCount;
    User* currUser;
signals:
    newGroupFound(QList<QString>);
};

#endif // REFRESHERGROUPLIST_H
