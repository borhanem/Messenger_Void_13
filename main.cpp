#include "mainwindow.h"
#include "loginpage.h"
#include "theme.h"
#include <QApplication>
#include <QFile>
#include <fstream>
#include<QFrame>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon icon(":/new/prefix1/Style/VoidMSG main.ico");
    a.setWindowIcon(icon);


//    std::ifstream iFile;
//    iFile.open("userLog.dat");
//    if(!iFile.is_open())
//    {
    QFile userLogFile("vdata/UserInfo/userLog.dat");
    QString css = read(loadTheme());
//    qDebug() <<  QThread::currentThreadId() << ": main.cpp\n";
// what do we do for first chat

    if( css.length() > 0)
    {
        a.setStyleSheet(css);
    }
    User sample;
//    sample.loadFromFile();
//    sample.getMsg("salam",User::Group);
//    msgBaseReceiver m;
//    m.show();
//    msgBase n;
//    n.show();

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
