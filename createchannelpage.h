#ifndef CREATECHANNELPAGE_H
#define CREATECHANNELPAGE_H

#include <QDialog>
#include "user.h"
namespace Ui {
class CreateChannelPage;
}

class CreateChannelPage : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChannelPage(const User* const user,QWidget *parent = nullptr);
    ~CreateChannelPage();

private slots:
    void on_cancel_pbn_clicked();

    void on_createchannel_pbn_clicked();

    void success_on_create_channel();
    void failure_on_create_channel(const QString& error);
signals:
    void channelCreated(QString channelname);
private:
    Ui::CreateChannelPage *ui;
    const User* const mp_user;
};

#endif // CREATECHANNELPAGE_H
