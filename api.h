#ifndef API_H
#define API_H
#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QString>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
//#include "refresherchannel.h"
//#include "refresherDirect.h"
//#include "refreshergroup.h"

class API : public QObject
{
    Q_OBJECT
public:
    explicit API(const QString& sUrl,QObject *parent = nullptr);
    void Register(const QString& uname,const QString& pass);
    void Login(const QString& uname,const QString& pass);
    void Logout(const QString &uname, const QString &pass);
    void SendMessageToUser(const QString& token,const QString& dst,const QString& body);
    void sendMessageToGroup(const QString& token,const QString& dst,const QString& body);
    void sendMessageToChannel(const QString& token,const QString& dst,const QString& body);
    void createGroup(const QString& token,const QString& groupName);
    void createChannel(const QString& token,const QString& channelName);
    void joinGroup(const QString& token,const QString& gruopName);
    void joinChannel(const QString& token,const QString& channelName);
    void getMsgUser(const QString &token, const QString &dst); // new entry
    void getMsgGroup(const QString &token, const QString &dst); // new entry
    void getMsgChannel(const QString &token, const QString &dst); // new entry
    void getGroupList(const QString &token);
    void getChannelList(const QString &token);
    void getUserList(const QString &token);

    QByteArray* getResponse();
signals:
    void SuccessOnRegister();
    void SuccessOnLogin(QString new_token);
    void SuccessOnLogout();
    void SuccessOnGetMsgUser(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgGroup(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgChannel(QJsonDocument jSonContent); // new entry
    void SuccessOnGetGroupList(QJsonDocument);
    void SuccessOnGetChannelList(QJsonDocument);
    void SuccessOnGetUserList(QJsonDocument);
    void SuccessOnCreateGroup();
    void SuccessOnCreateChannel();
    void SuccessOnJoinChannel();
    void FailureOnJoinChannel(QString error);
    void SuccessOnJoinGroup();
    void FailureOnJoinGroup(QString error);
    void getMsgCountSignal(QString msgCount);
    void FailureOnRegister(QString error);
    void FailureOnLogin(QString error);
    void FailureOnLogout(QString error);
    void FailureOnGetMsgUser(QString error);
    void FailureOnGetMsgGroup(QString error);
    void FailureOnGetMsgChannel(QString error);
    void FailureOnCreateGroup(QString error);
    void FailureOnCreateChannel(QString error);
    void FailureOnGetGroupList(QString error);
    void FailureOnGetChannelList(QString error);
    void FailureOnGetUserList(QString error);
    void SuccessOnSendMsgToUser();
    void SuccessOnSendMsgToGroup();
    void SuccessOnSendMsgToChannel();
    void FailureOnSendMsgToChannel(QString error);
    void FailureOnSendMsgToGroup(QString error);
    void FailureOnSendMsgToUser(QString error);
private slots:
    void RegisterResponder();
    void LoginResponder();
    void LogoutResponder();
    void createGroupResponder();
    void createChannelResponder();
    void getMsgUserResponder();
    void getMsgChannelResponder();
    void getMsgGroupResponder();
    void getGroupListResponder();
    void getChannelListResponder();
    void getUserListResponder();
    void SendMessageToUserResponder(); // new entry
    void sendMessageToGroupResponder();
    void sendMessageToChannelResponder();
    void joinGroupResponder();
    void joinChannelResponder();
    //void getData();
private:
    QString url_s;
    QNetworkAccessManager* man_ptr;
    QByteArray* data;
    QNetworkReply *reply;
    bool m_isAvailable;
};

#endif // API_H
