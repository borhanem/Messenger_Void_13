#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "user.h"
#include <QDateTime>
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

    void on_logout_pbn_clicked();

    void on_Theme_1_clicked();

    void on_Theme_2_pbn_clicked();

    void on_pushButton_clicked();

    void on_Theme_3_pbn_clicked();

    void on_toolButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    User* mp_user;
};
#endif // MAINWINDOW_H
