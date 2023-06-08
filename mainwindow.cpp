#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_user = new User();
    char path[] = "userLog.txt";
    m_user->loadFromFile(path);
    qDebug() << "Alaki";
    qDebug() <<  m_user->getUserName();
    qDebug()<< " " <<m_user->getToken();
    QString txt = "you logged in as " + m_user->getUserName() + "\n" + "Your Token: " + m_user->getToken();
    ui->sample->setText(txt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

