#include "createchannelpage.h"
#include "ui_createchannelpage.h"

CreateChannelPage::CreateChannelPage(const User* const user,QWidget *parent ) :
    QDialog(nullptr),
    ui(new Ui::CreateChannelPage),
    mp_user(user)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->result_lbl->clear();
    ui->stackedWidget->setCurrentIndex(0);
    ui->createchannel_pbn->setDefault(true);
    ui->tocreate_tbn->hide();
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
    ui->tojoin_tbn->setDisabled(true);
    QString input_channel_name = ui->channelname_led->text();
    if(input_channel_name.isEmpty())
    {
        ui->result_lbl->setText("<!>Channel Name cannot be empty<!>");
        ui->cancel_pbn->setDisabled(false);
        ui->createchannel_pbn->setDisabled(false);
        ui->channelname_led->setDisabled(false);
        ui->tojoin_tbn->setDisabled(false);
        return;
    }
    ui->result_lbl->setText("Sending request to server...");
    mp_user->createNewChat(input_channel_name,User::Channel);
}

void CreateChannelPage::success_on_create_channel()
{
    QString newChannelName=ui->channelname_led->text();
    ui->result_lbl->setText("Channel created Successfully");
    ui->cancel_pbn->setDisabled(false);
    ui->createchannel_pbn->setDisabled(false);
    ui->channelname_led->setDisabled(false);
    ui->tojoin_tbn->setDisabled(false);
    ui->tocreate_tbn->setDisabled(false);
    emit channelCreated(newChannelName);
    //this->close();
}

void CreateChannelPage::failure_on_create_channel(const QString& error)
{
    ui->result_lbl->setText(error);
    ui->cancel_pbn->setDisabled(false);
    ui->createchannel_pbn->setDisabled(false);
    ui->channelname_led->setDisabled(false);
    ui->tojoin_tbn->setDisabled(false);
    ui->tocreate_tbn->setDisabled(false);
}


void CreateChannelPage::on_tojoin_tbn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tocreate_tbn->show();
    ui->tojoin_tbn->hide();
    ui->joinchannel_pbn->setDefault(true);
}


void CreateChannelPage::on_tocreate_tbn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tocreate_tbn->hide();
    ui->tojoin_tbn->show();
    ui->createchannel_pbn->setDefault(true);
}


void CreateChannelPage::on_joinchannel_pbn_clicked()
{
    ui->cancel_pbn->setDisabled(true);
    ui->createchannel_pbn->setDisabled(true);
    ui->channelname_led->setDisabled(true);
    ui->tocreate_tbn->setDisabled(true);
    QString input_channel_name = ui->channelname_led->text();
    if(input_channel_name.isEmpty())
    {
        ui->result_lbl->setText("<!>Channnel Name cannot be empty<!>");
        ui->cancel_pbn->setDisabled(false);
        ui->createchannel_pbn->setDisabled(false);
        ui->channelname_led->setDisabled(false);
        ui->tocreate_tbn->setDisabled(false);
        return;
    }
    ui->result_lbl->setText("Sending request to server...");
    mp_user->joinChat(input_channel_name,User::Channel);

}

void CreateChannelPage::mousePressEvent(QMouseEvent* event)
{
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void CreateChannelPage::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void CreateChannelPage::on_Exit_pbn_clicked()
{
    this->close();
}

