#ifndef MESSAGE_H
#define MESSAGE_H



#include <QDateTime>
#include <QDataStream>
class Message
{
public:
    explicit Message();
    explicit Message(QString txt,QString sender ="void",QString receiver="void",QDateTime time=QDateTime::currentDateTime());
    virtual ~Message();
    friend QDataStream& operator<<(QDataStream &stream,const Message &m);
    friend QDataStream& operator>>(QDataStream &stream,Message &m);
    virtual QString body() const;

    QDateTime time() const;

    QString sender() const;

    QString receiver() const;

protected:
    QString m_body;
    QDateTime m_time;
    QString m_sender;
    QString m_receiver;


};


#endif // MESSAGE_H
