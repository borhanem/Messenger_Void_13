#include "abstractchat.h"


AbstractChat::AbstractChat(QString chatName,const ChatType& ct, User *user)
    : m_chat_name(chatName),mp_user(user),m_chat_type(ct)
{
    qDebug("AbstractChat Constructor\n");
}

AbstractChat::~AbstractChat()
{
    qDebug("AbstractChat Destructor\n");
}

QString AbstractChat::chatName()const
{
    return m_chat_name;
}

AbstractChat::ChatType AbstractChat::chatType() const
{
    return m_chat_type;
}
