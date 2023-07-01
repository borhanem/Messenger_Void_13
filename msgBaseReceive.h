#ifndef MSGBASERECEIVE_H
#define MSGBASERECEIVE_H

#include <QDialog>
#include "message.h"
namespace Ui {
class msgBaseReceiver;
}

class msgBaseReceiver :  public QDialog, public Message
{
    Q_OBJECT

public:
    explicit msgBaseReceiver(const QString& txt,const QString& sender ="void",const QString& receiver="void",const QDateTime& time=QDateTime::currentDateTime(),QWidget *parent = nullptr);
    ~msgBaseReceiver();

private:
    Ui::msgBaseReceiver *ui;
};

#endif // MSGBASERECEIVE_H
