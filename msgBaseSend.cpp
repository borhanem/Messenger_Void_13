#include "msgBaseSend.h"
#include "ui_msgBaseSend.h"

msgBase::msgBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::msgBase)
{
    ui->setupUi(this);
}

msgBase::~msgBase()
{
    delete ui;
}
