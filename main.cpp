#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>
#include <QFile>

QString read(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        return in.readAll();
    }
    return "";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString d ="1";
    QString css = read(QString(":/new/prefix1/Style/Style"  + d + ".css"));

    if( css.length() > 0)
    {
        a.setStyleSheet(css);
    }

    LoginPage lpg;
    lpg.show();

    return a.exec();
}
