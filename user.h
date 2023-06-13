#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString userName,QString passWord,QString token = "",QObject* parent = nullptr);
    void signUp(char* filePath);
    void login(char* filePath);
    void logOut(char* filePath);
private:
    QString m_username;
    QString m_password;
    QString m_token;
    void writeToFile(char* filePath);
    void readFromFile(char* filePath);

signals:

};

#endif // USER_H
