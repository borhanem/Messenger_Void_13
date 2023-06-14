#include "message.h"

Message::Message(QObject *parent)
    : QObject{parent}
{

}

Message::Message():m_text("I am the Danger"),m_time("1/1/1 04:20"),m_sender("Mahta")
{

}

Message::Message(QString txt, QString time, QString sender) : m_text(txt),m_time(time),m_sender(sender)
{

}
