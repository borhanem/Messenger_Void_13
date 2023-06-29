#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
#include "api.h"
#include <QDataStream>
#include <QFile>
#include <QDir>
#include "message.h"
class User : public QObject
{
    Q_OBJECT
public:
    enum ChatType
    {
        Private,
        Group,
        Channel
    };
    User();
    explicit User(QString userName,QString passWord,QString token = "",QString userPath="userLog.dat",QObject* parent = nullptr);
    void Register();
    void login();
    void logOut();
    void createNewChat(const QString& chatName,const ChatType& type)const;
    void joinChat(const QString& chatName,const ChatType& type)const;
    void sendMessage(const Message& msg,const ChatType& type);
    void getMsgDM(const QString &dst); // new entry
    void getMsgGroup(const QString &dst); // new entry
    void getMsgChannel(const QString &dst); // new entry
    int loadFromFile();
    int saveToFile();
    QString getUserName();
    QString getPassword();
    QString getToken();
    void SetUserName(const QString& new_user_name);
    void SetPassWord(const QString& new_pass_word);
    friend QDataStream& operator<<(QDataStream &stream,const User &u);
    friend QDataStream& operator>>(QDataStream &stream,User &u);
private:
    const QString m_UserLogFilePath;
    QString m_username;
    QString m_password;
    QString m_token;
    API* m_server;

    //void writeToFile(char* filePath);
    //void readFromFile(char* filePath);
private slots:
    void server_handler_on_Register();
    void server_handler_on_SendMessage();
    void server_handler_on_Login(QString token);
    void server_handler_on_Logout();
    void server_handler_on_createNewChat();
    void server_handler_on_joinChat();
    void server_handler_on_failure(QString Error);
signals:
    void Success();
    void SuccessOnLogout();
    void SuccessOnSendMessage();
    void Failure(QString Error);
    void FailureOnLogout(QString Error);
};

#endif // USER_H
