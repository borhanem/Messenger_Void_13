#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "theme.h"
#include <windows.h>
#include <QListWidgetItem>
#include "channelchat.h"
#include "createprivatepage.h"
#include "privatechat.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mp_user(new User()),
    mp_groupWorker(new WorkerRefresher(WorkerRefresher::ChatList,User::Group)),
    mp_channelWorker(new WorkerRefresher(WorkerRefresher::ChatList,User::Channel)),
    mp_privateWorker(new WorkerRefresher(WorkerRefresher::ChatList,User::Private)),
    m_groupCount(0),
    m_channelCount(0),
    m_privateCount(0)
{
    ui->setupUi(this);
    mp_user->loadFromFile();
    this->loadChats();
    ui->Minus_tbn->hide();
    ui->toolButton->setCheckable(true);
    ui->Add_tbn->setCheckable(true);
    ui->stackedWidget->setCurrentIndex(0);
    ui->user_led->setText(mp_user->getUserName());
    ui->pass_led->setText(mp_user->getPassword());
    ui->token_led->setText(mp_user->getToken());
    setWindowFlags(Qt::FramelessWindowHint);
    ui->repository_info_lbl->hide();
    ui->repository_link_lbl->hide();
    ui->createGroup_pbn->hide();
    ui->newchannel_pbn->hide();
    ui->newchat_pbn->hide();
    ui->pass_led->setDisabled(true);
    ui->user_led->setDisabled(true);
    ui->token_led->setDisabled(true);
    ui->pass_led->hide();
    ui->pass_lbl->hide();
    ui->Theme_3_pbn->hide();
    ui->Theme_2_pbn->hide();
    ui->Theme_1->hide();
    ui->user_led->hide();
    ui->user_lbl->hide();
    ui->logout_pbn->hide();
    ui->pushButton->hide();
    ui->token_lbl->hide();
    ui->token_led->hide();
    ui->repository_link_lbl->setText("<a href=\"https://github.com/borhanem/Messenger_Void_13/tree/master/\">https://github.com/borhanem/Messenger_Void_13.git</a>");
    ui->repository_link_lbl->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->repository_link_lbl->setOpenExternalLinks(true);
    connect(mp_user,&User::SuccessOnLogout,this,&MainWindow::logoutUser);
    connect(mp_groupWorker,&WorkerRefresher::chatResultReady,this,&MainWindow::group_refresh_handler);
    connect(mp_channelWorker,&WorkerRefresher::chatResultReady,this,&MainWindow::channel_refresh_handler);
    connect(mp_privateWorker,&WorkerRefresher::chatResultReady,this,&MainWindow::private_refresh_handler);
    mp_groupWorker->setPreSize(this->m_groupCount);
    mp_channelWorker->setPreSize(this->m_channelCount);
    mp_privateWorker->setPreSize(this->m_privateCount);
    mp_groupWorker->run();
    mp_channelWorker->run();
    mp_privateWorker->run();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mp_user;
    delete mp_groupWorker;
    delete mp_channelWorker;
    for(auto& i : this->mp_ChatList)
    {
        delete i;
    }
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


        ui->chats_listWidget->show();
        ui->Exit_pbn->show();
        ui->Add_tbn->show();

        setting_pbn = new QPropertyAnimation(ui->toolButton , "geometry");
        setting_pbn->setDuration(1);
        setting_pbn->setStartValue(QRect(527,2,31,31));
        setting_pbn->setEndValue(QRect(467,2,31,31));
        setting_pbn->start();

        user_lbl_hide = new QPropertyAnimation(ui->user_lbl , "geometry");
        user_lbl_hide-> setDuration(200);
        user_lbl_hide->setStartValue(QRect(17,42,52,20));
        user_lbl_hide-> setEndValue(QRect(-383,42,52,20));
        user_lbl_hide->start();

        user_led_hide = new QPropertyAnimation(ui->user_led , "geometry");
        user_led_hide-> setDuration(200);
        user_led_hide->setStartValue(QRect(17,75,350,61));
        user_led_hide-> setEndValue(QRect(-383,75,350,61));
        user_led_hide->start();

        pass_lbl_hide = new QPropertyAnimation(ui->pass_lbl , "geometry");
        pass_lbl_hide-> setDuration(200);
        pass_lbl_hide->setStartValue(QRect(17,143,52,20));
        pass_lbl_hide-> setEndValue(QRect(-383,143,68,20));
        pass_lbl_hide->start();

       pass_led_hide = new QPropertyAnimation(ui->pass_led , "geometry");
        pass_led_hide-> setDuration(200);
        pass_led_hide->setStartValue(QRect(17,176,350,61));
        pass_led_hide-> setEndValue(QRect(-383,176,350,61));
        pass_led_hide->start();

        token_lbl_hide = new QPropertyAnimation(ui->token_lbl , "geometry");
        token_lbl_hide-> setDuration(200);
        token_lbl_hide->setStartValue(QRect(17,244,52,20));
        token_lbl_hide-> setEndValue(QRect(-383,244,52,20));
        token_lbl_hide->start();

        token_led_hide = new QPropertyAnimation(ui->token_led , "geometry");
        token_led_hide-> setDuration(200);
        token_led_hide->setStartValue(QRect(17,277,350,61));
        token_led_hide-> setEndValue(QRect(-383,277,350,61));
        token_led_hide->start();


        logout_hide = new QPropertyAnimation(ui->logout_pbn , "geometry");
        logout_hide->setDuration(200);
        logout_hide->setStartValue(QRect(17,378,350,61));
        logout_hide->setEndValue(QRect(-383,378,350,61));
        logout_hide->start();

        color_1_hide = new QPropertyAnimation(ui->Theme_1 , "geometry");
        color_1_hide->setDuration(200);
        color_1_hide->setStartValue(QRect(450,75,91,61));
        color_1_hide->setEndValue(QRect(600,75,91,61));
        color_1_hide->start();

        color_2_hide = new QPropertyAnimation(ui->Theme_2_pbn , "geometry");
        color_2_hide->setDuration(200);
        color_2_hide->setStartValue(QRect(450,176,91,61));
        color_2_hide->setEndValue(QRect(600,176,91,61));
        color_2_hide->start();

        color_3_hide = new QPropertyAnimation(ui->Theme_3_pbn , "geometry");
        color_3_hide->setDuration(200);
        color_3_hide->setStartValue(QRect(450,277,91,61));
        color_3_hide->setEndValue(QRect(600,277,91,61));
        color_3_hide->start();

        color_4_hide = new QPropertyAnimation(ui->pushButton , "geometry");
        color_4_hide->setDuration(200);
        color_4_hide->setStartValue(QRect(450,378,91,61));
        color_4_hide->setEndValue(QRect(600,378,91,61));
        color_4_hide->start();

        info_lbl = new QPropertyAnimation(ui->repository_info_lbl , "geometry");
        info_lbl->setDuration(200);
        info_lbl->setStartValue(QRect(17,490,300,20));
        info_lbl->setEndValue(QRect(-333,490,300,20));
        info_lbl->start();

        link_lbl = new QPropertyAnimation(ui->repository_link_lbl , "geometry");
        link_lbl->setDuration(200);
        link_lbl->setStartValue(QRect(17,520,400,20));
        link_lbl->setEndValue(QRect(-433,520,400,20));
        link_lbl->start();
    }
    else
    {

        ui->chats_listWidget->hide();
        ui->createGroup_pbn->hide();
        ui->newchannel_pbn->hide();
        ui->newchat_pbn->hide();
        ui->Exit_pbn->hide();
        ui->Add_tbn->hide();

        user_lbl_hide = new QPropertyAnimation(ui->user_lbl , "geometry");
        user_lbl_hide-> setDuration(200);
        user_lbl_hide->setStartValue(QRect(-83,42,52,20));
        user_lbl_hide-> setEndValue(QRect(17,42,52,20));
        user_lbl_hide->start();

        user_led_hide = new QPropertyAnimation(ui->user_led , "geometry");
        user_led_hide-> setDuration(200);
        user_led_hide->setStartValue(QRect(-83,75,350,61));
        user_led_hide-> setEndValue(QRect(17,75,350,61));
        user_led_hide->start();

        pass_lbl_hide = new QPropertyAnimation(ui->pass_lbl , "geometry");
        pass_lbl_hide-> setDuration(200);
        pass_lbl_hide->setStartValue(QRect(-83,143,52,20));
        pass_lbl_hide-> setEndValue(QRect(17,143,68,20));
        pass_lbl_hide->start();

        pass_led_hide = new QPropertyAnimation(ui->pass_led , "geometry");
        pass_led_hide-> setDuration(200);
        pass_led_hide->setStartValue(QRect(-83,176,350,61));
        pass_led_hide-> setEndValue(QRect(17,176,350,61));
        pass_led_hide->start();

        token_lbl_hide = new QPropertyAnimation(ui->token_lbl , "geometry");
        token_lbl_hide-> setDuration(200);
        token_lbl_hide->setStartValue(QRect(-83,244,52,20));
        token_lbl_hide-> setEndValue(QRect(17,244,52,20));
        token_lbl_hide->start();

        token_led_hide = new QPropertyAnimation(ui->token_led , "geometry");
        token_led_hide-> setDuration(200);
        token_led_hide->setStartValue(QRect(-83,277,350,61));
        token_led_hide-> setEndValue(QRect(17,277,350,61));
        token_led_hide->start();


        logout_hide = new QPropertyAnimation(ui->logout_pbn , "geometry");
        logout_hide->setDuration(200);
        logout_hide->setStartValue(QRect(-83,378,350,61));
        logout_hide->setEndValue(QRect(17,378,350,61));
        logout_hide->start();

        color_1_hide = new QPropertyAnimation(ui->Theme_1 , "geometry");
        color_1_hide->setDuration(200);
        color_1_hide->setStartValue(QRect(550,75,91,61));
        color_1_hide->setEndValue(QRect(450,75,91,61));
        color_1_hide->start();

        color_2_hide = new QPropertyAnimation(ui->Theme_2_pbn , "geometry");
        color_2_hide->setDuration(200);
        color_2_hide->setStartValue(QRect(550,176,91,61));
        color_2_hide->setEndValue(QRect(450,176,91,61));
        color_2_hide->start();

        color_3_hide = new QPropertyAnimation(ui->Theme_3_pbn , "geometry");
        color_3_hide->setDuration(200);
        color_3_hide->setStartValue(QRect(550,277,91,61));
        color_3_hide->setEndValue(QRect(450,277,91,61));
        color_3_hide->start();

        color_4_hide = new QPropertyAnimation(ui->pushButton , "geometry");
        color_4_hide->setDuration(200);
        color_4_hide->setStartValue(QRect(550,378,91,61));
        color_4_hide->setEndValue(QRect(450,378,91,61));
        color_4_hide->start();


        info_lbl = new QPropertyAnimation(ui->repository_info_lbl , "geometry");
        info_lbl->setDuration(200);
        info_lbl->setStartValue(QRect(-83,490,300,20));
        info_lbl->setEndValue(QRect(17,490,300,20));
        info_lbl->start();

        link_lbl = new QPropertyAnimation(ui->repository_link_lbl , "geometry");
        link_lbl->setDuration(200);
        link_lbl->setStartValue(QRect(-83,520,360,20));
        link_lbl->setEndValue(QRect(17,520,360,20));
        link_lbl->start();

        setting_pbn = new QPropertyAnimation(ui->toolButton , "geometry");
        setting_pbn->setDuration(1);
        setting_pbn->setStartValue(QRect(467,2,31,31));
        setting_pbn->setEndValue(QRect(527,2,31,31));
        setting_pbn->start();

        ui->repository_info_lbl->show();
        ui->repository_link_lbl->show();
        ui->pass_led->show();
        ui->pass_lbl->show();
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
    this->deleteLater();
    this->close();
}


void MainWindow::on_createGroup_pbn_clicked()
{
    mp_cgp = new CreateGroupPage(this->mp_user,this);
    //connect(mp_cgp,&CreateGroupPage::finished,this,&MainWindow::delete_createGroupPage);
    connect(mp_cgp,&CreateGroupPage::NewGroup,this,&MainWindow::handler_on_NewGroup);
    mp_cgp->exec();
    delete mp_cgp;
}

//void MainWindow::delete_createGroupPage()
//{
//    //delete mp_cgp;
//}

void MainWindow::handler_on_NewGroup(QString newGroupName)
{
    this->mp_groupWorker->setPreSize(++this->m_groupCount);
    qDebug("handler on NewGroup called in mainWindow\n");
    AbstractChat* newGroup = new GroupChat(newGroupName,this);
    this->mp_ChatList.push_back(newGroup);
    newGroup->saveToFile();
    QListWidgetItem* newItem = new QListWidgetItem(newGroup->chatName());
    newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(newGroup));
    ui->chats_listWidget->addItem(newItem);
    ui->chats_listWidget_2->addItem(newItem);
    dynamic_cast<GroupChat*>(newGroup)->open();
}

void MainWindow::handler_on_NewChannel(QString newChannelName)
{
    this->mp_channelWorker->setPreSize(++this->m_channelCount);
    AbstractChat* newChannel = new ChannelChat(newChannelName,this);
    this->mp_ChatList.push_back(newChannel);
    newChannel->saveToFile();
    QListWidgetItem* newItem = new QListWidgetItem(newChannel->chatName());
    newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(newChannel));
    ui->chats_listWidget->addItem(newItem);
    ui->chats_listWidget_2->addItem(newItem);
    dynamic_cast<ChannelChat*>(newChannel)->open();
}

void MainWindow::hanlder_on_NewPrivate(QString newPrivateName)
{
    this->mp_privateWorker->setPreSize(++this->m_privateCount);
    qDebug() << "MainWindow::hanlder_on_NewPrivate => PrivateChat with the name " << newPrivateName << "created";
    AbstractChat* newPrivate = new PrivateChat(newPrivateName,this);
    this->mp_ChatList.push_back(newPrivate);
    newPrivate->saveToFile();
    QListWidgetItem* newItem = new QListWidgetItem(newPrivate->chatName());
    newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(newPrivate));
    ui->chats_listWidget->addItem(newItem);
    ui->chats_listWidget_2->addItem(newItem);
    dynamic_cast<PrivateChat*>(newPrivate)->open();
}


void MainWindow::on_Exit_pbn_clicked()
{
    //this->deleteLater();
    this->close();
}


void MainWindow::on_chats_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    AbstractChat* selected_chat = qvariant_cast<AbstractChat*>(item->data(Qt::UserRole));
    switch (selected_chat->chatType()) {
    case AbstractChat::Private:
    // cast to PrivateChat
        dynamic_cast<PrivateChat*>(selected_chat)->open();
        break;
    case AbstractChat::Group:
        // cast to GroupChat
        dynamic_cast<GroupChat*>(selected_chat)->open();
        break;
    case AbstractChat::Channel:
        // cast to Channel
        dynamic_cast<ChannelChat*>(selected_chat)->open();
        break;
    default:
        qDebug("Error From MainWindows::on_chats_listWidget_itemDoubleClicked: Cannot recognize the type");
        break;
    }

}


void MainWindow::on_newchannel_pbn_clicked()
{

    CreateChannelPage* chp = new CreateChannelPage(mp_user,this);
    connect(chp,&CreateChannelPage::channelCreated,this,&MainWindow::handler_on_NewChannel);
    chp->exec();
    delete chp;
}


void MainWindow::on_Minus_tbn_clicked()
{

        ui->createGroup_pbn->show();
        ui->newchannel_pbn->show();
        ui->newchat_pbn->show();
        ui->toolButton->show();
        ui->Exit_pbn->show();
        ui->Add_tbn->show();
        ui->Minus_tbn->hide();
        ui->Add_tbn->setStyleSheet(ui->Minus_tbn->styleSheet());

        setting_pbn = new QPropertyAnimation(ui->Minus_tbn , "geometry");
        setting_pbn->setDuration(1);
        setting_pbn->setStartValue(QRect(527,2,31,31));
        setting_pbn->setEndValue(QRect(499,2,31,31));
        setting_pbn->start();

        add_chat = new QPropertyAnimation(ui->newchat_pbn , "geometry");
        add_chat->setDuration(150);
        add_chat->setStartValue(QRect(360,105,180,40));
        add_chat->setEndValue(QRect(600,105,180,40));
        add_chat->start();

        add_group = new QPropertyAnimation(ui->createGroup_pbn , "geometry");
        add_group->setDuration(300);
        add_group->setStartValue(QRect(360,207,180,40));
        add_group->setEndValue(QRect(600,207,180,40));
        add_group->start();

        add_channel = new QPropertyAnimation(ui->newchannel_pbn , "geometry");
        add_channel->setDuration(150);
        add_channel->setStartValue(QRect(360,308,180,40));
        add_channel->setEndValue(QRect(600,308,180,40));
        add_channel->start();

        list = new QPropertyAnimation(ui->chats_listWidget , "geometry");
        list->setDuration(100);
        list->setStartValue(QRect(20,50,323,490));
        list->setEndValue(QRect(20,50,520,490));
        list->start();



}
void MainWindow::loadChats()
{
        QDir gDir("vdata/MsgData/Groups"),cDir("vdata/MsgData/Channels"),pDir("vdata/MsgData/Privates");
    if(gDir.exists())
    {
        qDebug() << "vdata/MsgData/Groups" << " exist!\n";
        for (const QFileInfo &file : gDir.entryInfoList(QDir::Files))
        {
            qDebug() << file.baseName();
            AbstractChat* groupEntity = new GroupChat(file.baseName(),this);
            //groupEntity->loadFromFile();
            qDebug() << "loaded From File";
            mp_ChatList.push_back(groupEntity);
            qDebug() << "added to ChatList";
            QListWidgetItem* newItem = new QListWidgetItem(groupEntity->chatName());
            newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(groupEntity));
            ui->chats_listWidget->addItem(newItem);
            ui->chats_listWidget_2->addItem(newItem);
            m_groupCount++;
        }
        qDebug() << "MainWindow::loadChats => groupCount = " << m_groupCount;
    }
    if(cDir.exists())
    {
        qDebug() << "vdata/MsgData/Channels" << " exist!\n";
        for (const QFileInfo &file : cDir.entryInfoList(QDir::Files))
        {
            qDebug() << file.baseName();
            AbstractChat* ChannelEntity = new ChannelChat(file.baseName(),this);
            //ChannelEntity->loadFromFile();
            qDebug() << "loaded From File";
            mp_ChatList.push_back(ChannelEntity);
            qDebug() << "added to ChatList";
            QListWidgetItem* newItem = new QListWidgetItem(ChannelEntity->chatName());
            newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(ChannelEntity));
            ui->chats_listWidget->addItem(newItem);
            ui->chats_listWidget_2->addItem(newItem);
            m_channelCount++;
        }
        qDebug() << "MainWindow::loadChats => channelCount = " << m_channelCount;

    }
    if(pDir.exists())
    {
        qDebug() << "vdata/MsgData/Privates" << " exist!\n";
        for (const QFileInfo &file : pDir.entryInfoList(QDir::Files))
        {
            qDebug() << file.baseName();
            AbstractChat* PrivateEntity = new PrivateChat(file.baseName(),this);
            //groupEntity->loadFromFile();
            qDebug() << "loaded From File";
            mp_ChatList.push_back(PrivateEntity);
            qDebug() << "added to ChatList";
            QListWidgetItem* newItem = new QListWidgetItem(PrivateEntity->chatName());
            newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(PrivateEntity));
            ui->chats_listWidget->addItem(newItem);
            ui->chats_listWidget_2->addItem(newItem);
            m_privateCount++;
        }
        qDebug() << "MainWindow::loadChats => groupCount = " << m_groupCount;
    }

}


void MainWindow::on_Exit_pbn_2_clicked()
{
    this->deleteLater();
    this->close();

}


void MainWindow::on_Add_tbn_clicked()
{
    ui->toolButton->hide();
    ui->createGroup_pbn->show();
    ui->newchannel_pbn->show();
    ui->newchat_pbn->show();
    ui->Exit_pbn->hide();
    ui->Minus_tbn->show();
    ui->Add_tbn->hide();
    ui->Add_tbn->setStyleSheet(ui->Minus_tbn->styleSheet());

    list = new QPropertyAnimation(ui->chats_listWidget , "geometry");
    list->setDuration(100);
    list->setStartValue(QRect(20,50,520,490));
    list->setEndValue(QRect(20,50,323,490));
    list->start();

    add_chat = new QPropertyAnimation(ui->newchat_pbn , "geometry");
    add_chat->setDuration(150);
    add_chat->setStartValue(QRect(550,105,180,40));
    add_chat->setEndValue(QRect(360,105,180,40));
    add_chat->start();

    add_group = new QPropertyAnimation(ui->createGroup_pbn , "geometry");
    add_group->setDuration(300);
    add_group->setStartValue(QRect(550,207,180,40));
    add_group->setEndValue(QRect(360,207,180,40));
    add_group->start();

    add_channel = new QPropertyAnimation(ui->newchannel_pbn , "geometry");
    add_channel->setDuration(450);
    add_channel->setStartValue(QRect(550,308,180,40));
    add_channel->setEndValue(QRect(360,308,180,40));
    add_channel->start();

    setting_pbn = new QPropertyAnimation(ui->Minus_tbn , "geometry");
    setting_pbn->setDuration(1);
    setting_pbn->setStartValue(QRect(499,2,31,31));
    setting_pbn->setEndValue(QRect(527,2,31,31));
    setting_pbn->start();
}

void MainWindow::group_refresh_handler(QList<AbstractChat*> new_chats)
{
    this->m_groupCount += new_chats.size();
    this->mp_ChatList += new_chats;
    for(auto& i : new_chats){
    QListWidgetItem* newItem = new QListWidgetItem(i->chatName());
    newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(i));
    ui->chats_listWidget->addItem(newItem);
    ui->chats_listWidget_2->addItem(newItem);
    }
}

void MainWindow::channel_refresh_handler(QList<AbstractChat *> new_chats)
{
    this->m_channelCount += new_chats.size();
    this->mp_ChatList += new_chats;
    for(auto& i : new_chats){
    QListWidgetItem* newItem = new QListWidgetItem(i->chatName());
    newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(i));
    ui->chats_listWidget->addItem(newItem);
    ui->chats_listWidget_2->addItem(newItem);
    }
}

void MainWindow::private_refresh_handler(QList<AbstractChat *> new_chats)
{
    this->m_privateCount += new_chats.size();
    this->mp_ChatList += new_chats;
    for(auto& i : new_chats){
    QListWidgetItem* newItem = new QListWidgetItem(i->chatName());
    newItem->setData(Qt::UserRole,QVariant::fromValue<AbstractChat*>(i));
    ui->chats_listWidget->addItem(newItem);
    ui->chats_listWidget_2->addItem(newItem);
    }
}


void MainWindow::on_newchat_pbn_clicked()
{
    CreatePrivatePage* cpg = new CreatePrivatePage(this->mp_user,this);
    connect(cpg,&CreatePrivatePage::NewPrivate,this,&MainWindow::hanlder_on_NewPrivate);
    cpg->exec();
    delete cpg;
}

