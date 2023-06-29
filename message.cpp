#include "message.h"

Message::Message(QObject *parent)
    : QObject{parent},m_body("I am the Danger"),m_time(QDateTime::currentDateTime()),m_sender("void"),m_receiver("void")
{

}

Message::Message(QString txt, QString sender, QString receiver, QDateTime time, QObject *parent)
    : QObject{parent},m_body(txt),m_time(time),m_sender(sender),m_receiver(receiver)
{

}

QString Message::body() const
{
    return m_body;
}

QDateTime Message::time() const
{
    return m_time;
}

QString Message::sender() const
{
    return m_sender;
}

QString Message::receiver() const
{
    return m_receiver;
}
QDataStream& operator<<(QDataStream &stream,const Message &m)
{
    stream << m.m_body;
    stream << m.m_time;
    stream << m.m_sender;
    stream << m.m_receiver;
    return stream;
}
QDataStream& operator>>(QDataStream &stream,Message &m)
{
    stream >> m.m_body;
    stream >> m.m_time;
    stream >> m.m_sender;
    stream >> m.m_receiver;
    return stream;
}
