#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString userName,QString passWord,QString token = "",QObject* parent = nullptr);

private:
    QString m_username;
    QString m_password;
    QString m_token;

signals:

};

#endif // USER_H
