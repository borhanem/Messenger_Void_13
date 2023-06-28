#include "creategrouppage.h"
#include "ui_creategrouppage.h"

CreateGroupPage::CreateGroupPage(const User* const user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGroupPage),
    mp_user(user)
{
    ui->setupUi(this);
    ui->result_lbl->clear();
    ui->creategroup_pbn->setDefault(true);
    connect(mp_user,&User::Success,this,&CreateGroupPage::success_on_create_group);
    connect(mp_user,&User::Failure,this,&CreateGroupPage::failure_on_create_group);
}

CreateGroupPage::~CreateGroupPage()
{
    delete ui;
    qDebug("createGroupPage destructor!");
}

void CreateGroupPage::on_cancel_pbn_clicked()
{
    this->close();
}


void CreateGroupPage::on_creategroup_pbn_clicked()
{
    ui->cancel_pbn->setDisabled(true);
    ui->creategroup_pbn->setDisabled(true);
    ui->groupname_led->setDisabled(true);
    QString input_group_name = ui->groupname_led->text();
    if(input_group_name.isEmpty())
    {
        ui->result_lbl->setText("<!>Group Name cannot be empty<!>");
        ui->cancel_pbn->setDisabled(false);
        ui->creategroup_pbn->setDisabled(false);
        ui->groupname_led->setDisabled(false);
        return;
    }
    ui->result_lbl->setText("Sending request to server...");
    mp_user->createNewChat(input_group_name,User::Group);

}

void CreateGroupPage::success_on_create_group()
{
    QString newGroupName=ui->groupname_led->text();
    ui->result_lbl->setText("Group created Successfully");
    ui->cancel_pbn->setDisabled(false);
    ui->creategroup_pbn->setDisabled(false);
    ui->groupname_led->setDisabled(false);
    emit NewGroup(newGroupName);
    this->close();
}

void CreateGroupPage::failure_on_create_group(const QString &error)
{
    ui->result_lbl->setText(error);
    ui->cancel_pbn->setDisabled(false);
    ui->creategroup_pbn->setDisabled(false);
    ui->groupname_led->setDisabled(false);
}

