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

void API::SendMessageToUser(const QString &token,const QString& dst,const QString& body)
{
    /*
     *  /sendmessageuser?token=7a3c48f7c7939b7269d01443a431825f&dst=ali&body=hi
    */
    QString temp = url_s +"/sendmessageuser?token="+token+"&dst="+dst+"&body="+body;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::SendMessageToUserResponder);
}

void API::sendMessageToGroup(const QString &token, const QString& dst,const QString& body)
{
    /*
     *  /sendmessagegroup?token=7a3c48f7c7939b7269d01443a431825f&dst=ap&body=hello%20all
    */
    QString temp = url_s +"/sendmessagegroup?token="+token+"&dst="+dst+"&body="+body;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::sendMessageToGroupResponder);
}

void API::sendMessageToChannel(const QString &token, const QString &dst, const QString &body)
{
    /*
         /sendmessagechannel?token=7a3c48f7c7939b7269d01443a431825f&dst=mychannel&body=hello%20all
    */
    QString temp = url_s +"/sendmessagechannel?token="+token+"&dst="+dst+"&body="+body;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::sendMessageToChannelResponder);
}


void API::createGroup(const QString &token, const QString &groupName)
{
    /*
     * /creategroup?token=7a3c48f7c7939b7269d01443a431825f&group_name=G1&group_title=Group1
     */
    QString temp = url_s + "/creategroup?token="+token+"&group_name="+groupName;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::createGroupResponder);
}

void API::createChannel(const QString &token, const QString &channelName)
{
    /*
     * /createchannel?token=7a3c48f7c7939b7269d01443a431825f&channel_name=mychannel&channel_title=Channel1
     */
    QString temp = url_s + "/createchannel?token="+token+"&channel_name="+channelName;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::createChannelResponder);
}

void API::joinGroup(const QString &token, const QString &gruopName)
{
 /*
  * /joingroup?token=7a3c48f7c7939b7269d01443a431825f&group_name=ap
  */
    QString temp = url_s + "/joingroup?token="+token+"&group_name="+gruopName;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::joinGroupResponder);
}

void API::joinChannel(const QString &token, const QString &channelName)
{
 /*
  * /joinchannel?token=7a3c48f7c7939b7269d01443a431825f&channel_name=aplab
  */
    QString temp = url_s + "/joinchannel?token="+token+"&channel_name="+channelName;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::joinChannelResponder);
}

void API::getMsgUser(const QString &token, const QString &dst)
{
    QString temp = url_s + "/getuserchats?token=" + token + "&dst=" + dst;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    //connect(reply,&QNetworkReply::finished,this,&API::DMId);
}

void API::getMsgGroup(const QString &token, const QString &dst)
{
    QString temp = url_s + "/getgroupchats?token=" + token + "&dst=" + dst;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    connect(reply,&QNetworkReply::finished,this,&API::getMsgGroupResponder);
}

void API::getMsgChannel(const QString &token, const QString &dst)
{
    QString temp = url_s + "/getchannelchats?token=" + token + "&dst=" + dst;
    reply = man_ptr->get(QNetworkRequest(QUrl(temp)));
    //connect(reply,&QNetworkReply::finished,this,&API::ChannelID);
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

void API::createGroupResponder()
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
            emit SuccessOnCreateGroup();
        }
        else
        {
            emit FailureOnCreateGroup(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnCreateGroup(reply->errorString());
        }
        reply->deleteLater();
}

void API::createChannelResponder()
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
            emit SuccessOnCreateChannel();
        }
        else
        {
            emit FailureOnCreateChannel(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnCreateChannel(reply->errorString());
        }
        reply->deleteLater();
}

void API::getMsgUserResponder()
{
        if (reply->error() == QNetworkReply::NoError) {
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        if(jDoc.isObject())
        {
            QJsonObject jObj = jDoc.object();
            QString respond_code =  jObj.value("code").toString();
            QString respond_message =jObj.value("message").toString();
            if(respond_code == "200"){

                emit SuccessOnGetMsgUser(jDoc);
            }
            else {
                emit FailureOnGetMsgUser(respond_message);
            }
        }
        else {
            data = NULL;
            emit FailureOnGetMsgUser(reply->errorString());
        }
        }
        else
        {
        qDebug("getMsgUserResponde: jdoc is not a object\n");
        }
        reply->deleteLater();
}

void API::getMsgChannelResponder()
{
        if (reply->error() == QNetworkReply::NoError) {
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        if(jDoc.isObject())
        {
            QJsonObject jObj = jDoc.object();
            QString respond_code =  jObj.value("code").toString();
            QString respond_message =jObj.value("message").toString();
            if(respond_code == "200"){

                emit SuccessOnGetMsgChannel(jDoc);
            }
            else {
                emit FailureOnGetMsgChannel(respond_message);
            }
        }
        else {
            data = NULL;
            emit FailureOnGetMsgChannel(reply->errorString());
        }
        }
        else
        {
        qDebug("getMsgChannelResponde: jdoc is not a object\n");
        }
        reply->deleteLater();
}

void API::getMsgGroupResponder()
{
        if (reply->error() == QNetworkReply::NoError) {
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        if(jDoc.isObject())
        {
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();
        if(respond_code == "200"){

                emit SuccessOnGetMsgGroup(jDoc);
        }
        else {
                emit FailureOnGetMsgGroup(respond_message);
               }
        }
        else {
        data = NULL;
            emit FailureOnGetMsgGroup(reply->errorString());
        }
        }
        else
        {
        qDebug("getMsgGroupResponde: jdoc is not a object\n");
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
        emit FailureOnSendMsgToUser(reply->errorString());
        }
        reply->deleteLater();
}

void API::sendMessageToGroupResponder()
{
        qDebug("sendMessageToGroupResponder from API class\n");
        if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnSendMsgToGroup();
        }
        else
        {
            emit FailureOnSendMsgToGroup(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnSendMsgToGroup(reply->errorString());
        }
        reply->deleteLater();
}

void API::sendMessageToChannelResponder()
{
        qDebug("sendMessageToChannelpResponder from API class\n");
        if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            emit SuccessOnSendMsgToChannel();
        }
        else
        {
            emit FailureOnSendMsgToChannel(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnSendMsgToGroup(reply->errorString());
        }
        reply->deleteLater();
}

void API::joinGroupResponder()
{
        qDebug("joinGroupResponder from API class\n");
        if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            if(respond_message == "You are already Joined!")
            {
                emit FailureOnJoinGroup("You are already Joined!");
            }
            else{
            emit SuccessOnJoinGroup();
            }
        }
        else
        {
            emit FailureOnJoinGroup(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnJoinGroup(reply->errorString());
        }
        reply->deleteLater();
}

void API::joinChannelResponder()
{
        qDebug("joinGroupResponder from API class\n");
        if (reply->error() == QNetworkReply::NoError) {
        //read the response
        *data = reply->readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(*data);
        QJsonObject jObj = jDoc.object();
        QString respond_code =  jObj.value("code").toString();
        QString respond_message =jObj.value("message").toString();

        if(respond_code == "200")
        {
            if(respond_message == "You are already Joined!")
            {
            emit FailureOnJoinGroup("You are already Joined!");
            }
            else{
            emit SuccessOnJoinGroup();
            }

        }
        else
        {
            emit FailureOnJoinChannel(respond_message);
        }
        }
        else {
        // If there was an error, display the error message
        // qDebug() << "Error:" << reply->errorString();
        data = NULL;
        emit FailureOnJoinChannel(reply->errorString());
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

