#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "user.h"
#include <QDateTime>
#include <QMouseEvent>
#include <QPoint>
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

    void mouseReleaseEvent(QMouseEvent *event);

    void on_logout_pbn_clicked();

    void on_Theme_1_clicked();

    void on_Theme_2_pbn_clicked();

    void on_pushButton_clicked();

    void on_Theme_3_pbn_clicked();

    void on_toolButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    User* mp_user;
    QPoint m_windowPos;
    QPoint m_mousePressPos;
};
#endif // MAINWINDOW_H
