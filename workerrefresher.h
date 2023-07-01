#ifndef WORKERREFRESHER_H
#define WORKERREFRESHER_H

#include <QObject>
#include "user.h"
#include <QTimer>
#include "abstractchat.h"
#define PAUSETIME 2000

class WorkerRefresher : public QObject
{
    Q_OBJECT
public:
    enum RefresherType{
        MSGList,ChatList
    };
    explicit WorkerRefresher(const RefresherType& rt,const User::ChatType& ct,size_t preSize=0,const QString& chatname="",QObject *parent = nullptr);
    ~WorkerRefresher();
    void run();
    void setPreSize(size_t new_size);
private slots:
    void sendRefreshRequest();
    void handleRespond(QJsonObject Respond, size_t);
signals:
    void msgResultReady(QList<Message*>);
    void chatResultReady(QList<AbstractChat*>);
private:
    User* mp_currUser;
    QTimer* mp_timer;
    const RefresherType m_refresher_type;
    const User::ChatType m_chat_type;
    QString m_chat_name;
    size_t m_pre_size;
    void handleMsgs(QJsonObject, size_t new_size);
    void handleGroups(QJsonObject Respond, size_t new_size);
    void handleChannels(QJsonObject Respond,size_t new_size);
    void handleUsers(QJsonObject Respond, size_t new_size);
};

#endif // WORKERREFRESHER_H
