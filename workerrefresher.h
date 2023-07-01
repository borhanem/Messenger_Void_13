#ifndef WORKERREFRESHER_H
#define WORKERREFRESHER_H

#include <QObject>
#include "user.h"
#include <QTimer>

#define PAUSETIME 2000

class WorkerRefresher : public QObject
{
    Q_OBJECT
public:
    enum RefresherType{
        MSGList,ChatList
    };
    explicit WorkerRefresher(const RefresherType& rt,const User::ChatType& ct,const QString& chatname="",QObject *parent = nullptr);
    ~WorkerRefresher();
    void run();
private slots:
    void sendRefreshRequest();
signals:
    void resultReady(QList<Message*>);
private:
    User* mp_currUser;
    QTimer* mp_timer;
    const RefresherType m_refresher_type;
    const User::ChatType m_chat_type;
    QString m_chat_name;
};

#endif // WORKERREFRESHER_H
