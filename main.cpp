#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>
#include <QFile>
#include <fstream>
#include<QFrame>
QString loadTheme()
{
    QString i = ":/new/prefix1/Style/Style1.css";
    QDir settingDir;
    if(!settingDir.exists("settingInfo"))
    {
        settingDir.mkpath("settingInfo");
    }
    QFile logFile("settingInfo/settingLog.dat");
    if(!logFile.open(QIODevice::ReadOnly))
    {
        return i;
    }
    QDataStream data_dst(&logFile);
    data_dst >> i;
    i= ":/new/prefix1/Style/Style"+ i +".css";
    return i;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    std::ifstream iFile;
//    iFile.open("userLog.dat");
//    if(!iFile.is_open())
//    {
    QFile userLogFile("userLog.dat");
    QString css = read(loadTheme());

    MainWindow main;

    if( css.length() > 0)
    {
        a.setStyleSheet(css);
    }

    if(!userLogFile.exists())
    {


    MainWindow b;
    b.show();


        LoginPage lpg;
        lpg.show();
        lpg.exec();
    }
    else
    {
        main.show();
    }

    return a.exec();
}
