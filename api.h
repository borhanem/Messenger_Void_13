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
    void getMsgDM(const QString &token, const QString &dst); // new entry
    void getMsgGroup(const QString &token, const QString &dst); // new entry
    void getMsgChannel(const QString &token, const QString &dst); // new entry
    QByteArray* getResponse();
signals:
    void SuccessOnRegister();
    void SuccessOnLogin(QString new_token);
    void SuccessOnLogout();
    void SuccessOnGetMsgDM(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgGroup(QJsonDocument jSonContent); // new entry
    void SuccessOnGetMsgChannel(QJsonDocument jSonContent); // new entry
    void getMsgCountSignalDM(QString msgCount,QJsonObject jSonObject);
    void getMsgCountSignalGroup(QString msgCount,QJsonObject jSonObject);
    void getMsgCountSignalChannel(QString msgCount,QJsonObject jSonObject);
    void SuccessOnCreateGroup();
    void SuccessOnCreateChannel();
    void FailureOnRegister(QString error);
    void FailureOnLogin(QString error);
    void FailureOnLogout(QString error);
    void FailureOnGetMsg(QString error); // new entry
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
    void getMsgDmResponder(); // new entry
    void getMsgGroupResponder(); // new entry
    void getMsgChannelResponder(); // new entry
    void createGroupResponder();
    void createChannelResponder();
    void SendMessageToUserResponder(); // new entry
    void sendMessageToGroupResponder();
    void sendMessageToChannelResponder();
    //void getData();
private:
    QString url_s;
    QNetworkAccessManager* man_ptr;
    QByteArray* data;
    QNetworkReply *reply;
};

#endif // API_H
