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
    void createGroup(const QString& token,const QString& groupName);
    void createChannel(const QString& token,const QString& channelName);
    void getMsgDM(const QString &token, const QString &dst); // new entry
    void getMsgGroup(const QString &token, const QString &dst); // new entry
    void getMsgChannel(const QString &token, const QString &dst); // new entry
    void DMId(); // new entry
    void GroupId(); // new entry
    void ChannelID(); // new entry
    QByteArray* getResponse();
signals:
    void SuccessOnRegister();
    void SuccessOnLogin(QString new_token);
    void SuccessOnLogout();
    void SuccessOnGetMsgDM(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgGroup(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgChannel(QJsonDocument jSonContent); // new entry
    void SuccessOnCreateGroup();
    void SuccessOnCreateChannel();
    void getMsgCountSignal(QString msgCount);
    void FailureOnRegister(QString error);
    void FailureOnLogin(QString error);
    void FailureOnLogout(QString error);
    void FailureOnGetMsg(QString error); // new entry
    void FailureOnCreateGroup(QString error);
    void FailureOnCreateChannel(QString error);
    void SuccessOnSendMsgToUser();
    void SuccessOnSendMsgToGroup();
    void FailureOnSendMsgToGroup(QString error);
    void FailureOnSendMsgToUser(QString error);
private slots:
    void RegisterResponder();
    void LoginResponder();
    void LogoutResponder();
    void createGroupResponder();
    void createChannelResponder();
    void getMsgResponder(int argMsgID); // new entry
    void SendMessageToUserResponder(); // new entry
    void sendMessageToGroupResponder();
    //void getData();
private:
    QString url_s;
    QNetworkAccessManager* man_ptr;
    QByteArray* data;
    QNetworkReply *reply;
};

#endif // API_H
