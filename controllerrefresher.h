#ifndef CONTROLLERREFRESHER_H
#define CONTROLLERREFRESHER_H

#include <QObject>
#include <QThread>
#include "workerrefresher.h"
class ControllerRefresher : public QObject
{
    Q_OBJECT
public:
    explicit ControllerRefresher(const WorkerRefresher::RefresherType &refType,const User::ChatType& chatType,const size_t& preSize=0,const QString& CurrUserName = "",const QString& chatName="",QObject *parent = nullptr);
    ~ControllerRefresher();
    void setPreSize(size_t new_pre_size);
    void operate();
private:
    QThread m_workerThread;
    WorkerRefresher* mp_worker;
    const WorkerRefresher::RefresherType m_refresher_type;
    const User::ChatType m_chat_type;
    const QString m_curr_username;
    void handleGroups(QJsonObject Respond, size_t new_size, size_t pre_size);
    void handleChannels(QJsonObject Respond, size_t new_size, size_t pre_size);
    void handleUsers(QJsonObject Respond, size_t new_size, size_t pre_size);
private slots:
    void HandleNewChats(QJsonObject Respond, size_t,size_t);
    void handleNewMsg(QJsonObject Respond, size_t,size_t);
signals:
    void msgResultReady(QList<Message*>);
    void chatResultReady(QList<AbstractChat*>);

};

#endif // CONTROLLERREFRESHER_H
