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
    void getMsg(const QString &dst,const ChatType& type); // new entry
    int loadFromFile();
    int saveToFile();
    QString getUserName();
    QString getPassword();
    QString getToken();
    void SetUserName(const QString& new_user_name);
    void SetPassWord(const QString& new_pass_word);
    friend QDataStream& operator<<(QDataStream &stream,const User &u);
    friend QDataStream& operator>>(QDataStream &stream,User &u);
    int msgCountGetterDm(const QString &dst);
    int msgCountGetterChannel(const QString &dst);
    int msgCountGetterGroup(const QString &dst);
    int userCountGetter();
    int channelCountGetter();
    int groupCountGetter();
    QVector<QString> userListGetter();
    QVector<QString> channelListGetter();
    QVector<QString> groupListGetter();
    QJsonObject msgContentGetterDm(const QString &dst);
    QJsonObject msgContentGetterChannel(const QString &dst);
    QJsonObject msgContentGetterGroup(const QString &dst);
    void msgCountDmReinit(const QString &dst);
    void msgCountGroupReinit(const QString &dst); // check this for group
    void msgCountChannelReinit(const QString &dst);
    void userListReinit();
    void channelListReinit();
    void groupListReinit();
private:
    const QString m_UserLogFilePath;
    QString m_username;
    QString m_password;
    QString m_token;
    API* m_server;
    QMap<QString,QPair<int,QJsonObject>> directData; // stores msg count and message JSon obj
    QMap<QString,QPair<int,QJsonObject>> groupData;
    QMap<QString,QPair<int,QJsonObject>> channelData;
    QVector<QString> userList;
    QVector<QString> channelList;
    QVector<QString> groupList;
    int userCount;
    int channelCount;
    int groupCount;
    //void writeToFile(char* filePath);
    //void readFromFile(char* filePath);
private slots:
    void msgCountChannelSlot(const QString& argMsgCount,QJsonObject jObj);
    void msgCountDmSlot(const QString& argMsgCount,QJsonObject jObj);
    void msgCountGroupSlot(const QString& argMsgCount,QJsonObject jObj);
    void userListSlot(const QString& argUserCount,QJsonObject jObj);
    void groupListSlot(const QString& argGroupCount,QJsonObject jObj);
    void channelListSlot(const QString& argChannelCount,QJsonObject jObj);
    void server_handler_on_Register();
    void server_handler_on_SendMessage();
    void server_handler_on_Login(QString token);
    void server_handler_on_Logout();
    void server_handler_on_createNewChat();
    void server_handler_on_joinChat();
    void server_hanlder_on_GetMsg(QJsonDocument jSonContent);
    void server_handler_on_failure(QString Error);
signals:
    void Success();
    void SuccessOnLogout();
    void SuccessOnSendMessage();
    void SuccessOnGetMessage(QJsonObject,size_t);
    void FailureOnGetMessage(QString Error);
    void Failure(QString Error);
    void FailureOnLogout(QString Error);
};

#endif // USER_H
