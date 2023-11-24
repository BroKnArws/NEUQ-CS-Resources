#ifndef GENDATATHREAD_H
#define GENDATATHREAD_H

#include <qthread.h>
#include "data_define.h"
#include "cglobal.h"
#include <QSemaphore>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QMessageBox>

// 执行线程互斥访问信号量

class GenDataThread : public QThread
{
    Q_OBJECT
public:
    QString id = "生成数据线程";
    GenDataThread();


protected:
    void run();

signals:
    void showMessage(QString str);
    void openUI();

};



class DelDataThread : public QThread
{
    Q_OBJECT
public:
    QString id = "删除线程";
    DelDataThread();


protected:
    void run();

signals:
    void showMessage(QString str);
    void openUI();


};


class ExeDataThread : public QThread
{
    Q_OBJECT
public:
    QString id = "执行线程";
    ExeDataThread();

protected:
    void run();

signals:
    void openUI(TCB* tcb);
    // 通知内存有变动
    void notify();
    void showMessage(QString str);

public slots:

};

#endif // GENDATATHREAD_H
