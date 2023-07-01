#include "msgBaseSend.h"
#include "ui_msgBaseSend.h"

msgBaseSend::msgBaseSend(const QString& txt,const QString& sender ,const QString& receiver,const QDateTime& time,QWidget *parent) :
    QDialog(parent),
    Message(txt,sender,receiver,time),
    ui(new Ui::msgBase)
{
    ui->setupUi(this);
    ui->setupUi(this);
    ui->textBrowser->setText(this->m_body);
    ui->textBrowser->setAlignment(Qt::AlignRight);
    ui->Name->setText(this->m_sender);
    ui->Time->setText(this->m_time.time().toString());
}

msgBaseSend::~msgBaseSend()
{
    delete ui;
}
