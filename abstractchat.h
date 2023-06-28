#ifndef ABSTRACTCHAT_H
#define ABSTRACTCHAT_H

#include "user.h"
#include "QList"
#include "message.h"
class AbstractChat
{
public:
    AbstractChat(QString chatName,User *user=NULL);
    virtual ~AbstractChat();
    virtual int saveToFile() = 0;
    virtual int loadFromFile() = 0;
    virtual QString chatName();
protected:
    QString m_chat_name;
    User* mp_user;
    QList<Message*> m_message_list;

};

#endif // ABSTRACTCHAT_H
