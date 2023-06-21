#ifndef THEME_H
#define THEME_H
#include <iostream>
#include <QString>
#include <QFile>
#include <QDir>
#include <fstream>
#include <QDialog>

class Theme
{
public:

    Theme();
};

QString read(QString path);

int ThemeChange (QString i);

QString loadTheme();
#endif // THEME_H
