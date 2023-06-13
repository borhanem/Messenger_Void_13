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
    ui->register_result_lbl->clear();
    m_server = new API("http://api.barafardayebehtar.ml:8080");
    connect(m_server,&API::Success,this,&::RegisterPage::server_handler_on_success);
    connect(m_server,&API::Failure,this,&::RegisterPage::server_handler_on_failure);
}

RegisterPage::~RegisterPage()
{
    delete ui;
}

void RegisterPage::on_register_pbn_clicked()
{

    checkInput();
}

void RegisterPage::checkInput()
{
    bool isvalid=true;
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
        isvalid=false;
    }
    if(lname.isEmpty())
    {
        ui->lnam_warning_lbl->setText("<!> Last Name is Empty");
        isvalid=false;
    }
    if(user_name.isEmpty())
    {
        ui->usrname_warning_lbl->setText("<!> User Name is Empty");
        isvalid=false;
    }
    if(pass.isEmpty())
    {
        ui->password_warning_lbl->setText("<!> PassWord is Empty");
        isvalid=false;
    }
    if(confirm_pass.isEmpty())
    {
        ui->confirm_pass_warning_lbl->setText("<!> Confirm is Empty");
        isvalid=false;
    }
    if(confirm_pass != pass)
    {
        ui->confirm_pass_warning_lbl->setText("<!> Doesn't match");
        isvalid=false;
    }
    if(isvalid)
    {
            ui->register_pbn->setDisabled(true);
        ui->register_result_lbl->setStyleSheet(" {  color : white; }");
        ui->register_result_lbl->setText("Requesting the server...");
        m_server->Register(user_name,pass);
    }
}

void RegisterPage::server_handler_on_success(QByteArray *data)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(*data);
    QJsonObject jObj = jDoc.object();
    QString respond_code =  jObj.value("code").toString();
    QString respond_message =jObj.value("message").toString();
    if(respond_code =="200")
    {
        ui->register_result_lbl->setStyleSheet("QLabel {  color : green; }");
    }
    else
    {
        ui->register_result_lbl->setStyleSheet("QLabel {  color : red; }");
    }
    ui->register_result_lbl->setText(respond_message);
    ui->register_pbn->setDisabled(false);

}
void RegisterPage::firstTimeRegisterFileMaker()
{

}

void RegisterPage::server_handler_on_failure(QNetworkReply *reply)
{
    ui->register_result_lbl->setStyleSheet("QLabel {  color : red; }");
    ui->register_result_lbl->setText(reply->errorString());
    ui->register_pbn->setDisabled(false);
}
