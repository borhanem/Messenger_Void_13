#include "msgBaseReceive.h"
#include "ui_msgBaseReceive.h"

msgBaseReceiver::msgBaseReceiver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::msgBaseReceiver)
{
    ui->setupUi(this);
}

msgBaseReceiver::~msgBaseReceiver()
{
    delete ui;
}
