#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "registerpage.h"
#include <QDialog>
#include <QString>
#include "user.h"
#include "theme.h"
#include <QMouseEvent>
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
    void registerPage_handler(int i);
    void autoLogin(User* NewUser);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
 //   void autoLogout(User user);
    void on_Theme_1_clicked();
    void on_Theme_2_pbn_clicked();
    void on_Theme_3_pbn_clicked();
    void on_pushButton_clicked();
    void on_Exit_pbn_clicked();

signals:
   // void needLogout(User user);
private:
    QPoint dragPosition;
    bool checkInput();
    Ui::LoginPage *ui;
    RegisterPage *register_ptr;
    User *mp_user;
};


#endif // LOGINPAGE_H
