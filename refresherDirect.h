#ifndef REFRESHERDIRECT_H
#define REFRESHERDIRECT_H

#include <QObject>
#include "refresherabstract.h"

class refresherDirect : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherDirect(QObject *parent = nullptr,const QString& argDst = "");
    void refresherMain() override;
    void msgCountInit() override;
private:
    QString dstDirect;
    int msgCount;
    User* currUser;
signals:
    void directRefreshSignal();
private slots:


};


#endif // REFRESHERDIRECT_H
