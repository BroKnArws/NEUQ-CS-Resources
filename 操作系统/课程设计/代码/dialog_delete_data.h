#ifndef DIALOG_DELETE_DATA_H
#define DIALOG_DELETE_DATA_H

#include <QDebug>
#include <QQueue>
#include <QDialog>
#include <QListView>
#include <QList>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include "cglobal.h"
#include "mymessagebox.h"

namespace Ui {
class dialog_delete_data;
}

class dialog_delete_data : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_delete_data(QWidget *parent = nullptr);
    ~dialog_delete_data();

private:
    Ui::dialog_delete_data *ui;
    QListView *lv_fileLists;
    QQueue<FCB*> tmpFCB;
    QStandardItemModel * model;
    MyMessageBox *myMbox;

    // 选中的行数
    int row_selected;

    // QWidget interface
    QLabel* ll_owner;
    QLabel* ll_fileSize;
protected:
    void closeEvent(QCloseEvent *event);
    void getFileList();
signals:
    void dataUpdated();


public slots:
    void on_pushButton_clicked();
    // 点击文件
    void showClick(QModelIndex index);
    // 刷新文件列表
    void refresh();

};

#endif // DIALOG_DELETE_DATA_H
