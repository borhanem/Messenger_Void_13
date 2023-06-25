#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "theme.h"
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
    connect(mp_user,&User::SuccessOnLogout,this,&MainWindow::logoutUser);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mp_user;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
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
        user_lbl_hide-> setDuration(150);
        user_lbl_hide->setStartValue(QRect(451,11,52,20));
        user_lbl_hide-> setEndValue(QRect(600,11,52,20));
        user_lbl_hide->start();

        user_led_hide = new QPropertyAnimation(ui->user_led , "geometry");
        user_led_hide-> setDuration(250);
        user_led_hide->setStartValue(QRect(451,38,119,28));
        user_led_hide-> setEndValue(QRect(600,38,119,28));
        user_led_hide->start();

        pass_lbl_hide = new QPropertyAnimation(ui->label , "geometry");
        pass_lbl_hide-> setDuration(350);
        pass_lbl_hide->setStartValue(QRect(451,73,68,20));
        pass_lbl_hide-> setEndValue(QRect(600,73,68,20));
        pass_lbl_hide->start();

       pass_led_hide = new QPropertyAnimation(ui->pass_led , "geometry");
        pass_led_hide-> setDuration(450);
        pass_led_hide->setStartValue(QRect(451,100,119,28));
        pass_led_hide-> setEndValue(QRect(600,100,119,28));
        pass_led_hide->start();

        token_lbl_hide = new QPropertyAnimation(ui->token_lbl , "geometry");
        token_lbl_hide-> setDuration(600);
        token_lbl_hide->setStartValue(QRect(451,135,46,20));
        token_lbl_hide-> setEndValue(QRect(600,135,46,20));
        token_lbl_hide->start();

        token_led_hide = new QPropertyAnimation(ui->token_led , "geometry");
        token_led_hide-> setDuration(500);
        token_led_hide->setStartValue(QRect(451,162,119,28));
        token_led_hide-> setEndValue(QRect(600,162,119,28));
        token_led_hide->start();


        logout_hide = new QPropertyAnimation(ui->logout_pbn , "geometry");
        logout_hide->setDuration(400);
        logout_hide->setStartValue(QRect(451,224,121,29));
        logout_hide->setEndValue(QRect(600,224,121,29));
        logout_hide->start();

        color_1_hide = new QPropertyAnimation(ui->Theme_1 , "geometry");
        color_1_hide->setDuration(300);
        color_1_hide->setStartValue(QRect(450,290,25,21));
        color_1_hide->setEndValue(QRect(599,290,25,21));
        color_1_hide->start();

        color_2_hide = new QPropertyAnimation(ui->Theme_2_pbn , "geometry");
        color_2_hide->setDuration(250);
        color_2_hide->setStartValue(QRect(482,290,24,21));
        color_2_hide->setEndValue(QRect(631,290,24,21));
        color_2_hide->start();

        color_3_hide = new QPropertyAnimation(ui->Theme_3_pbn , "geometry");
        color_3_hide->setDuration(200);
        color_3_hide->setStartValue(QRect(513,290,25,21));
        color_3_hide->setEndValue(QRect(712,290,25,21));
        color_3_hide->start();

        color_4_hide = new QPropertyAnimation(ui->pushButton , "geometry");
        color_4_hide->setDuration(150);
        color_4_hide->setStartValue(QRect(545,290,24,21));
        color_4_hide->setEndValue(QRect(744,290,24,21));
        color_4_hide->start();
    }
    else
    {

        user_lbl_hide = new QPropertyAnimation(ui->user_lbl , "geometry");
        user_lbl_hide-> setDuration(200);
        user_lbl_hide->setStartValue(QRect(600,11,52,20));
        user_lbl_hide-> setEndValue(QRect(451,11,52,20));
        user_lbl_hide->start();

        user_led_hide = new QPropertyAnimation(ui->user_led , "geometry");
        user_led_hide-> setDuration(250);
        user_led_hide->setStartValue(QRect(600,38,119,28));
        user_led_hide-> setEndValue(QRect(451,38,119,28));
        user_led_hide->start();

        pass_lbl_hide = new QPropertyAnimation(ui->label , "geometry");
        pass_lbl_hide-> setDuration(350);
        pass_lbl_hide->setStartValue(QRect(600,73,68,20));
        pass_lbl_hide-> setEndValue(QRect(451,73,68,20));
        pass_lbl_hide->start();

        pass_led_hide = new QPropertyAnimation(ui->pass_led , "geometry");
        pass_led_hide-> setDuration(450);
        pass_led_hide->setStartValue(QRect(600,100,119,28));
        pass_led_hide-> setEndValue(QRect(451,100,119,28));
        pass_led_hide->start();

        token_lbl_hide = new QPropertyAnimation(ui->token_lbl , "geometry");
        token_lbl_hide-> setDuration(550);
        token_lbl_hide->setStartValue(QRect(600,135,46,20));
        token_lbl_hide-> setEndValue(QRect(451,135,46,20));
        token_lbl_hide->start();

        token_led_hide = new QPropertyAnimation(ui->token_led , "geometry");
        token_led_hide-> setDuration(650);
        token_led_hide->setStartValue(QRect(600,162,119,28));
        token_led_hide-> setEndValue(QRect(451,162,119,28));
        token_led_hide->start();

        logout_hide = new QPropertyAnimation(ui->logout_pbn , "geometry");
        logout_hide->setDuration(750);
        logout_hide->setStartValue(QRect(600,224,121,29));
        logout_hide->setEndValue(QRect(451,224,121,29));
        logout_hide->start();

        color_1_hide = new QPropertyAnimation(ui->Theme_1 , "geometry");
        color_1_hide->setDuration(850);
        color_1_hide->setStartValue(QRect(599,290,25,21));
        color_1_hide->setEndValue(QRect(450,290,25,21));
        color_1_hide->start();

        color_2_hide = new QPropertyAnimation(ui->Theme_2_pbn , "geometry");
        color_2_hide->setDuration(900);
        color_2_hide->setStartValue(QRect(631,290,24,21));
        color_2_hide->setEndValue(QRect(482,290,24,21));
        color_2_hide->start();

        color_3_hide = new QPropertyAnimation(ui->Theme_3_pbn , "geometry");
        color_3_hide->setDuration(950);
        color_3_hide->setStartValue(QRect(662,290,25,21));
        color_3_hide->setEndValue(QRect(513,290,25,21));
        color_3_hide->start();

        color_4_hide = new QPropertyAnimation(ui->pushButton , "geometry");
        color_4_hide->setDuration(1000);
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

void MainWindow::logoutUser()
{
    LoginPage* lpgPtr = new LoginPage();
    lpgPtr->open();
    this->close();
}

