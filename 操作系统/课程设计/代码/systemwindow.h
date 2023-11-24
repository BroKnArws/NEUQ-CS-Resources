#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

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
class SystemWindow;
}

class SystemWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemWindow(QWidget *parent = nullptr);
    ~SystemWindow();

    // 功能
    QLabel * functionLabel;
    QPushButton * btn_gen_data;
    QPushButton * btn_del_data;
    QPushButton * btn_exe_data;
    QHBoxLayout * h1Layout;

    // 监视
    QLabel * monitorLabel;
    QPushButton * btn_memory_monitor;
    QPushButton * btn_disk_monitor;
    QHBoxLayout * h2Layout;

    // Window
    window_exe_data * exeform;
    MemoryMonitor * mMonitor;


signals:
    void onMoveToPushButton(QString btnStr);

    void updateMemoryBitMap(queue<MemoryBlockItem> items);
    // 主线程发信号，通知两个监视器更新数据
    void notifyUpdate();

public slots:
    // 状态显示
    void showMessageOnStatusBar(QString str);
    void showBtnTextOnStatusBar();

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

    // 显示等待框
    void showDialog(QDialog * dialog);
    void closeDialog(QDialog * dialog);
    void showMessage(QString str);

    // 更新槽，通知内存和磁盘监视器进行刷新
    void updateMemoryUI();
    void updateDiskUI();

    // 接受数据生成、删除线程传递的槽，通知主线程数据发生变化
    void updateData();


private:
    Ui::SystemWindow *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SYSTEMWINDOW_H
