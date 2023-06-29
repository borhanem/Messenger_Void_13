#include "mainwindow.h"
#include "loginpage.h"
#include "theme.h"
#include <QApplication>
#include <QFile>
#include <fstream>
#include<QFrame>
#include "refresherDirect.h".h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    std::ifstream iFile;
//    iFile.open("userLog.dat");
//    if(!iFile.is_open())
//    {
    QFile userLogFile("vdata/UserInfo/userLog.dat");
    QString css = read(loadTheme());
    qDebug() <<  QThread::currentThreadId() << ": main.cpp\n";
    User* nUser = new User(QString("receive"),QString::number(1234),QString("dea1fd09fab4c03974c2b0b2e0e37b59"),QString("vdata/UserInfo/userLog.dat"));
    refresherDirect* tr1 = new refresherDirect(QString("send"),nUser);
    // create user class in new thread not in constructor
    tr1->start();
    if( css.length() > 0)
    {
        a.setStyleSheet(css);
    }

    if(!userLogFile.exists())
    {
        LoginPage* lpg = new LoginPage();
        lpg->open();
        // delete lpg;
    }
    else
    {
        MainWindow* main = new MainWindow();
        main->show();
    }

    return a.exec();
}

// User::msgCountDmSlot not running despite signal being connected
