#ifndef CHANNELCHAT_H
#define CHANNELCHAT_H

#include <QDialog>
#include <QVBoxLayout>
#include "workerrefresher.h"
#include "abstractchat.h"
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
private:
    Ui::ChannelChat *ui;
    QVBoxLayout* messagesLayout;
    WorkerRefresher* worker;

//    refresherChannel* refresher;
};

#endif // CHANNELCHAT_H
