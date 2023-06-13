#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "registerpage.h"
#include <QWidget>
#include <QString>
#include "api.h"
namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:

    void on_Register_pbn_clicked();

    void on_login_pbn_clicked();
    void server_handler_on_success(QByteArray* data);
    void server_handler_on_failure( QNetworkReply *reply);


    void on_Theme_1_clicked();

    void on_Theme_2_pbn_clicked();


    void on_Theme_3_pbn_clicked();

    void on_pushButton_clicked();

private:
    void checkInput();
    Ui::LoginPage *ui;
    RegisterPage *register_ptr;
    API *m_server;
};

QString read(QString path);

#endif // LOGINPAGE_H
