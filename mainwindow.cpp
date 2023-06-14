#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mp_user(new User())
{
    ui->setupUi(this);
    mp_user->loadFromFile();
    ui->user_led->setText(mp_user->getUserName());
    ui->pass_led->setText(mp_user->getPassword());
    ui->token_led->setText(mp_user->getToken());
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_logout_pbn_clicked()
{
    mp_user->logOut();
}


void MainWindow::on_toolButton_clicked()
{

    QString time_format = "yyyy-MM-dd  HH:mm:ss";
    QDateTime a = QDateTime::currentDateTime();
    QString as = a.toString(time_format);

    qDebug() << as; // print "2014-07-16  17:47:04"
    QDateTime b = QDateTime::fromString(as,time_format);

    ui->listWidget->addItem(b.toString());
}

