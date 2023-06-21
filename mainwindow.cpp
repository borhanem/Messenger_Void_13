#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginpage.h"
#include <windows.h>


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
        user_lbl_hide = new QPropertyAnimation(ui->user_lbl , "geometry");
        user_lbl_hide-> setDuration(300);
        user_lbl_hide->setStartValue(QRect(451,11,52,20));
        user_lbl_hide-> setEndValue(QRect(600,11,52,20));
        user_lbl_hide->start();

        user_led_hide = new QPropertyAnimation(ui->user_led , "geometry");
        user_led_hide-> setDuration(500);
        user_led_hide->setStartValue(QRect(451,38,119,28));
        user_led_hide-> setEndValue(QRect(600,38,119,28));
        user_led_hide->start();

        pass_lbl_hide = new QPropertyAnimation(ui->label , "geometry");
        pass_lbl_hide-> setDuration(700);
        pass_lbl_hide->setStartValue(QRect(451,73,68,20));
        pass_lbl_hide-> setEndValue(QRect(600,73,68,20));
        pass_lbl_hide->start();

       pass_led_hide = new QPropertyAnimation(ui->pass_led , "geometry");
        pass_led_hide-> setDuration(900);
        pass_led_hide->setStartValue(QRect(451,100,119,28));
        pass_led_hide-> setEndValue(QRect(600,100,119,28));
        pass_led_hide->start();

        token_lbl_hide = new QPropertyAnimation(ui->token_lbl , "geometry");
        token_lbl_hide-> setDuration(1200);
        token_lbl_hide->setStartValue(QRect(451,135,46,20));
        token_lbl_hide-> setEndValue(QRect(600,135,46,20));
        token_lbl_hide->start();

        token_led_hide = new QPropertyAnimation(ui->token_led , "geometry");
        token_led_hide-> setDuration(1000);
        token_led_hide->setStartValue(QRect(451,162,119,28));
        token_led_hide-> setEndValue(QRect(600,162,119,28));
        token_led_hide->start();


        logout_hide = new QPropertyAnimation(ui->logout_pbn , "geometry");
        logout_hide->setDuration(800);
        logout_hide->setStartValue(QRect(451,224,121,29));
        logout_hide->setEndValue(QRect(600,224,121,29));
        logout_hide->start();

        color_1_hide = new QPropertyAnimation(ui->Theme_1 , "geometry");
        color_1_hide->setDuration(600);
        color_1_hide->setStartValue(QRect(450,290,25,21));
        color_1_hide->setEndValue(QRect(599,290,25,21));
        color_1_hide->start();

        color_2_hide = new QPropertyAnimation(ui->Theme_2_pbn , "geometry");
        color_2_hide->setDuration(500);
        color_2_hide->setStartValue(QRect(482,290,24,21));
        color_2_hide->setEndValue(QRect(631,290,24,21));
        color_2_hide->start();

        color_3_hide = new QPropertyAnimation(ui->Theme_3_pbn , "geometry");
        color_3_hide->setDuration(400);
        color_3_hide->setStartValue(QRect(513,290,25,21));
        color_3_hide->setEndValue(QRect(712,290,25,21));
        color_3_hide->start();

        color_4_hide = new QPropertyAnimation(ui->pushButton , "geometry");
        color_4_hide->setDuration(300);
        color_4_hide->setStartValue(QRect(545,290,24,21));
        color_4_hide->setEndValue(QRect(744,290,24,21));
        color_4_hide->start();
    }
    else
    {

        user_lbl_hide = new QPropertyAnimation(ui->user_lbl , "geometry");
        user_lbl_hide-> setDuration(300);
        user_lbl_hide->setStartValue(QRect(600,11,52,20));
        user_lbl_hide-> setEndValue(QRect(451,11,52,20));
        user_lbl_hide->start();

        user_led_hide = new QPropertyAnimation(ui->user_led , "geometry");
        user_led_hide-> setDuration(500);
        user_led_hide->setStartValue(QRect(600,38,119,28));
        user_led_hide-> setEndValue(QRect(451,38,119,28));
        user_led_hide->start();

        pass_lbl_hide = new QPropertyAnimation(ui->label , "geometry");
        pass_lbl_hide-> setDuration(700);
        pass_lbl_hide->setStartValue(QRect(600,73,68,20));
        pass_lbl_hide-> setEndValue(QRect(451,73,68,20));
        pass_lbl_hide->start();

        pass_led_hide = new QPropertyAnimation(ui->pass_led , "geometry");
        pass_led_hide-> setDuration(900);
        pass_led_hide->setStartValue(QRect(600,100,119,28));
        pass_led_hide-> setEndValue(QRect(451,100,119,28));
        pass_led_hide->start();

        token_lbl_hide = new QPropertyAnimation(ui->token_lbl , "geometry");
        token_lbl_hide-> setDuration(1100);
        token_lbl_hide->setStartValue(QRect(600,135,46,20));
        token_lbl_hide-> setEndValue(QRect(451,135,46,20));
        token_lbl_hide->start();

        token_led_hide = new QPropertyAnimation(ui->token_led , "geometry");
        token_led_hide-> setDuration(1300);
        token_led_hide->setStartValue(QRect(600,162,119,28));
        token_led_hide-> setEndValue(QRect(451,162,119,28));
        token_led_hide->start();

        logout_hide = new QPropertyAnimation(ui->logout_pbn , "geometry");
        logout_hide->setDuration(1500);
        logout_hide->setStartValue(QRect(600,224,121,29));
        logout_hide->setEndValue(QRect(451,224,121,29));
        logout_hide->start();

        color_1_hide = new QPropertyAnimation(ui->Theme_1 , "geometry");
        color_1_hide->setDuration(1700);
        color_1_hide->setStartValue(QRect(599,290,25,21));
        color_1_hide->setEndValue(QRect(450,290,25,21));
        color_1_hide->start();

        color_2_hide = new QPropertyAnimation(ui->Theme_2_pbn , "geometry");
        color_2_hide->setDuration(1800);
        color_2_hide->setStartValue(QRect(631,290,24,21));
        color_2_hide->setEndValue(QRect(482,290,24,21));
        color_2_hide->start();

        color_3_hide = new QPropertyAnimation(ui->Theme_3_pbn , "geometry");
        color_3_hide->setDuration(1900);
        color_3_hide->setStartValue(QRect(662,290,25,21));
        color_3_hide->setEndValue(QRect(513,290,25,21));
        color_3_hide->start();

        color_4_hide = new QPropertyAnimation(ui->pushButton , "geometry");
        color_4_hide->setDuration(2000);
        color_4_hide->setStartValue(QRect(694,290,24,21));
        color_4_hide->setEndValue(QRect(545,290,24,21));
        color_4_hide->start();

        ui->pass_led->show();
        ui->label->show();
        ui->Theme_3_pbn->show();
        ui->Theme_2_pbn->show();
        ui->Theme_1->show();
        ui->logout_pbn->show();
        ui->pushButton->show();
        ui->token_lbl->show();
        ui->token_led->show();
        ui->user_led->show();
        ui->user_lbl->show();
    }



}

