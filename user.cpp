#include "user.h"
#include "api.h"
#include <fstream>
#include <iostream>


User::User(QString userName, QString passWord, QString token, QObject *parent)
    : QObject{parent},m_username(userName),m_password(passWord),m_token(token)
{

}

void User::signUp(char* filePath)
{
    writeToFile(filePath);



    // do stuff later cuz this function is so stupid
}

void User::login(char* filePath)
{
    // implement logout if needed
    API loginApi("http://api.barafardayebehtar.ml:8080");
    ifstream fileExistCheck;
    fileExistCheck.open(filePath);
    if(fileExistCheck){
        loginApi.Register(m_username,m_password);
    }else{

    }
}

void User::logOut(char* filePath)
{
    std::remove(filePath);
}

void User::writeToFile(char *filePath)
{
    std::ofstream f1out;
    f1out.open(filePath,std::ios::binary);
    f1out.write((char*)this, sizeof(User));
    f1out.close();
}

void User::readFromFile(char *filePath)
{
    std::ifstream f1in;
    f1in.open(filePath,std::ios::binary);
    f1in.read((char*)this, sizeof(User));
    f1in.close();
}
