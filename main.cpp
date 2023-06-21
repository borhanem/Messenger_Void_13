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
