#ifndef MSGBASERECEIVE_H
#define MSGBASERECEIVE_H

#include <QDialog>

namespace Ui {
class msgBaseReceiver;
}

class msgBaseReceiver : public QDialog
{
    Q_OBJECT

public:
    explicit msgBaseReceiver(QWidget *parent = nullptr);
    ~msgBaseReceiver();

private:
    Ui::msgBaseReceiver *ui;
};

#endif // MSGBASERECEIVE_H
