#ifndef REFRESHERDIRECTLIST_H
#define REFRESHERDIRECTLIST_H

#include <QObject>
#include "refresherabstract.h"
class refresherDirectList : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherDirectList(QObject *parent = nullptr);
    void refresherMain() override;
    void jsonHandle() override;
    void userMalloc() override;
    void contactCountInit();
private:
    int userCount;
    User* currUser;
signals:
    void newUserFound(QList<QString>);
};

#endif // REFRESHERDIRECTLIST_H
