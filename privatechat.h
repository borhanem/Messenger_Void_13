#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QDialog>
#include "abstractchat.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include "workerrefresher.h"
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
    void on_Exit_pbn_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint dragPosition;
    Ui::PrivateChat *ui;
    QVBoxLayout* messagesLayout;
    WorkerRefresher* worker;
};

#endif // PRIVATECHAT_H
