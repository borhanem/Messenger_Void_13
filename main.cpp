#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>
#include <QFile>

void changeStyle(QString num)
{
    QString css = read(QString(":/new/prefix1/Style/Style"  + num + ".css"));

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString d ="2";
    QString css = read(QString(":/new/prefix1/Style/Style"  + d + ".css"));

    if( css.length() > 0)
    {
        a.setStyleSheet(css);
    }

    LoginPage lpg;
    lpg.show();

    return a.exec();
}
