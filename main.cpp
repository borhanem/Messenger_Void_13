#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>
#include <fstream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::ifstream iFile;
    char path[] = "userLog.dat";
    iFile.open(path);
    if(!iFile.is_open())
    {
    LoginPage lpg;
    lpg.show();
    lpg.exec();
    }
    iFile.close();
    MainWindow myMain;
    myMain.show();
    return a.exec();
}
