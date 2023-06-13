#include "loginpage.h"
#include "ui_loginpage.h"
#include <fstream>
LoginPage::LoginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginPage),
    mp_user(new User())
{
    ui->setupUi(this);
    register_ptr=new RegisterPage(this);
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    ui->login_result_lbl->clear();
    ui->login_pbn->setDefault(true);
    connect(mp_user,&User::Success,this,&::LoginPage::server_handler_on_success);
    connect(mp_user,&User::Failure,this,&::LoginPage::server_handler_on_failure);
    connect(register_ptr,&RegisterPage::RegisterSuccessfully,this,&LoginPage::autoLogin);
}

LoginPage::~LoginPage()
{
    delete ui;
}



void LoginPage::on_Register_pbn_clicked()
{
    this->hide();
    register_ptr->show();
    register_ptr->exec();
//    delete register_ptr;
//    register_ptr = new RegisterPage(this);
    this->show();
}


void LoginPage::on_login_pbn_clicked()
{
    ui->login_pbn->setDisabled(true);
    ui->username_led->setDisabled(true);
    ui->password_led->setDisabled(true);
    if(checkInput())
    {
          QString user_name = ui->username_led->text();
          QString pass_word = ui->password_led->text();
          mp_user->SetUserName(user_name);
          mp_user->SetPassWord(pass_word);
          mp_user->login();
          ui->login_result_lbl->setStyleSheet(" {  color : white; }");
          ui->login_result_lbl->setText("sending Request to server...");
    }
    else{
          ui->login_pbn->setDisabled(false);
          ui->username_led->setDisabled(false);
          ui->password_led->setDisabled(false);
    }

}

void LoginPage::server_handler_on_success()
{
//    QJsonDocument jDoc = QJsonDocument::fromJson(*data);
//    QJsonObject jObj = jDoc.object();
//    QString respond_code =  jObj.value("code").toString();
//    QString respond_message =jObj.value("message").toString();
//    QString respond_token = jObj.value("token").toString();
//    qDebug() << "from Server Handler: " << respond_token;

    ui->login_result_lbl->setStyleSheet("QLabel {  color : green; }");
    ui->login_result_lbl->setText("You Logged in Successfully");
    ui->login_pbn->setDisabled(false);
    ui->username_led->setDisabled(false);
    ui->password_led->setDisabled(false);
    //this->close();
}

void LoginPage::server_handler_on_failure(QString error)
{
    ui->login_result_lbl->setStyleSheet("QLabel {  color : red; }");
    ui->login_result_lbl->setText(error);
    ui->login_pbn->setDisabled(false);
    ui->username_led->setDisabled(false);
    ui->password_led->setDisabled(false);
}

void LoginPage::autoLogin(User *NewUser)
{
    ui->username_led->setText(NewUser->getUserName());
    ui->password_led->setText(NewUser->getPassword());
}

bool LoginPage::checkInput()
{
    bool isValid = true;
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    QString user_name = ui->username_led->text();
    QString pass_word = ui->password_led->text();
    if(user_name.isEmpty())
    {
        ui->usrname_warning_lbl->setText("<!> Username box is Empty");
        isValid = false;
    }
    if(pass_word.isEmpty())
    {
        ui->password_warning_lbl->setText("<!> Password box is Empty");
        isValid = false;
    }
    return isValid;
    }

