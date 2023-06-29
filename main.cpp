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
    QFile userLogFile("vdata/UserInfo/userLog.dat");
    QString css = read(loadTheme());
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
