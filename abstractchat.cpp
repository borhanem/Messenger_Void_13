#include "abstractchat.h"


AbstractChat::AbstractChat(QString chatName, User *user)
    : m_chat_name(chatName),mp_user(user)
{

}

AbstractChat::~AbstractChat()
{

}
