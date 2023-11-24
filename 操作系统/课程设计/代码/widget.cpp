#include "widget.h"
#include "ui_widget.h"
#include "user.h"
#include "disk_monitor.h"
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <fstream>
#include <QDialog>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setProperty("canMove",true);
    this->initUi();
    this->initMember();
    qRegisterMetaType<TCB*>("TCB*");
}

Widget::~Widget()
{
    delete ui;
}

/**********************************************************初始化函数****************************************************************/

void Widget::initUi()
{
    //初始化窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    ui->w_bg->setGraphicsEffect(shadow);
    ui->lay_bg->setMargin(12);

    //Logo
    QPixmap logo(":/icons/logo.png");
    ui->lab_logo->setPixmap(logo);

    //itemLogo
    QPixmap item1(":/icons/item_01.png");
    QPixmap item2(":/icons/item_02.png");
    ui->lab_item_01->setPixmap(item1);
    ui->lab_item_02->setPixmap(item2);
}

void Widget::initMember()
{
    this->myMbox = new MyMessageBox();
    connect(myMbox,SIGNAL(btnchicked(int)),this,SLOT(changeMboxReturn(int)));

    //最小化到托盘
    QIcon icon = QIcon(":/icons/logo.png");//设置最小图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Peach"); //提示文字
    //添加托盘列表项(还原与退出)
    returnNormal = new QAction(" Show", this);
    returnNormal->setFont(QFont("Arial", 9));
    returnNormal->setObjectName("returnNormal");
    returnNormal->setIcon(QIcon(":/icons/show.png"));
    quitAction = new QAction(" Quit", this);
    quitAction->setFont(QFont("Arial", 9));
    quitAction->setObjectName("quitAction");
    quitAction->setIcon(QIcon(":/icons/out.png"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));           //绑定槽函数退出
    connect(returnNormal, SIGNAL(triggered()), this, SLOT(showNormal()));   //绑定槽函数还原界面
    connect(ui->creat,&QPushButton::clicked,this,[=](){
        if (ui->edit_username->text().trimmed().size() == 0){
            myMbox->setIcon("warn");
            myMbox->setBodyText("请输入用户名");
            myMbox->setButtonText("确定");
            myMbox->exec();
        } else {
          switch(User::count){
          case 0:
              User::userName0 = ui->edit_username->text().toStdString();
              User::userName.append(ui->edit_username->text());
              User::count++;
              myMbox->setIcon("check");
              myMbox->setBodyText("创建成功");
              myMbox->setButtonText("确定");
              myMbox->exec();
              break;
          case 1:
              User::userName1 = ui->edit_username->text().toStdString();
              if (User::userName0==User::userName1){
                  User::count--;
                  myMbox->setIcon("error");
                  myMbox->setBodyText("当前用户已存在");
                  myMbox->setButtonText("确定");
                  myMbox->exec();
              }
              else{
                  User::userName.append(ui->edit_username->text());
                  User::count++;
                  myMbox->setIcon("check");
                  myMbox->setBodyText("创建成功");
                  myMbox->setButtonText("确定");
                  myMbox->exec();
              }
              break;
          case 2:
              User::userName2 = ui->edit_username->text().toStdString();
              if ((User::userName0==User::userName2)or(User::userName1==User::userName2)){
                  User::count--;
                  myMbox->setIcon("error");
                  myMbox->setBodyText("当前用户已存在");
                  myMbox->setButtonText("确定");
                  myMbox->exec();
              }
              else{
                  User::count++;
                  User::userName.append(ui->edit_username->text());
                  myMbox->setIcon("check");
                  myMbox->setBodyText("创建成功");
                  myMbox->setButtonText("确定");
                  myMbox->exec();
              }
              break;
          case 3:
              //User::userName3 = ui->edit_username->text().toStdString();
              User::userName.append(ui->edit_username->text());
              User::count++;
              myMbox->setIcon("check");
              myMbox->setBodyText("创建成功");
              myMbox->setButtonText("确定");
              myMbox->exec();
              break;
          }
        }
    });

    //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(returnNormal);
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);

    // 启动线程
    connect(ui->btn_menu_item_1,SIGNAL(clicked()),SLOT(createDataGenThread()));
    connect(ui->btn_menu_item_2,SIGNAL(clicked()),SLOT(createDataDelThread()));
    connect(ui->btn_menu_item_3,SIGNAL(clicked()),SLOT(createDataExeThread()));
    // 信号唤醒UI
    connect(ui->btn_menu_item_4,SIGNAL(clicked()),SLOT(openMemoryMonitor()));
    connect(ui->btn_menu_item_5,SIGNAL(clicked()),SLOT(openDiskMonitor()));
}

/**********************************************************自定义函数****************************************************************/

void Widget::littleShow()
{
    this->hide();//隐藏主窗口
    trayIcon->show();//显示托盘

    //显示到系统提示框的信息
    QString title="Peach";
    QString text="正自动在后台运行";
    trayIcon->showMessage(title,text,QSystemTrayIcon::Information,3000); //此参数为提示时长
}

/**********************************************************控件槽函数****************************************************************/

void Widget::closeEvent(QCloseEvent *event)
{
    myMbox->setIcon("question");
    myMbox->setBodyText("How to leave?");
    myMbox->setButtonText("Little","Logout");
    myMbox->exec();
    if(mbox_return == 0) {
        event->ignore();
    }else if(mbox_return == 1){
        event->ignore();
        littleShow();
    }
}

void Widget::changeMboxReturn(int num)
{
    this->mbox_return = num;
}

void Widget::on_btn_main_item_1_clicked()
{
    ui->sw_main->setCurrentIndex(0);
}

void Widget::on_btn_main_item_2_clicked()
{
    ui->sw_main->setCurrentIndex(1);
}

void Widget::on_btn_main_item_3_clicked()
{
    ui->sw_main->setCurrentIndex(2);
}

void Widget::on_btn_main_item_4_clicked()
{
    ui->sw_main->setCurrentIndex(3);
}

void Widget::on_btn_logout_clicked()
{
    close();
}

void Widget::on_btn_littleshow_clicked()
{
    showMinimized();
}

void Widget::updateData()
{
    // 通知两个监视器进行更新
    emit notifyUpdate();
}

// 创建一个数据生成线程
void Widget::createDataGenThread()
{
    GenDataThread *thread = new GenDataThread();
    QObject::connect(thread,SIGNAL(showMessage(QString)),this,SLOT(showMessage(QString)));
    QObject::connect(thread,SIGNAL(openUI()),this,SLOT(openDataGenUI()));
    thread->start();
    qDebug() <<"数据生成线程启动";
}

void Widget::createDataDelThread()
{
    DelDataThread *thread = new DelDataThread();
    QObject::connect(thread,SIGNAL(showMessage(QString)),this,SLOT(showMessage(QString)));
    QObject::connect(thread,SIGNAL(openUI()),this,SLOT(openDataDelUI()));
    thread->start();
    qDebug() <<"数据生成线程启动";
}

void Widget::createDataExeThread()
{
    ExeDataThread *thread = new ExeDataThread();
    QObject::connect(thread,SIGNAL(showMessage(QString)),this,SLOT(showMessage(QString)));
    connect(thread,SIGNAL(showMessage(QString)),this,SLOT(showMessage(QString)));
    connect(thread,SIGNAL(notify()),this,SLOT(updateData()));
    QObject::connect(thread,SIGNAL(openUI(TCB*)),this,SLOT(openDataExeUI(TCB*)));
    //连接信号
    thread->start();
    qDebug() <<"执行线程启动";
}

void Widget::openDataGenUI()
{
    dialog_gen_data * gdata = new dialog_gen_data(this);
    connect(gdata,SIGNAL(dataUpdated()),this,SLOT(updateData()));
    gdata->show();
}

void Widget::openDataDelUI()
{
    dialog_delete_data * ddata = new dialog_delete_data(this);
    // 删除信号
    connect(ddata,SIGNAL(dataUpdated()),this,SLOT(updateData()));
    // 传入信号
    connect(this,SIGNAL(notifyUpdate()),ddata,SLOT(refresh()));
    ddata->show();
}

void Widget::openDataExeUI(TCB* tcb)
{
    // 初始化其他
    window_exe_data * exeform = new window_exe_data(nullptr,tcb);
    // 删除信号
    connect(exeform,SIGNAL(notifyUpdate()),this,SLOT(updateData()));
    // 传入信号,通知更新文件信息
    connect(this,SIGNAL(notifyUpdate()),exeform,SLOT(updateFiles()));
    exeform->show();
}

void Widget::openMemoryMonitor()
{
    qDebug() << "开启内存可视化";
    MemoryMonitor * monitor = new MemoryMonitor(this);
    // 连接信号
    connect(this,SIGNAL(notifyUpdate()),monitor,SLOT(updateMemoryUI()));
    monitor->show();
}

void Widget::openDiskMonitor()
{
    qDebug() << "开启磁盘可视化";
    DiskMonitor * monitor = new DiskMonitor(this);
    connect(this,SIGNAL(notifyUpdate()),monitor,SLOT(updateDiskUI()));
    monitor ->show();
}


void Widget::on_creat_clicked()
{

}

void Widget::on_btn_menu_item_1_clicked()
{

}

void Widget::on_btn_menu_item_2_clicked()
{

}

void Widget::on_btn_menu_item_3_clicked()
{

}

void Widget::on_btn_menu_item_4_clicked()
{

}

void Widget::on_btn_menu_item_5_clicked()
{

}

void Widget::updateMemoryUI()
{
    // 备用
}

void Widget::updateDiskUI()
{
    // 备用
}
