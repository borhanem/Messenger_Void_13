#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QDialog>
#include <QString>
#include "api.h"
#include "user.h"
namespace Ui {
class RegisterPage;
}

class RegisterPage : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = nullptr);
    ~RegisterPage();

private slots:
    void on_register_pbn_clicked();
    void server_handler_on_success();
    void server_handler_on_failure(QString error);

signals:
    void RegisterSuccessfully(User* new_user);
private:
    Ui::RegisterPage *ui;
    bool checkInput();
    User *mp_newuser;

};

#endif // REGISTERPAGE_H
