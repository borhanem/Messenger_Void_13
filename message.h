#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDateTime>
#include <QDataStream>
class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    explicit Message(QString txt,QString sender ="void",QString receiver="void",QDateTime time=QDateTime::currentDateTime(),QObject *parent = nullptr);

    friend QDataStream& operator<<(QDataStream &stream,const Message &m);
    friend QDataStream& operator>>(QDataStream &stream,Message &m);
    QString body() const;

    QDateTime time() const;

    QString sender() const;

    QString receiver() const;

private:
    QString m_body;
    QDateTime m_time;
    QString m_sender;
    QString m_receiver;
signals:

};

#endif // MESSAGE_H
