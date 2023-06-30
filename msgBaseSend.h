#ifndef MSGBASESEND_H
#define MSGBASESEND_H

#include <QDialog>
#include "message.h"
namespace Ui {
class msgBase;
}

class msgBaseSend : public QDialog,public Message
{
    Q_OBJECT

public:
    explicit msgBaseSend(const QString& txt,const QString& sender ="void",const QString& receiver="void",const QDateTime& time=QDateTime::currentDateTime(),QWidget *parent = nullptr);
    ~msgBaseSend();

private:
    Ui::msgBase *ui;
};

#endif // MSGBASESEND_H
