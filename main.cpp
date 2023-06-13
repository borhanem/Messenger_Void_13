#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>
#include <QFile>
#include <fstream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    std::ifstream iFile;
//    iFile.open("userLog.dat");
//    if(!iFile.is_open())
//    {
    QString css = read(":/new/prefix1/Style/Style1.css");

    if( css.length() > 0)
    {
        a.setStyleSheet(css);
    }
        LoginPage lpg;
        lpg.show();
        lpg.exec();
//    }
//    else
//    {
//        MainWindow main;
//        iFile.close();
//        main.show();
//    }

    return a.exec();
}
