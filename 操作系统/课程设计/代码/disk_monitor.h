#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

#include "data_define.h"
#include "cglobal.h"

#include <QDebug>
#include <QtGui>
#include <QStandardItemModel>
#include <QLabel>
#include <QMainWindow>
#include <QTableView>

namespace Ui {
class DiskMonitor;
}

class DiskMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiskMonitor(QWidget *parent = nullptr);
    ~DiskMonitor();


    QTableView* tv_disk;
    QStandardItemModel* model;

    QStandardItemModel* notFreeModel;
    QLabel *ll_data;
    QLabel *ll_status;
    QLabel *ll_pos;
    QLabel *ll_page;
    QLabel *ll_totoal_free;


private:
    Ui::DiskMonitor *ui;

    queue<BitMapItem> qMapTemp;
    BitMapItem bMItem[32][32];

signals:
    // 通知主线程更新线程
    void needUpdate();

public slots:
    // 刷新内存
    void updateDiskUI();
    // 点击表格事件
    void onTableClicked(const QModelIndex & mIndex);
};

#endif // DISK_MONITOR_H
