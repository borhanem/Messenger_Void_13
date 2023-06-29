#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QList>
#include "qlistwidget.h"
#include "user.h"
#include <QDateTime>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QPropertyAnimation>
#include <abstractchat.h>
#include "groupchat.h"
#include "loginpage.h"
#include "creategrouppage.h"
#include "createchannelpage.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool setting_show;

private slots:

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void on_logout_pbn_clicked();

    void on_Theme_1_clicked();

    void on_Theme_2_pbn_clicked();

    void on_pushButton_clicked();

    void on_Exit_pbn_clicked();

    void on_Theme_3_pbn_clicked();

    void on_toolButton_clicked(bool checked);

    void logoutUser();

    void on_createGroup_pbn_clicked();

//    void delete_createGroupPage();

    void handler_on_NewGroup(QString newGroupName);
    void handler_on_NewChannel(QString newChannelName);
    void on_chats_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_newchannel_pbn_clicked();


    void on_Add_tbn_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    User* mp_user;
    QList<AbstractChat*> mp_ChatList;
    CreateGroupPage* mp_cgp;



    QPoint dragPosition;
    QPoint m_windowPos;
    QPoint m_mousePressPos;
    QPropertyAnimation* user_lbl_hide;
    QPropertyAnimation* user_led_hide;
    QPropertyAnimation* pass_lbl_hide;
    QPropertyAnimation* pass_led_hide;
    QPropertyAnimation* token_lbl_hide;
    QPropertyAnimation* token_led_hide;
    QPropertyAnimation* logout_hide;
    QPropertyAnimation* color_1_show;
    QPropertyAnimation* color_2_show;
    QPropertyAnimation* color_3_show;
    QPropertyAnimation* color_4_show;
    QPropertyAnimation* color_1_hide;
    QPropertyAnimation* color_2_hide;
    QPropertyAnimation* color_3_hide;
    QPropertyAnimation* color_4_hide;
    QPropertyAnimation* info_lbl;
    QPropertyAnimation* link_lbl;
    QPropertyAnimation* setting_pbn;
    QPropertyAnimation* add_chat;
    QPropertyAnimation* add_channel;
    QPropertyAnimation* add_group;

};
#endif // MAINWINDOW_H
