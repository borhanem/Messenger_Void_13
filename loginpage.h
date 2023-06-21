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


    void on_Theme_1_clicked();
    void on_Theme_2_pbn_clicked();
    void on_Theme_3_pbn_clicked();
    void on_pushButton_clicked();

private:
    bool checkInput();
    Ui::LoginPage *ui;
    RegisterPage *register_ptr;
    User *mp_user;
};


QString read(QString path);
int ThemeChange (QString i);
#endif // LOGINPAGE_H
