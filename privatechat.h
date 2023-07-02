#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QDialog>
#include "abstractchat.h"
#include <QVBoxLayout>
#include "workerrefresher.h"
#include "controllerrefresher.h"
namespace Ui {
class PrivateChat;
}

class PrivateChat : public QDialog , public AbstractChat
{
    Q_OBJECT

public:
    explicit PrivateChat(QString chatName,QWidget *parent = nullptr);
    ~PrivateChat();
    int saveToFile() override;
    int loadFromFile() override;
    void updateList() override;
private slots:
    void on_send_pbn_clicked();
    void success_on_send_message();
    void failure_on_send_message(QString Error);
    void Refresh_handler(QList<Message*>);
private:
    Ui::PrivateChat *ui;
    QVBoxLayout* messagesLayout;
    ControllerRefresher* controller;
};

#endif // PRIVATECHAT_H
