#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include "registerpage.h"
#include <QWidget>
#include <QString>

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

private:
    int checkInput();
    Ui::LoginPage *ui;
    RegisterPage *register_ptr;
};

#endif // LOGINPAGE_H
