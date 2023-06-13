#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "registerpage.h"
#include <QDialog>
#include <QString>
#include "user.h"
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
    void server_handler_on_success();
    void server_handler_on_failure(QString error);
    void autoLogin(User* NewUser);
private:
    bool checkInput();
    Ui::LoginPage *ui;
    RegisterPage *register_ptr;
    User *mp_user;
};

#endif // LOGINPAGE_H
