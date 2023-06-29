#include "createchannelpage.h"
#include "ui_createchannelpage.h"

CreateChannelPage::CreateChannelPage(const User* const user,QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::CreateChannelPage),
    mp_user(user)
{
    ui->setupUi(this);
    ui->result_lbl->clear();
    ui->createchannel_pbn->setDefault(true);
    connect(mp_user,&User::Success,this,&CreateChannelPage::success_on_create_channel);
    connect(mp_user,&User::Failure,this,&CreateChannelPage::failure_on_create_channel);
}

CreateChannelPage::~CreateChannelPage()
{
    delete ui;
}

void CreateChannelPage::on_cancel_pbn_clicked()
{
    this->close();
}


void CreateChannelPage::on_createchannel_pbn_clicked()
{
    ui->cancel_pbn->setDisabled(true);
    ui->createchannel_pbn->setDisabled(true);
    ui->channelname_led->setDisabled(true);
    QString input_channel_name = ui->channelname_led->text();
    if(input_channel_name.isEmpty())
    {
        ui->result_lbl->setText("<!>Group Name cannot be empty<!>");
        ui->cancel_pbn->setDisabled(false);
        ui->createchannel_pbn->setDisabled(false);
        ui->channelname_led->setDisabled(false);
        return;
    }
    ui->result_lbl->setText("Sending request to server...");
    mp_user->createNewChat(input_channel_name,User::Channel);
}

void CreateChannelPage::success_on_create_channel()
{
    QString newChannelName=ui->channelname_led->text();
    ui->result_lbl->setText("Group created Successfully");
    ui->cancel_pbn->setDisabled(false);
    ui->createchannel_pbn->setDisabled(false);
    ui->channelname_led->setDisabled(false);
    emit channelCreated(newChannelName);
    this->close();
}

void CreateChannelPage::failure_on_create_channel(const QString& error)
{
    ui->result_lbl->setText(error);
    ui->cancel_pbn->setDisabled(false);
    ui->createchannel_pbn->setDisabled(false);
    ui->channelname_led->setDisabled(false);
}

