#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
class User : public QObject
{
    Q_OBJECT
public:
    User();
    explicit User(QString userName,QString passWord,QString token = "",QObject* parent = nullptr);
    void Register(char* filePath);
    void login(char* filePath);
    void logOut(char* filePath);
    void loadFromFile(char* filePath);
    QString getUserName();
    QString getPassword();
    QString getToken();

private:
    char m_username[200];
    char m_password[200];
    char m_token[200];
    void writeToFile(char* filePath);
    void readFromFile(char* filePath);

signals:

};

#endif // USER_H
