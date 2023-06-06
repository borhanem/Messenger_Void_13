#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "registerpage.h"
#include <QDialog>
#include <QString>
#include "api.h"
namespace Ui {
class LoginPage;
}

class LoginPage : public QDialog
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
private:
    void checkInput();
    Ui::LoginPage *ui;
    RegisterPage *register_ptr;
    API *m_server;
};

#endif // LOGINPAGE_H
