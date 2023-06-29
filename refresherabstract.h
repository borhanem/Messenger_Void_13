#ifndef REFRESHERABSTRACT_H
#define REFRESHERABSTRACT_H

#include <QObject>
#include <QThread>
#include "api.h"
#include "user.h"
#include "message.h"
#define FREEZEDURATION 1

class refresherAbstract : public QThread
{
    Q_OBJECT
public:
    explicit refresherAbstract(QObject *parent = nullptr);
    void run();

    virtual void refresherMain() = 0;
    virtual void msgCountInit() = 0;
    virtual void jsonHandle() = 0;
signals:

private slots:
signals:

};

#endif // REFRESHERABSTRACT_H
