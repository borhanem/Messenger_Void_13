#include "user.h"
#include <fstream>
#include <iostream>
#include <string>
#include <QRegularExpression>
User::User() : m_UserLogFilePath("UserInfo/userLog.dat"),
               m_username ("VoidUser"),
               m_password("123456789"),
               m_token("borhan81alireza82mahta83"),
               m_server(new API("http://api.barafardayebehtar.ml:8080"))
{
    QObject::connect(m_server,&API::SuccessOnRegister,this,&User::server_handler_on_Register);
    QObject::connect(m_server,&API::SuccessOnLogin,this,&User::server_handler_on_Login);
    QObject::connect(m_server,&API::SuccessOnLogout,this,&User::server_handler_on_Logout);
    QObject::connect(m_server,&API::FailureOnRegister,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogin,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogout,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnGetMsg,this,&User::server_handler_on_failure); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalDM,this,&User::msgCountDmSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalChannel,this,&User::msgCountChannelSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalGroup,this,&User::msgCountGroupSlot); // new entry
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
    QObject::connect(m_server,&API::FailureOnRegister,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogin,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnLogout,this,&User::server_handler_on_failure);
    QObject::connect(m_server,&API::FailureOnGetMsg,this,&User::server_handler_on_failure); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalDM,this,&User::msgCountDmSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalChannel,this,&User::msgCountChannelSlot); // new entry
    QObject::connect(m_server,&API::getMsgCountSignalGroup,this,&User::msgCountGroupSlot); // new entry

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
    if(!LogDir.exists("UserInfo"))
    {
        LogDir.mkpath("UserInfo");
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

void User::msgCountChannelSlot(QString argMsgCount)
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

        msgCountChannel = num;
    }else{
        qDebug() << "User::msgCountDmSlot error";

    }
}

void User::msgCountDmSlot(QString argMsgCount)
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

        msgCountDm = num;
    }else{
        qDebug() << "User::msgCountDmslot error";

    }
}

void User::msgCountGroupSlot(QString argMsgCount)
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

        msgCountGroup = num;
    }else{
        qDebug() << "User::msgCountGroupSlot error";

    }
}

int User::msgCountGetterDm()
{
    return msgCountDm;
}

int User::msgCountGetterChannel()
{
    return msgCountChannel;
}

int User::msgCountGetterGroup()
{
    return msgCountGroup;
}

void User::allMsgCountsReInit(QString dst)
{
    m_server->getMsgChannel(m_token,dst);
    m_server->getMsgDM(m_token,dst);
    m_server->getMsgGroup(m_token,dst);
}

void User::server_handler_on_Register()
{
/*    if(saveToFile()){
        emit Failure("Can't Save the User data");
    }
    else*{ }*/
        emit Success();

}

void User::server_handler_on_Login(QString token)
{
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
    emit Success();
}

void User::server_handler_on_failure(QString error)
{
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
