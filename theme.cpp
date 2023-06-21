#include "theme.h"

Theme::Theme()
{

}

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
