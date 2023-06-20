#ifndef REFRESHERABSTRACT_H
#define REFRESHERABSTRACT_H

#include <QObject>
#include <QThread>
#include "api.h"
#include "user.h"

#define FREEZEDURATION 1

class refresherAbstract : public QThread
{
    Q_OBJECT
public:
    explicit refresherAbstract(QObject *parent = nullptr);
    void run();
    virtual void jSonChecker(int& argMsgCount) = 0;
    virtual int msgCountInit(const QString& responseMsg) = 0;
signals:

private:
    User* currUser;
};

#endif // REFRESHERABSTRACT_H
