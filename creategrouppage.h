#ifndef CREATEGROUPPAGE_H
#define CREATEGROUPPAGE_H

#include <QDialog>
#include "user.h"
namespace Ui {
class CreateGroupPage;
}

class CreateGroupPage : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGroupPage(const User* const user = nullptr,QWidget *parent = nullptr);
    ~CreateGroupPage();

private slots:
    void on_cancel_pbn_clicked();

    void on_creategroup_pbn_clicked();

    void success_on_create_group();
    void failure_on_create_group(const QString&);
private:
    Ui::CreateGroupPage *ui;
    const User* const mp_user;
};

#endif // CREATEGROUPPAGE_H
