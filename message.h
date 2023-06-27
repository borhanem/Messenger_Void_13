#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "user.h"
#include <QDataStream>
class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    explicit Message(QString txt,QString time,QString sender ="void",QString receiver="void",QObject *parent = nullptr);
    friend QDataStream& operator<<(QDataStream &stream,const Message &m);
    friend QDataStream& operator>>(QDataStream &stream,Message &m);
private:
    QString m_body;
    QString m_time;
    QString m_sender;
    QString m_receiver;
signals:

};

#endif // MESSAGE_H
