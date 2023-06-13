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

