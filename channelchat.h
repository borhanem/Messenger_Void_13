#ifndef CHANNELCHAT_H
#define CHANNELCHAT_H

#include <QDialog>
#include <QVBoxLayout>
#include "controllerrefresher.h"
#include "workerrefresher.h"
#include "abstractchat.h"
#include <QMouseEvent>
//#include "refresherchannel.h"
namespace Ui {
class ChannelChat;
}

class ChannelChat : public QDialog , public AbstractChat
{
    Q_OBJECT

public:
    explicit ChannelChat(QString chatName,QWidget *parent = nullptr);
    ~ChannelChat();
    virtual int loadFromFile()override;
    virtual int saveToFile()override;
    void updateList()override;
private slots:
    void on_send_pbn_clicked();
    void success_on_send_message();
    void failure_on_send_message(QString error);
    void Refresh_Handler(QList<Message*>);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void on_Exit_pbn_clicked();

private:
        QPoint dragPosition;
    Ui::ChannelChat *ui;
    QVBoxLayout* messagesLayout;
    ControllerRefresher* controller;

//    refresherChannel* refresher;
};

#endif // CHANNELCHAT_H
