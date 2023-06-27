#include "message.h"

Message::Message(QObject *parent)
    : QObject{parent},m_body("I am the Danger"),m_time("1/1/1 04:20"),m_sender("void"),m_receiver("void")
{

}

Message::Message(QString txt, QString time, QString sender, QString receiver, QObject *parent)
    : QObject{parent},m_body(txt),m_time(time),m_sender(sender),m_receiver(receiver)
{

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
