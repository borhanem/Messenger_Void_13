#include "msgBaseReceive.h"
#include "ui_msgBaseReceive.h"

msgBaseReceiver::msgBaseReceiver(const QString& txt,const QString& sender,const QString& receiver,const QDateTime& time,QWidget *parent) :
    QDialog(parent),
    Message(txt,sender,receiver,time),
    ui(new Ui::msgBaseReceiver)
{
    ui->setupUi(this);
    ui->msg_index->setText(this->m_body);
    ui->Name->setText(this->m_sender);
    ui->Time->setText(this->m_time.time().toString());
}

msgBaseReceiver::~msgBaseReceiver()
{
    delete ui;
}
