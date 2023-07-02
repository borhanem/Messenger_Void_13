#include "loginpage.h"
#include "mainwindow.h"
#include "ui_loginpage.h"
#include <fstream>
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
    QDialog(nullptr),
    ui(new Ui::LoginPage),
    register_ptr(NULL),
    mp_user(new User())
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
//    register_ptr=new RegisterPage(this);
    ui->usrname_warning_lbl->clear();
    ui->password_warning_lbl->clear();
    ui->login_result_lbl->clear();
    ui->login_pbn->setDefault(true);
    connect(mp_user,&User::Success,this,&::LoginPage::server_handler_on_success);
    connect(mp_user,&User::Failure,this,&::LoginPage::server_handler_on_failure);
}

void LoginPage::mousePressEvent(QMouseEvent* event)
{
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void LoginPage::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

LoginPage::~LoginPage()
{
    delete ui;
    delete mp_user;
    delete register_ptr;
}



void LoginPage::on_Register_pbn_clicked()
{
    this->hide();
    if(register_ptr == NULL)
    {
    register_ptr=new RegisterPage(this);
    connect(register_ptr,&RegisterPage::RegisterSuccessfully,this,&LoginPage::autoLogin);
    connect(register_ptr,&RegisterPage::finished,this,&LoginPage::registerPage_handler);
    }
    register_ptr->open();
//    delete register_ptr;
//    register_ptr = new RegisterPage(this);
//    this->show();
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
    MainWindow* mainptr = new MainWindow();
    mainptr->show();
    this->deleteLater();
    this->close();
}

void LoginPage::server_handler_on_failure(QString error)
{
    ui->login_result_lbl->setStyleSheet("QLabel {  color : red; }");
    ui->login_result_lbl->setText(error);
    ui->login_pbn->setDisabled(false);
    ui->username_led->setDisabled(false);
    ui->password_led->setDisabled(false);
//    if(error == "Try Again")
//    {
//          User temp(this->mp_user->getUserName(),this->mp_user->getPassword());
//          temp.logOut();
//    }
}

void LoginPage::registerPage_handler(int i)
{
    this->show();
    ui->login_pbn->setDefault(true);
}

void LoginPage::autoLogin(User *NewUser)
{
    ui->username_led->setText(NewUser->getUserName());
    ui->password_led->setText(NewUser->getPassword());
}

//void LoginPage::autoLogout(User user)
//{
//    user.logOut();
//}

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

int ThemeChange (QString i)
{
    QString css = read(QString(":/new/prefix1/Style/Style"+ i +".css"));

    if( css.length() > 0)
    {
        ((QApplication*)QApplication::instance())->setStyleSheet(css);
        QDir settingDir;
        if(!settingDir.exists("vdata/settingInfo"))
        {
            settingDir.mkpath("vdata/settingInfo");
        }
        QFile logFile("vdata/settingInfo/settingLog.dat");
        if(!logFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            return -1;
        }
        QDataStream data_dst(&logFile);
        data_dst << i;
        logFile.close();
        return 0;
    }
    return 1;
}

void LoginPage::on_Theme_1_clicked()
{
        ThemeChange("1");
}



void LoginPage::on_Theme_2_pbn_clicked()
{
    ThemeChange("2");
}



void LoginPage::on_Theme_3_pbn_clicked()
{
      ThemeChange("3");
}


void LoginPage::on_pushButton_clicked()
{
        ThemeChange("4");
}


void LoginPage::on_Exit_pbn_clicked()
{
    this->close();
}

