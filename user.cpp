#include "user.h"
#include <fstream>
#include <iostream>
#include <string>
#include <QRegularExpression>
#include "msgBaseReceive.h"
#include "msgBaseSend.h"
User::User() : m_UserLogFilePath("vdata/UserInfo/userLog.dat"),
    m_username ("VoidUser"),
    m_password("123456789"),
    m_token("borhan81alireza82mahta83"),
    m_server(new API("http://api.barafardayebehtar.ml:8080"))
{
    QObject::connect(m_server,&API::SuccessOnRegister,this,&User::server_handler_on_Register);
    QObject::connect(m_server,&API::SuccessOnLogin,this,&User::server_handler_on_Login);
    QObject::connect(m_server,&API::SuccessOnLogout,this,&User::server_handler_on_Logout);
    QObject::connect(m_server,&API::SuccessOnSendMsgToUser,this,&User::server_handler_on_Logout);
    QObject::connect(m_server,&API::SuccessOnSendMsgToGroup,this,&User::server_handler_on_SendMessage);//
    QObject::connect(m_server,&API::FailureOnSendMsgToGroup,this,&User::server_handler_on_failure);//
    QObject::connect(m_server,&API::SuccessOnSendMsgToChannel,this,&User::server_handler_on_SendMessage);//
    QObject::connect(m_server,&API::FailureOnSendMsgToChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnRegister,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogin,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogout,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnCreateGroup,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnCreateChannel,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinGroup,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinChannel,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnGetMsgGroup,this,&User::server_hanlder_on_GetMsg);
    QObject::connect(m_server,&API::FailureOnGetMsgGroup,this,&User::FailureOnGetMessage);
    QObject::connect(m_server,&API::SuccessOnGetMsgChannel,this,&User::server_hanlder_on_GetMsg);
    QObject::connect(m_server,&API::FailureOnGetMsgChannel,this,&User::FailureOnGetMessage);
    QObject::connect(m_server,&API::SuccessOnGetMsgUser,this,&User::server_hanlder_on_GetMsg);
    QObject::connect(m_server,&API::FailureOnGetMsgUser,this,&User::FailureOnGetMessage);
    QObject::connect(m_server,&API::SuccessOnGetUserList,this,&::User::server_handler_on_GetChatList);
    QObject::connect(m_server,&API::FailureOnGetUserList,this,&::User::FailureOnGetChatList);
    QObject::connect(m_server,&API::SuccessOnGetGroupList,this,&::User::server_handler_on_GetChatList);
    QObject::connect(m_server,&API::FailureOnGetGroupList,this,&::User::FailureOnGetChatList);
    QObject::connect(m_server,&API::SuccessOnGetChannelList,this,&::User::server_handler_on_GetChatList);
    QObject::connect(m_server,&API::FailureOnGetChannelList,this,&::User::FailureOnGetChatList);
}

User::User(QString userName, QString passWord, QString token,QString userPath, QObject *parent)
    : QObject{parent},
    m_UserLogFilePath(userPath),
    m_username(userName),
    m_password(passWord),
    m_token(token),
    m_server(new API("http://api.barafardayebehtar.ml:8080"))
{
    QObject::connect(m_server,&API::SuccessOnRegister,this,&User::server_handler_on_Register);
    QObject::connect(m_server,&API::SuccessOnLogin,this,&User::server_handler_on_Login);
    QObject::connect(m_server,&API::SuccessOnLogout,this,&User::server_handler_on_Logout);
    QObject::connect(m_server,&API::SuccessOnSendMsgToUser,this,&User::server_handler_on_Logout);
    QObject::connect(m_server,&API::SuccessOnSendMsgToGroup,this,&User::server_handler_on_SendMessage);//
    QObject::connect(m_server,&API::FailureOnSendMsgToGroup,this,&User::server_handler_on_failure);//
    QObject::connect(m_server,&API::SuccessOnSendMsgToChannel,this,&User::server_handler_on_SendMessage);//
    QObject::connect(m_server,&API::FailureOnSendMsgToChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnRegister,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogin,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogout,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnCreateGroup,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnCreateChannel,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinGroup,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinChannel,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnGetMsgGroup,this,&User::server_hanlder_on_GetMsg);
    QObject::connect(m_server,&API::FailureOnGetMsgGroup,this,&User::FailureOnGetMessage);
    QObject::connect(m_server,&API::SuccessOnGetMsgChannel,this,&User::server_hanlder_on_GetMsg);
    QObject::connect(m_server,&API::FailureOnGetMsgChannel,this,&User::FailureOnGetMessage);
    QObject::connect(m_server,&API::SuccessOnGetMsgUser,this,&User::server_hanlder_on_GetMsg);
    QObject::connect(m_server,&API::FailureOnGetMsgUser,this,&User::FailureOnGetMessage);
    QObject::connect(m_server,&API::SuccessOnGetUserList,this,&::User::server_handler_on_GetChatList);
    QObject::connect(m_server,&API::FailureOnGetUserList,this,&::User::FailureOnGetChatList);
    QObject::connect(m_server,&API::SuccessOnGetGroupList,this,&::User::server_handler_on_GetChatList);
    QObject::connect(m_server,&API::FailureOnGetGroupList,this,&::User::FailureOnGetChatList);
    QObject::connect(m_server,&API::SuccessOnGetChannelList,this,&::User::server_handler_on_GetChatList);
    QObject::connect(m_server,&API::FailureOnGetChannelList,this,&::User::FailureOnGetChatList);
}
void User::Register()
{
    m_server->Register(m_username,m_password);
}

void User::login()
{
    m_server->Login(this->m_username,this->m_password);
    // saveToFile(filePath);

}

void User::logOut()
{
    m_server->Logout(this->m_username,this->m_password);
    // std::remove(m_file_path.toStdString().c_str());
}

void User::createNewChat(const QString &chatName, const ChatType &type) const
{

    switch(type)
    {
    case Private:
        qDebug() << "User::joinChat : There is no Option for joining a Private Chat";
        break;
    case Group:
        m_server->createGroup(this->m_token,chatName);
        break;
    case Channel:
        m_server->createChannel(this->m_token,chatName);
        break;

    default:
        qDebug("Error - from User::sendMessage : No match for type\n");
    }
}

void User::joinChat(const QString &chatName, const ChatType &type) const
{
    switch(type)
    {
    case Private:
        qDebug() << "User::joinChat : There is no Option for joining a Private Chat";
        break;
    case Channel:
        m_server->joinChannel(this->m_token,chatName);
        break;
    case Group:
        m_server->joinGroup(this->m_token,chatName);
        break;
    default:
        qDebug() << "User::joinChat : No match for type";
        break;
    }
}
void User::sendMessage(const Message &msg, const ChatType &type)
{
    switch(type)
    {
    case Private:
        m_server->SendMessageToUser(this->m_token,msg.receiver(),msg.body());
        break;
    case Group:
        m_server->sendMessageToGroup(this->m_token,msg.receiver(),msg.body());
        break;
    case Channel:
        m_server->sendMessageToChannel(this->m_token,msg.receiver(),msg.body());
        break;

    default:
        qDebug("Error - from User::sendMessage : No match for type\n");
    }
}

void User::getMsg(const QString &dst, const ChatType &type)
{

    switch(type)
    {
    case Private:
        m_server->getMsgUser(this->m_token,dst);
        break;

    case Group:
        m_server->getMsgGroup(this->m_token,dst);
        break;

    case Channel:
        m_server->getMsgChannel(this->m_token,dst);
        break;

    default:
        qDebug() << "Error - from User::getMsg : No match for type\n";
        break;
    }
}

void User::getChatList(const ChatType &type)
{
    switch(type)
    {
    case Private:
        m_server->getUserList(this->m_token);
        break;

    case Group:
        m_server->getGroupList(this->m_token);
        break;

    case Channel:
        m_server->getChannelList(this->m_token);
        break;

    default:
        qDebug() << "Error - from User::getMsg : No match for type\n";
        break;
    }
}

int User::loadFromFile()
{
    QFile logFile(m_UserLogFilePath);
    if(!logFile.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    QDataStream user_ds(&logFile);
    user_ds.setVersion(QDataStream::Qt_6_5);
    user_ds >> *this;

    logFile.close();
    return 0;
    //    char *data;
    //    size_t data_size;
    //    std::ifstream iFile;
    //    iFile.open(m_file_path.toStdString().c_str(),std::ios::binary);
    //    if(iFile.is_open())
    //    {
    //            // load m_username member data
    //            iFile.read((char*)&data_size,sizeof(size_t));
    //            data = new char[data_size+1];
    //            iFile.read(data,data_size*sizeof(char));
    //            data[data_size]='\0';
    //            m_username = data;
    //            delete[] data;
    //            // load m_password member data
    //            iFile.read((char*)&data_size,sizeof(size_t));
    //            data = new char[data_size+1];
    //            iFile.read(data,data_size*sizeof(char));
    //            data[data_size]='\0';
    //            m_password = data;
    //            delete[] data;
    //            // load m_token member data
    //            iFile.read((char*)&data_size,sizeof(size_t));
    //            data = new char[data_size+1];
    //            iFile.read(data,data_size*sizeof(char));
    //            data[data_size]='\0';
    //            m_token = data;
    //            delete[] data;

    //            // close the file
    //            return 0;
    //        iFile.close();
    //    }
    //    return -1;
}

int User::saveToFile()
{
    QDir LogDir;
    if(!LogDir.exists("vdata/UserInfo"))
    {
        LogDir.mkpath("vdata/UserInfo");
    }
    QFile logFile(m_UserLogFilePath);
    if(!logFile.open(QIODevice::WriteOnly))
    {
        return -1;
    }
    QDataStream user_ds(&logFile);
    user_ds.setVersion(QDataStream::Qt_6_5);
    user_ds << *this;

    logFile.close();
    return 0;
    //    //char *data;
    //    size_t data_size;
    //    std::string std_data;
    //    std::ofstream oFile;
    //    oFile.open(m_file_path.toStdString().c_str(),std::ios::binary);

    //    if(oFile.is_open())
    //    {

    //        // save m_username member data
    ////    std_data = m_username.toStdString();
    ////    data_size = std_data.size();
    ////    //data = std_data.data();
    ////    oFile.write((char*)&data_size,sizeof(size_t));
    ////    oFile.write(std_data.c_str(),data_size*sizeof(char));
    ////        // save m_password member data
    ////    std_data = m_password.toStdString();
    ////    data_size = std_data.size();
    ////    //data = std_data.data();
    ////    oFile.write((char*)&data_size,sizeof(size_t));
    ////    oFile.write(std_data.c_str(),data_size*sizeof(char));
    ////        // save m_token member data
    ////    std_data = m_token.toStdString();
    ////    data_size = std_data.size();
    ////    //data = std_data.data();
    ////    oFile.write((char*)&data_size,sizeof(size_t));
    ////    oFile.write(std_data.c_str(),data_size*sizeof(char));

    ////    // close the file
    ////    oFile.close();
    ////        return 0;
    ////    }
    ////    return -1;

}

QString User::getUserName()
{
    return m_username;
}

QString User::getPassword()
{
    return m_password;
}

QString User::getToken()
{
    return m_token;
}

void User::SetUserName(const QString &new_user_name)
{
    m_username = new_user_name;
}

void User::SetPassWord(const QString &new_pass_word)
{
    m_password = new_pass_word;
}

void User::server_handler_on_Register()
{
    /*    if(saveToFile()){
        emit Failure("Can't Save the User data");
    }
    else*{ }*/
    emit Success();

}

void User::server_handler_on_SendMessage()
{
    qDebug("server_handler_on_SendMessage from UserClass\n");
    emit SuccessOnSendMessage();
}

void User::server_handler_on_Login(QString token)
{
    // user already logged in
    if(token.isEmpty())
    {
        this->logOut();
        emit Failure("Try Again");
        return;
    }
    m_token = token;
    // if savetoFile can't save the user
    if(saveToFile())
    {
        emit Failure("Can't Save the user data");
    }
    else{
        emit Success();
    }
}

void User::server_handler_on_Logout()
{
    std::remove(m_UserLogFilePath.toStdString().c_str());
    emit SuccessOnLogout();
}

void User::server_handler_on_createNewChat()
{
    emit Success();
}

void User::server_handler_on_joinChat()
{
    emit Success();
}

void User::server_hanlder_on_GetMsg(QJsonDocument jSonContent)
{
    qDebug() << "User::server_hanlder_on_GetMsg is running\n";
    QJsonObject msgContent = jSonContent.object();//currUser->msgContentGetterGroup(dstGroup);
    QRegularExpression re("-\\d+-");
    size_t msgCount;
    QString argMsgCount = msgContent.value("message").toString();
    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argMsgCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        msgCount = numStr.toULongLong();
        qDebug() << "User::server_hanlder_on_GetMsg - msgCount : " << msgCount;
    }
    else
    {
        qDebug() << "User::server_hanlder_on_GetMsg - do not match!\n";
        return;
    }
    emit SuccessOnGetMessage(msgContent,msgCount);
}

void User::server_handler_on_failure(QString error)
{
    qDebug() << "User::server_handler_on_failure : " << error;
    emit Failure(error);

}

void User::server_handler_on_GetChatList(QJsonDocument jSonContent)
{
    qDebug() << "User::server_handler_on_GetChatList is running\n";
    QJsonObject msgContent = jSonContent.object();//currUser->msgContentGetterGroup(dstGroup);
    QRegularExpression re("-\\d+-");
    size_t msgCount;
    QString argMsgCount = msgContent.value("message").toString();
    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argMsgCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        msgCount = numStr.toULongLong();
        qDebug() << "User::server_handler_on_GetChatList - msgCount : " << msgCount;
    }
    else
    {
        qDebug() << "User::server_handler_on_GetChatList - do not match!\n";
        return;
    }
    emit SuccessOnGetChatList(msgContent,msgCount);
}
QDataStream& operator<<(QDataStream &stream,const User &u)
{
    stream << u.m_username;
    stream << u.m_password;
    stream << u.m_token;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, User &u)
{
    stream >> u.m_username;
    stream >> u.m_password;
    stream >> u.m_token;
    return stream;
}
//void User::LoadToFile(char *filePath)
//{
//    std::ofstream f1out;
//    User temp(m_username,m_password,m_token);
//    qDebug() << "from write to file: " << temp.getUserName() << " " << temp.getPassword() << " "<< temp.getToken();
//    f1out.open(filePath);
//    if(f1out.is_open())
//    {
//    f1out.write((char*)&temp, sizeof(temp));
//    f1out.close();
//    }
//}

//void User::readFromFile(char *filePath)
//{
//    std::ifstream f1in;
//    f1in.open(filePath);
//    f1in.read((char*)this, sizeof(User));
//    f1in.close();
//}
