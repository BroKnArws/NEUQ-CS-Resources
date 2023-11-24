#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//最小化相关
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
//自定义弹窗
#include "mymessagebox.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <qboxlayout.h>
#include "gendatathread.h"
#include "window_exe_data.h"
#include <QDebug>
#include <queue>
#include "data_define.h"
#include "cglobal.h"
#include "memory_monitor.h"
#include "dialog_delete_data.h"
#include "dialog_gen_data.h"
#include <QMetaType>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    // Window
    window_exe_data * exeform;
    MemoryMonitor * mMonitor;

signals:
    void onMoveToPushButton(QString btnStr);

    void updateMemoryBitMap(queue<MemoryBlockItem> items);
    // 主线程发信号，通知两个监视器更新数据
    void notifyUpdate();


public slots:
    // 创建进程
    void createDataGenThread();
    void createDataDelThread();
    void createDataExeThread();

    // 打开监视
    void openDataGenUI();
    void openDataDelUI();
    void openDataExeUI(TCB* tcb);
    void openMemoryMonitor();
    void openDiskMonitor();


    // 更新槽，通知内存和磁盘监视器进行刷新
    void updateMemoryUI();
    void updateDiskUI();

    // 接受数据生成、删除线程传递的槽，通知主线程数据发生变化
    void updateData();


private slots:
    void closeEvent(QCloseEvent *event);

    void changeMboxReturn(int num);

    void on_btn_main_item_1_clicked();

    void on_btn_main_item_2_clicked();

    void on_btn_main_item_3_clicked();

    void on_btn_main_item_4_clicked();

    void on_btn_logout_clicked();

    void on_btn_littleshow_clicked();

    void on_creat_clicked();


    void on_btn_menu_item_1_clicked();
    void on_btn_menu_item_2_clicked();
    void on_btn_menu_item_3_clicked();
    void on_btn_menu_item_4_clicked();
    void on_btn_menu_item_5_clicked();

private:
    Ui::Widget *ui;

    MyMessageBox *myMbox;
    //自定义窗口通信参数
    int mbox_return;

    //最小化到托盘
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    //窗口管理动作
    QAction *returnNormal;
    QAction *quitAction;

    void initUi();          //Ui界面初始化函数
    void initMember();      //成员变量初始化函数
    void littleShow();      //最小化显示函数
};

#endif // WIDGET_H
