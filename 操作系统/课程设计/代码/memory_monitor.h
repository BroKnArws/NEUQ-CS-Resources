#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "cglobal.h"
#include <QDebug>
#include <QTableView>

namespace Ui {
class MemoryMonitor;
}

class MemoryMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MemoryMonitor(QWidget *parent = nullptr);
    ~MemoryMonitor();

    // 表格属性
    QTableView *tv_memory;
    QStandardItemModel * model;

signals:
    // 通知主线程更新线程
    void needUpdate();

public slots:
    // 刷新内存
    void updateMemoryUI();


private:
    Ui::MemoryMonitor *ui;
};

#endif // MEMORY_MONITOR_H
