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
    connect(reply,&QNetworkReply::finished,this,&API::getData);
}

void API::Login(const QString &uname, const QString &pass)
{
    QString temp = url_s+"/login?username="+uname+"&password="+pass;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::getData);
}

QByteArray *API::getResponse()
{
    return data;
}


void API::getData()
{
    if (reply->error() == QNetworkReply::NoError) {
        // If the request was successful, read the response
        *data = reply->readAll();
        // qDebug() << "Response:" << *data;
        emit Success(data);

    } else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit Failure(reply);
    }
    reply->deleteLater();
}

