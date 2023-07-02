#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QDialog>
#include "abstractchat.h"
#include <QVBoxLayout>
#include "refreshergroup.h"
#include "workerrefresher.h"
#include <QMouseEvent>
namespace Ui {
class GroupChat;
}

class GroupChat : public QDialog , public AbstractChat
{
    Q_OBJECT

public:
    explicit GroupChat(QString chatName,QWidget *parent = nullptr);
    ~GroupChat();
    int saveToFile() override;
    int loadFromFile() override;
    void updateList() override;
private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void on_send_pbn_clicked();
    void success_on_send_message();
    void failure_on_send_message(QString Error);
    void on_refresh_pbn_clicked();
    void Refresh_handler(QList<Message*>);
    void on_Exit_pbn_clicked();

private:
    QPoint dragPosition;
    QPoint m_windowPos;
    QPoint m_mousePressPos;
    Ui::GroupChat *ui;
    QVBoxLayout* messagesLayout;
    WorkerRefresher* worker;

    //refresherGroup* refresher;
};

#endif // GROUPCHAT_H
