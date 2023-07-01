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
    void getMsgDm(const QString &token, const QString &dst); // new entry
    void getMsgGroup(const QString &token, const QString &dst); // new entry
    void getMsgChannel(const QString &token, const QString &dst); // new entry
    void getUserList(const QString &token);
    void getChannelList(const QString &token);
    void getGroupList(const QString &token);
    QByteArray* getResponse();
signals:
    void SuccessOnRegister();
    void SuccessOnLogin(QString new_token);
    void SuccessOnLogout();
    void SuccessOnGetMsgDm(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgGroup(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgChannel(QJsonDocument jSonContent); // new entry
    void SuccessOnGetUserList(QJsonDocument jSonContent);
    void SuccessOnGetChannelList(QJsonDocument jSonContent);
    void SuccessOnGetGroupList(QJsonDocument jSonContent);
    void getMsgCountSignalDM(QString msgCount,QJsonObject jSonObject);
    void getMsgCountSignalGroup(QString msgCount,QJsonObject jSonObject);
    void getMsgCountSignalChannel(QString msgCount,QJsonObject jSonObject);
    void getUserListSignal(QString userCount,QJsonObject jSonObject);
    void getChannelListSignal(QString userCount,QJsonObject jSonObject);
    void getGroupListSignal(QString userCount,QJsonObject jSonObject);
    void SuccessOnCreateGroup();
    void SuccessOnCreateChannel();
    void FailureOnGetChatList(QString error);
    void SuccessOnJoinChannel();
    void FailureOnJoinChannel(QString error);
    void SuccessOnJoinGroup();
    void FailureOnJoinGroup(QString error);
    void FailureOnRegister(QString error);
    void FailureOnLogin(QString error);
    void FailureOnLogout(QString error);
    void FailureOnGetMsg(QString error);
    void FailureOnCreateGroup(QString error);
    void FailureOnCreateChannel(QString error);
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
    void getUserListResponder();
    void getChannelListResponder();
    void getGroupListResponder();
    void createGroupResponder();
    void createChannelResponder();
    void getMsgDmResponder();
    void getMsgChannelResponder();
    void getMsgGroupResponder();
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
};

#endif // API_H
