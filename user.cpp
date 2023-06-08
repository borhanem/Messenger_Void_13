#include "user.h"
#include <fstream>
#include <iostream>
#include <string>

User::User() : m_username ("afasdfasf"),
               m_password("adfasfdasdf"),
               m_token("afasfdasdf")
{



}

User::User(QString userName, QString passWord, QString token, QObject *parent)
    : QObject{parent}
{
    strcpy(m_username,userName.toStdString().c_str());
    strcpy(m_password,passWord.toStdString().c_str());
    strcpy(m_token,token.toStdString().c_str());
}

void User::Register(char* filePath)
{
    writeToFile(filePath);



    // do stuff later cuz this function is so stupid
}

void User::login(char* filePath)
{
    writeToFile(filePath);

}

void User::logOut(char* filePath)
{
    std::remove(filePath);
}

void User::loadFromFile(char *filePath)
{
    User temp;
    std::ifstream iFile;
    iFile.open(filePath);
    if(iFile.is_open())
    {
        iFile.read((char*)this,sizeof(temp));
//        this->m_username = temp.m_username;
//        this->m_password = temp.m_password;
//        this->m_token = temp.m_token;
        qDebug() <<"From loadFromFile: "<< this->m_username << this->m_password << this->m_token << Qt::endl;
        iFile.close();
    }
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

void User::writeToFile(char *filePath)
{
    std::ofstream f1out;
    User temp(m_username,m_password,m_token);
    qDebug() << "from write to file: " << temp.getUserName() << " " << temp.getPassword() << " "<< temp.getToken();
    f1out.open(filePath);
    if(f1out.is_open())
    {
    f1out.write((char*)&temp, sizeof(temp));
    f1out.close();
    }
}

void User::readFromFile(char *filePath)
{
    std::ifstream f1in;
    f1in.open(filePath);
    f1in.read((char*)this, sizeof(User));
    f1in.close();
}
