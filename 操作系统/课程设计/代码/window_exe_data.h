#ifndef EXE_FORM_H
#define EXE_FORM_H

#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QWidget>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QQueue>
#include <QSpinBox>
#include <QTextBrowser>

#include "data_define.h"
#include "cglobal.h"

namespace Ui {
class window_exe_data;
}

class window_exe_data : public QWidget
{
    Q_OBJECT

public:
    explicit window_exe_data(QWidget *parent = nullptr,TCB* tcb=nullptr);
    ~window_exe_data();




private:
    Ui::window_exe_data *ui;
    QPushButton *btnRead;

    QListView* lv_fileList;
    QLabel * ll_createTime;
    QLabel * ll_owner;
    QLabel * ll_fileSize;
    QLabel * ll_fileName;
    QLabel * ll_loadFile;
    QStandardItemModel * model;
    QSpinBox * nb_pageNumber;
    QTextBrowser * tb_outputBuffer;

    QQueue<FCB*> tmpFCB;
    TCB* tcb;
    FCB* fileSelected;
    bool isInUse;

signals:
    // 做一次操作后，通知主线程更新
    void notifyUpdate();

public slots:
    void on_pushButton_clicked();
    // 更新文件列表
    void updateFiles();

    void on_btn_load_clicked();
    // 选择了文件
    void showClick(QModelIndex index);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // EXE_FORM_H
