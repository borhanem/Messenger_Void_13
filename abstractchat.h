#ifndef ABSTRACTCHAT_H
#define ABSTRACTCHAT_H

#include "user.h"
#include "QList"
#include "message.h"
class AbstractChat
{

public:
    enum ChatType{
        Private,
        Group,
        Channel
    };
    AbstractChat(QString chatName,const ChatType& ct);
    virtual ~AbstractChat();
    virtual int saveToFile() = 0;
    virtual int loadFromFile() = 0;
    virtual QString chatName() const;
    virtual ChatType chatType() const;
protected:
    QString m_chat_name;
    User* mp_user;
    QList<Message*> m_message_list;
    ChatType m_chat_type;
};

#endif // ABSTRACTCHAT_H
