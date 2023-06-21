#include "registerpage.h"
#include "ui_registerpage.h"

RegisterPage::RegisterPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterPage),
    mp_newuser(new User())
{
    ui->setupUi(this);
    ui->fname_warning_lbl->clear();
    ui->lnam_warning_lbl->clear();
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    ui->confirm_pass_warning_lbl->clear();
    setWindowFlags(Qt::FramelessWindowHint);

    ui->register_result_lbl->clear();
    ui->register_pbn->setDefault(true);
    connect(mp_newuser,&User::Success,this,&::RegisterPage::server_handler_on_success);
    connect(mp_newuser,&User::Failure,this,&::RegisterPage::server_handler_on_failure);

}

void RegisterPage::mousePressEvent(QMouseEvent* event)
{
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void RegisterPage::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

RegisterPage::~RegisterPage()
{
    delete ui;
    delete mp_newuser;
}

void RegisterPage::on_register_pbn_clicked()
{

    ui->register_pbn->setDisabled(true);
    ui->FName_led_2->setDisabled(true);
    ui->LName_led_2->setDisabled(true);
    ui->usrname_led->setDisabled(true);
    ui->pass_led_2->setDisabled(true);
    ui->confirmpass_led->setDisabled(true);
    if(checkInput())
    {
        QString user_name = ui->usrname_led->text();
        QString pass = ui->pass_led_2->text();
        ui->register_result_lbl->setStyleSheet(" {  color : white; }");
        ui->register_result_lbl->setText("Requesting the server...");
        mp_newuser->SetUserName(user_name);
        mp_newuser->SetPassWord(pass);
        mp_newuser->Register();

    }
    else{
        ui->register_pbn->setDisabled(false);
        ui->FName_led_2->setDisabled(false);
        ui->LName_led_2->setDisabled(false);
        ui->usrname_led->setDisabled(false);
        ui->pass_led_2->setDisabled(false);
        ui->confirmpass_led->setDisabled(false);
    }
}

bool RegisterPage::checkInput()
{
    bool isValid=true;
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
        isValid=false;
    }
    if(lname.isEmpty())
    {
        ui->lnam_warning_lbl->setText("<!> Last Name is Empty");
        isValid=false;
    }
    if(user_name.isEmpty())
    {
        ui->usrname_warning_lbl->setText("<!> User Name is Empty");
        isValid=false;
    }
    if(pass.isEmpty())
    {
        ui->password_warning_lbl->setText("<!> PassWord is Empty");
        isValid=false;
    }
    if(confirm_pass.isEmpty())
    {
        ui->confirm_pass_warning_lbl->setText("<!> Confirm is Empty");
        isValid=false;
    }
    if(confirm_pass != pass)
    {
        ui->confirm_pass_warning_lbl->setText("<!> Doesn't match");
        isValid=false;
    }
    return isValid;
}

void RegisterPage::server_handler_on_success()
{

    ui->register_result_lbl->setStyleSheet("QLabel {  color : green; }");
    ui->register_result_lbl->setText("You Registered Successfuly!");
    ui->register_pbn->setDisabled(false);
    ui->FName_led_2->setDisabled(false);
    ui->LName_led_2->setDisabled(false);
    ui->usrname_led->setDisabled(false);
    ui->pass_led_2->setDisabled(false);
    ui->confirmpass_led->setDisabled(false);
    emit RegisterSuccessfully(mp_newuser);
    this->close();

}

void RegisterPage::server_handler_on_failure(QString error)
{
    ui->register_result_lbl->setStyleSheet("QLabel {  color : red; }");
    ui->register_result_lbl->setText(error);
    ui->register_pbn->setDisabled(false);
    ui->FName_led_2->setDisabled(false);
    ui->LName_led_2->setDisabled(false);
    ui->usrname_led->setDisabled(false);
    ui->pass_led_2->setDisabled(false);
    ui->confirmpass_led->setDisabled(false);
}
