#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginpage.h"
#include <Qthread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mp_user(new User())
{
    ui->setupUi(this);
    mp_user->loadFromFile();
    ui->toolButton->setCheckable(true);
    ui->user_led->setText(mp_user->getUserName());
    ui->pass_led->setText(mp_user->getPassword());
    ui->token_led->setText(mp_user->getToken());
    setWindowFlags(Qt::FramelessWindowHint);
    ui->pass_led->hide();
    ui->label->hide();
    ui->Theme_3_pbn->hide();
    ui->Theme_2_pbn->hide();
    ui->Theme_1->hide();
    ui->user_led->hide();
    ui->user_lbl->hide();
    ui->logout_pbn->hide();
    ui->pushButton->hide();
    ui->token_lbl->hide();
    ui->token_led->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Store the initial position of the mouse press event
        m_mousePressPos = event->pos();
        // Store the initial position of the window
        m_windowPos = pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // Calculate the new position of the window based on the mouse movement
        QPoint diff = event->pos() - m_mousePressPos;
        QPoint newWindowPos = m_windowPos + diff;
        // Update the position of the window
        move(newWindowPos);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Reset the stored positions
        m_mousePressPos = QPoint();
        m_windowPos = QPoint();
    }
}

void MainWindow::on_logout_pbn_clicked()
{
    mp_user->logOut();
}


void MainWindow::on_Theme_1_clicked()
{
    ThemeChange("1");
}


void MainWindow::on_Theme_2_pbn_clicked()
{
  ThemeChange("2");
}


void MainWindow::on_pushButton_clicked()
{
  ThemeChange("4");
}


void MainWindow::on_Theme_3_pbn_clicked()
{
    ThemeChange("3");
}


void MainWindow::on_toolButton_clicked(bool checked)
{
    if(!checked)
    {

        ui->pass_led->hide();
        ui->label->hide();
        ui->Theme_3_pbn->hide();
        ui->Theme_2_pbn->hide();
        ui->Theme_1->hide();
        ui->user_led->hide();
        ui->user_lbl->hide();
        ui->logout_pbn->hide();
        ui->pushButton->hide();
        ui->token_lbl->hide();
        ui->token_led->hide();
    }
    else
    {
        ui->pass_led->show();
        ui->label->show();
        ui->Theme_3_pbn->show();
        ui->Theme_2_pbn->show();
        ui->Theme_1->show();
        ui->user_led->show();
        ui->user_lbl->show();
        ui->logout_pbn->show();
        ui->pushButton->show();
        ui->token_lbl->show();
        ui->token_led->show();
    }



}

