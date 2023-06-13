#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>
#include <fstream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    std::ifstream iFile;
//    iFile.open("userLog.dat");
//    if(!iFile.is_open())
//    {
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
