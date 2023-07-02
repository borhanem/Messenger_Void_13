#include "createprivatepage.h"
#include "ui_createprivatepage.h"
#include "message.h"
CreatePrivatePage::CreatePrivatePage(const User* const user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatePrivatePage),
    mp_user(user)
{
    ui->setupUi(this);
    ui->result_lbl->clear();
    ui->newprivate_pbn->setDefault(true);
    connect(mp_user,&User::SuccessOnSendMessage,this,&CreatePrivatePage::success_on_create_NewPrivate);
    connect(mp_user,&User::Failure,this,&CreatePrivatePage::failure_on_create_NewPrivate);
}

CreatePrivatePage::~CreatePrivatePage()
{
    delete ui;
}

void CreatePrivatePage::on_newprivate_pbn_clicked()
{
    ui->cancel_pbn->setDisabled(true);
    ui->newprivate_pbn->setDisabled(true);
    ui->username_led->setDisabled(true);
    QString input_user_name = ui->username_led->text();
    if(input_user_name.isEmpty())
    {
        ui->result_lbl->setText("<!>UserName cannot be empty<!>");
        ui->cancel_pbn->setDisabled(false);
        ui->newprivate_pbn->setDisabled(false);
        ui->username_led->setDisabled(false);
        return;
    }
    ui->result_lbl->setText("Sending request to server...");
    mp_user->sendMessage(Message(QString(""),mp_user->getUserName(),input_user_name),User::Private);
}


void CreatePrivatePage::on_cancel_pbn_clicked()
{
    this->close();
}

void CreatePrivatePage::success_on_create_NewPrivate()
{
    QString newPrivateName=ui->username_led->text();
    ui->result_lbl->setText("Private created Successfully");
    ui->cancel_pbn->setDisabled(false);
    ui->newprivate_pbn->setDisabled(false);
    ui->username_led->setDisabled(false);
    emit NewPrivate(newPrivateName);
    this->close();
}

void CreatePrivatePage::failure_on_create_NewPrivate(QString error)
{
    ui->result_lbl->setText(error);
    ui->cancel_pbn->setDisabled(false);
    ui->newprivate_pbn->setDisabled(false);
    ui->username_led->setDisabled(false);

}

