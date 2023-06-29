#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDebug>
#include "api.h"
#include <QDataStream>
#include <QFile>
#include <QDir>
//#include "refresherchannel.h"
//#include "refresherDirect.h"
//#include "refreshergroup.h"
//#include "refresherabstract.h"
class User : public QObject
{
    Q_OBJECT
public:
    User();
    explicit User(QString userName,QString passWord,QString token = "",QString userPath="userLog.dat",QObject* parent = nullptr);
    void Register();
    void login();
    void logOut();
    void createGroup(const QString& groupName)const;
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
    int msgCountGetterDm(const QString &dst);
    int msgCountGetterChannel(const QString &dst);
    int msgCountGetterGroup(const QString &dst);
    QJsonObject msgContentGetterDm(const QString &dst);
    QJsonObject msgContentGetterChannel(const QString &dst);
    QJsonObject msgContentGetterGroup(const QString &dst);
    void msgCountDmReinit(const QString &dst);
    void msgCountGroupReinit(const QString &dst); // check this for group
    void msgCountChannelReinit(const QString &dst);
private:
    const QString m_UserLogFilePath;
    QString m_username;
    QString m_password;
    QString m_token;
    API* m_server;
    QMap<QString,QPair<int,QJsonObject>> directData; // stores msg count and message JSon obj
    QMap<QString,QPair<int,QJsonObject>> groupData;
    QMap<QString,QPair<int,QJsonObject>> channelData;
    //void writeToFile(char* filePath);
    //void readFromFile(char* filePath);
private slots:
    void msgCountChannelSlot(const QString& argMsgCount,QJsonObject jObj);
    void msgCountDmSlot(const QString& argMsgCount,QJsonObject jObj);
    void msgCountGroupSlot(const QString& argMsgCount,QJsonObject jObj);
    void server_handler_on_Register();
    void server_handler_on_Login(QString token);
    void server_handler_on_Logout();
    void server_handler_on_creategGroup();
    void server_handler_on_failure(QString Error);
signals:
    void Success();
    void SuccessOnLogout();
    void Failure(QString Error);
    void FailureOnLogout(QString Error);
};

#endif // USER_H
