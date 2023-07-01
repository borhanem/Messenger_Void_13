#include "user.h"
#include <fstream>
#include <iostream>
#include <string>
#include <QRegularExpression>
#include <QThread>
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
    QObject::connect(m_server,&API::FailureOnGetMsg,this,&User::server_handler_on_failure); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalDM,this,&User::msgCountDmSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalChannel,this,&User::msgCountChannelSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalGroup,this,&User::msgCountGroupSlot); // new entry
    QObject::connect(m_server,&API::SuccessOnCreateGroup,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnCreateChannel,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinGroup,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinChannel,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::getUserListSignal,this,&User::userListSlot);
    QObject::connect(m_server,&API::getGroupListSignal,this,&User::groupListSlot);
    QObject::connect(m_server,&API::getChannelListSignal,this,&User::channelListSlot);
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
    QObject::connect(m_server,&API::FailureOnGetMsg,this,&User::server_handler_on_failure); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalDM,this,&User::msgCountDmSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalChannel,this,&User::msgCountChannelSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalGroup,this,&User::msgCountGroupSlot); // new entry
    QObject::connect(m_server,&API::SuccessOnCreateGroup,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnCreateChannel,this,&User::server_handler_on_createNewChat);
    QObject::connect(m_server,&API::FailureOnCreateChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinGroup,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinGroup,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::SuccessOnJoinChannel,this,&User::server_handler_on_joinChat);
    QObject::connect(m_server,&API::FailureOnJoinChannel,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::getUserListSignal,this,&User::userListSlot);
    QObject::connect(m_server,&API::getGroupListSignal,this,&User::groupListSlot);
    QObject::connect(m_server,&API::getChannelListSignal,this,&User::channelListSlot);
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
        m_server->getMsgDm(this->m_token,dst);
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

void User::msgCountChannelSlot(const QString& argMsgCount,QJsonObject jObj)
{
    QRegularExpression re("-\\d+-");

    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argMsgCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        int num = numStr.toInt();


        // ignore this part idk whats happening
        // trying to make the map by bruteforcing the user
        QList<QString> keys = channelData.keys();
        for (int i = 0; i < num; ++i){
            QString blockIter = "block " + QString::number(i);
            QJsonValue blockVal = jObj.value(blockIter);
            if(blockVal.isObject()){
                QJsonObject blockObj = blockVal.toObject();
                QString src = blockObj.value("src").toString();
                QString dst = blockObj.value("dst").toString();
//                qDebug() << QThread::currentThreadId() << "num::msgCountDmSlot2 : ";
                foreach(const QString& key, keys){
                    if(src == key || dst == key){
                        channelData[key].first = num;
                        channelData[key].second = jObj;
//                        qDebug() << QThread::currentThreadId() << "num::msgCountDmSlot3 : " << directData[key].first << "\n";
                        break;
                    }
                }
            }
        }
        // end of ignore
    }else{
        qDebug() << "User::msgCountDmslot error";

    }

}

void User::msgCountDmSlot(const QString& argMsgCount,QJsonObject jObj)
{

//    qDebug() <<  QThread::currentThreadId() << ": user::msgCountDmslot\n";
    QRegularExpression re("-\\d+-");
    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argMsgCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        int num = numStr.toInt();

//        qDebug() << QThread::currentThreadId() << "num::msgCountDmSlot1 :" << num << "\n";
        // ignore this part idk whats happening
        // trying to make the map by bruteforcing the user
        QList<QString> keys = directData.keys();
        for (int i = 0; i < num; ++i){
            QString blockIter = "block " + QString::number(i);
            QJsonValue blockVal = jObj.value(blockIter);
            if(blockVal.isObject()){
                QJsonObject blockObj = blockVal.toObject();
                QString src = blockObj.value("src").toString();
                QString dst = blockObj.value("dst").toString();
//                qDebug() << QThread::currentThreadId() << "num::msgCountDmSlot2 : ";
                foreach(const QString& key, keys){
                    if(src == key || dst == key){
                        directData[key].first = num;
                        directData[key].second = jObj;
//                        qDebug() << QThread::currentThreadId() << "num::msgCountDmSlot3 : " << directData[key].first << "\n";
                        break;
                    }
                }
            }
        }
        // end of ignore
    }else{
        qDebug() << "User::msgCountDmslot error";

    }
}

void User::msgCountGroupSlot(const QString& argMsgCount,QJsonObject jObj)
{
    QRegularExpression re("-\\d+-");

    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argMsgCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        int num = numStr.toInt();


        // ignore this part idk whats happening
        // trying to make the map by bruteforcing the user
        QList<QString> keys = groupData.keys();
        for (int i = 0; i < num; ++i){
            QString blockIter = "block " + QString::number(i);
            QJsonValue blockVal = jObj.value(blockIter);
            if(blockVal.isObject()){
                QJsonObject blockObj = blockVal.toObject();
                QString src = blockObj.value("src").toString();
                QString dst = blockObj.value("dst").toString();
//                qDebug() << QThread::currentThreadId() << "num::msgCountDmSlot2 : ";
                foreach(const QString& key, keys){
                    if(src == key || dst == key){
                        groupData[key].first = num;
                        groupData[key].second = jObj;
//                        qDebug() << QThread::currentThreadId() << "num::msgCountDmSlot3 : " << directData[key].first << "\n";
                        break;
                    }
                }
            }
        }
        // end of ignore
    }else{
        qDebug() << "User::msgCountGroupSlot error";

    }
}

void User::userListSlot(const QString &argUserCount, QJsonObject jObj)
{
    QRegularExpression re("-\\d+-");

    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argUserCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        int num = numStr.toInt();
        userCount = num;
        for(int i = 0; i < num; ++i){
            QString blockIter = "block " + QString::number(i);
            QJsonValue blockVal = jObj.value(blockIter);
            if(blockVal.isObject()){
                QJsonObject blockObj = blockVal.toObject();
                QString src = blockObj.value("src").toString();
                if(userList.indexOf(src) == -1){
                    userList.push_back(src);
                }
            }
        }
    }
}

void User::groupListSlot(const QString &argGroupCount, QJsonObject jObj)
{
    QRegularExpression re("-\\d+-");

    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argGroupCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        int num = numStr.toInt();
        userCount = num;
        for(int i = 0; i < num; ++i){
            QString blockIter = "block " + QString::number(i);
            QJsonValue blockVal = jObj.value(blockIter);
            if(blockVal.isObject()){
                QJsonObject blockObj = blockVal.toObject();
                QString src = blockObj.value("group_name").toString();
                if(groupList.indexOf(src) == -1){
                    groupList.push_back(src);
                }
            }
        }
    }
}

void User::channelListSlot(const QString &argChannelCount, QJsonObject jObj)
{
    QRegularExpression re("-\\d+-");

    // Find the first match in the string
    QRegularExpressionMatch match = re.match(argChannelCount);
    if (match.hasMatch()) {
        // Extract the matched text
        QString matchText = match.captured(0);

        // Remove the hyphens from the matched text
        QString numStr = matchText.remove('-');

        // Convert the number string to an integer
        int num = numStr.toInt();
        userCount = num;
        for(int i = 0; i < num; ++i){
            QString blockIter = "block " + QString::number(i);
            QJsonValue blockVal = jObj.value(blockIter);
            if(blockVal.isObject()){
                QJsonObject blockObj = blockVal.toObject();
                QString src = blockObj.value("channel_name").toString();
                if(channelList.indexOf(src) == -1){
                    channelList.push_back(src);
                }
            }
        }
    }
}

int User::msgCountGetterDm(const QString& dst)
{
//    int num = directData[dst].first;
//    qDebug() << "num::msgCountGetterDm - " << num;
    return directData[dst].first;
}

int User::msgCountGetterChannel(const QString& dst)
{
    return channelData[dst].first;
}

int User::msgCountGetterGroup(const QString& dst)
{
    return groupData[dst].first;
}

int User::userCountGetter()
{
    return userCount;
}

int User::channelCountGetter()
{
    return channelCount;
}

int User::groupCountGetter()
{
    return groupCount;
}

QVector<QString> User::userListGetter()
{
    return userList;
}

QVector<QString> User::channelListGetter()
{
    return channelList;
}

QVector<QString> User::groupListGetter()
{
    return groupList;
}


QJsonObject User::msgContentGetterDm(const QString &dst)
{
    return directData[dst].second;
}

QJsonObject User::msgContentGetterChannel(const QString &dst)
{
    return channelData[dst].second;
}

QJsonObject User::msgContentGetterGroup(const QString &dst)
{
    return groupData[dst].second;
}

void User::msgCountDmReinit(const QString& dst)
{
//    qDebug() <<  QThread::currentThreadId() << ": user::msgCountdmReinit1" << directData[dst].first << "|";
    if(!directData[dst].first){
        directData[dst].first = 1;
//        qDebug() <<  QThread::currentThreadId() << ": user::msgCountdmReinit2" << directData[dst].first << "|";
    }
    m_server->getMsgDm(m_token,dst);
}

void User::msgCountGroupReinit(const QString &dst)
{
    if(!groupData[dst].first){
        groupData[dst].first = 1;
//        qDebug() <<  QThread::currentThreadId() << ": user::msgCountdmReinit2" << directData[dst].first << "|";
    }
    m_server->getMsgGroup(m_token,dst);
}

void User::msgCountChannelReinit(const QString &dst)
{
    if(!channelData[dst].first){
        channelData[dst].first = 1;
        //        qDebug() <<  QThread::currentThreadId() << ": user::msgCountdmReinit2" << directData[dst].first << "|";
    }
    m_server->getMsgChannel(m_token,dst);
}

void User::userListReinit()
{
    m_server->getUserList(m_token);
}

void User::channelListReinit()
{
    m_server->getChannelList(m_token);
}

void User::groupListReinit()
{
    m_server->getGroupList(m_token);
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
