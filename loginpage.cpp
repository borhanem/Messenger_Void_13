#include "loginpage.h"
#include "ui_loginpage.h"
#include <QFile>
QString read(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        return in.readAll();
    }
    return "";
}

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    register_ptr = new RegisterPage();
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    ui->login_result_lbl->clear();
    m_server = new API("http://api.barafardayebehtar.ml:8080");
    connect(m_server,&API::Success,this,&::LoginPage::server_handler_on_success);
    connect(m_server,&API::Failure,this,&::LoginPage::server_handler_on_failure);
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
    this->show();
}


void LoginPage::on_login_pbn_clicked()
{
    checkInput();
}

void LoginPage::server_handler_on_success(QByteArray *data)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(*data);
    QJsonObject jObj = jDoc.object();
    QString respond_code =  jObj.value("code").toString();
    QString respond_message =jObj.value("message").toString();
    if(respond_code =="200")
    {
        ui->login_result_lbl->setStyleSheet("QLabel {  color : green; }");
    }
    else
    {
        ui->login_result_lbl->setStyleSheet("QLabel {  color : red; }");
    }
    ui->login_result_lbl->setText(respond_message);
    ui->login_pbn->setDisabled(false);
}

void LoginPage::server_handler_on_failure(QNetworkReply *reply)
{
    ui->login_result_lbl->setStyleSheet("QLabel {  color : red; }");
    ui->login_result_lbl->setText(reply->errorString());
    ui->login_pbn->setDisabled(false);
}

void LoginPage::checkInput()
{
    bool valid = true;
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    QString user_name = ui->username_led->text();
    QString pass_word = ui->password_led->text();
    if(user_name.isEmpty())
    {
        ui->usrname_warning_lbl->setText("<!> Username box is Empty");
        valid = false;
    }
    if(pass_word.isEmpty())
    {
        ui->password_warning_lbl->setText("<!> Password box is Empty");
        valid = false;
    }
    if(valid)
    {
    ui->login_pbn->setDisabled(true);
    m_server->Login(user_name,pass_word);
    ui->login_result_lbl->setStyleSheet(" {  color : white; }");
    ui->login_result_lbl->setText("sending Request to server...");
    }
    }






void LoginPage::on_Theme_1_clicked()
{
    QString css = read(QString(":/new/prefix1/Style/Style1.css"));

    if( css.length() > 0)
    {
    ((QApplication*)QApplication::instance())->setStyleSheet(css);
    }
}




void LoginPage::on_Theme_2_pbn_clicked()
{
    QString css = read(QString(":/new/prefix1/Style/Style2.css"));

    if( css.length() > 0)
    {
    ((QApplication*)QApplication::instance())->setStyleSheet(css);
    }
}





void LoginPage::on_Theme_3_pbn_clicked()
{
    QString css = read(QString(":/new/prefix1/Style/Style3.css"));

    if( css.length() > 0)
    {
    ((QApplication*)QApplication::instance())->setStyleSheet(css);
    }
}


void LoginPage::on_pushButton_clicked()
{
    QString css = read(QString(":/new/prefix1/Style/Style4.css"));

    if( css.length() > 0)
    {
    ((QApplication*)QApplication::instance())->setStyleSheet(css);
    }
}

