#ifndef MSGBASESEND_H
#define MSGBASESEND_H

#include <QDialog>

namespace Ui {
class msgBase;
}

class msgBase : public QDialog
{
    Q_OBJECT

public:
    explicit msgBase(QWidget *parent = nullptr);
    ~msgBase();

private:
    Ui::msgBase *ui;
};

#endif // MSGBASESEND_H
