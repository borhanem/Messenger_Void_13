#include "registerpage.h"
#include "ui_registerpage.h"

RegisterPage::RegisterPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
    ui->fname_warning_lbl->clear();
    ui->lnam_warning_lbl->clear();
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    ui->confirm_pass_warning_lbl->clear();
}

RegisterPage::~RegisterPage()
{
    delete ui;
}

void RegisterPage::on_register_pbn_clicked()
{
    checkInput();
}

int RegisterPage::checkInput()
{
    ui->fname_warning_lbl->clear();
    ui->lnam_warning_lbl->clear();
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    ui->confirm_pass_warning_lbl->clear();
    QString fname = ui->FName_led_2->text();
    QString lname = ui->LName_led_2->text();
    QString user_name = ui->usrname_led->text();
    QString pass = ui->pass_led_2->text();
    QString confirm_pass = ui->confirmpass_led->text();
    if(fname.isEmpty())
    {
        ui->fname_warning_lbl->setText("<!> First Name is Empty");
    }
    if(lname.isEmpty())
    {
        ui->lnam_warning_lbl->setText("<!> Last Name is Empty");
    }
    if(user_name.isEmpty())
    {
        ui->usrname_warning_lbl->setText("<!> User Name is Empty");
    }
    if(pass.isEmpty())
    {
        ui->password_warning_lbl->setText("<!> PassWord is Empty");
    }
    if(confirm_pass.isEmpty())
    {
        ui->confirm_pass_warning_lbl->setText("<!> Confirm is Empty");
    }
}

