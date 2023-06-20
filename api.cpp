#include "api.h"

API::API(const QString& sUrl,QObject *parent)
    : QObject{parent},url_s(sUrl)
{
    man_ptr = new QNetworkAccessManager(this);
    data = new QByteArray();
    //connect(reply,&QNetworkReply::finished,this,&API::getData);
}

void API::Register(const QString &uname, const QString &pass)
{
    // http://api.barafardayebehtar.ml:8080/signup?username=sara&password=1234&firstname=sara&lastname=baradaran
    QString temp = url_s+"/signup?username="+uname+"&password="+pass;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::RegisterResponder);
}

void API::Login(const QString &uname, const QString &pass)
{
    QString temp = url_s+"/login?username="+uname+"&password="+pass;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::LoginResponder);
}

void API::Logout(const QString &uname, const QString &pass)
{
    QString temp = url_s + "/logout?username="+uname+"&password="+pass;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::LogoutResponder);
}

void API::SendMessageToUser(const QString &token, const QString &dst, const QString &body)
{
    QString temp = url_s +"/sendmessageuser?token="+token+"&dst="+dst+"&body="+body;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::LogoutResponder);
}

void API::getMsgDM(const QString &token, const QString &dst)
{
    QString temp = url_s + "/getuserchats?token=" + token + "&dst=" + dst;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::DMId);
}

void API::getMsgGroup(const QString &token, const QString &dst)
{
    QString temp = url_s + "/getgroupchats?token=" + token + "&dst=" + dst;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::GroupId);
}

void API::getMsgChannel(const QString &token, const QString &dst)
{
    QString temp = url_s + "/getchannelchats?token=" + token + "&dst=" + dst;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::ChannelID);
}

void API::DMId()
{
    getMsgResponder(1);
}

void API::GroupId()
{
    getMsgResponder(2);
}

void API::ChannelID()
{
    getMsgResponder(3);
}

QByteArray *API::getResponse()
{
    return data;
}

void API::RegisterResponder()
{
    // If the request was successful
    if (reply->error() == QNetworkReply::NoError) {
       //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();
        if(respond_code == "200")
        {
            emit SuccessOnRegister();
        }
        else
        {
            emit FailureOnRegister(respond_message);
        }


    } else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnRegister(reply->errorString());
    }
    reply->deleteLater();
}

void API::LoginResponder()
{
    if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();
        QString respond_token = jObj.value("token").toString();
        if(respond_code == "200")
        {
            emit SuccessOnLogin(respond_token);
        }
        else
        {
            emit FailureOnLogin(respond_message);
        }
        }
    else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnLogin(reply->errorString());
        }
        reply->deleteLater();
}

void API::LogoutResponder()
{
        if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnLogout();
        }
        else
        {
            emit FailureOnLogout(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnLogout(reply->errorString());
        }
        reply->deleteLater();
}

void API::getMsgResponder(int argMsgID)
{
     if (reply->error() == QNetworkReply::NoError) {
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();
        if(respond_code == "200"){
            if (argMsgID == 1){
                emit SuccessOnGetMsgDM(jDoc);
            } else if(argMsgID == 2){
                emit SuccessOnGetMsgGroup(jDoc);
            } else if(argMsgID == 3){
                emit SuccessOnGetMsgChannel(jDoc);
            }
            emit getMsgCountSignal(respond_message);
         } else {
            emit FailureOnGetMsg(respond_message);
        }
     } else {
        data = NULL;
        emit FailureOnGetMsg(reply->errorString());
     }
    reply->deleteLater();
}

void API::SendMessageToUserResponder()
{
        if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnSendMsgToUser();
        }
        else
        {
            emit FailureOnSendMsgToUser(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnLogout(reply->errorString());
        }
        reply->deleteLater();
}



//void API::getData()
//{
//    if (reply->error() == QNetworkReply::NoError) {
//        // If the request was successful, read the response
//        *data = reply->readAll();
//        // qDebug() << "Response:" << *data;
//        emit Success(data);

//    } else {
//        // If there was an error, display the error message
//        // qDebug() << "Error:" << reply->errorString();
//        data = NULL;
//        emit Failure(reply);
//    }
//    reply->deleteLater();
//}

