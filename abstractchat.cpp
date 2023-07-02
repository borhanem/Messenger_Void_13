#include "abstractchat.h"


AbstractChat::AbstractChat(QString chatName,const ChatType& ct)
    : m_chat_name(chatName),mp_user(new User()),m_chat_type(ct)
{
    mp_user->loadFromFile();
    qDebug("AbstractChat Constructor\n");
}

AbstractChat::~AbstractChat()
{
    qDebug("AbstractChat Destructor\n");
    delete mp_user;
    for(auto& i : this->m_message_list)
    {
        delete i;
    }

}

QString AbstractChat::chatName()const
{
    return m_chat_name;
}

AbstractChat::ChatType AbstractChat::chatType() const
{
    return m_chat_type;
}
