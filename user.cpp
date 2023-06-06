#include "user.h"


User::User(QString userName, QString passWord, QString token, QObject *parent)
    : QObject{parent},m_username(userName),m_password(passWord),m_token(token)
{

}
