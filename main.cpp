#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPage lpg;
    lpg.show();

    return a.exec();
}
