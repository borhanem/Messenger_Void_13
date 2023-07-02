#ifndef CREATECHANNELPAGE_H
#define CREATECHANNELPAGE_H

#include <QDialog>
#include "user.h"
#include <QMouseEvent>

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

    void on_tojoin_tbn_clicked();

    void on_tocreate_tbn_clicked();

    void on_joinchannel_pbn_clicked();

    void on_Exit_pbn_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void channelCreated(QString channelname);
private:
    QPoint dragPosition;
    Ui::CreateChannelPage *ui;
    const User* const mp_user;

};

#endif // CREATECHANNELPAGE_H
