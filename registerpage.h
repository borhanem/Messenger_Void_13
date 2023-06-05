#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QDialog>
#include <QString>
#include "api.h"
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
    void server_handler_on_success(QByteArray* data);
    void server_handler_on_failure( QNetworkReply *reply);

private:
    Ui::RegisterPage *ui;
    void checkInput();
    API *m_server;
};

#endif // REGISTERPAGE_H
