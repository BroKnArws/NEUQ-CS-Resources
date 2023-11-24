#include "disk_monitor.h"
#include "ui_disk_monitor.h"

DiskMonitor::DiskMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiskMonitor)
{
    ui->setupUi(this);
    this->setWindowTitle("磁盘监视器");
    // 关闭即销毁
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    // 定义
    tv_disk = ui->tv_disk;
    ll_pos = ui->text_block_pos;
    ll_data = ui->text_block_data;
    ll_page = ui->text_page;
    ll_status = ui->text_block_status;
    ll_totoal_free = ui->text_total_free_block;
    // 表格
    model = new QStandardItemModel(tv_disk);
    // 32*32
    model->setRowCount(32);
    model->setColumnCount(32);
    // 设置属性
    tv_disk->setModel(model);
    tv_disk->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    tv_disk->setEditTriggers(QTableView::NoEditTriggers);
//    tv_disk->setRowHeight(0,50);
    tv_disk->setSelectionMode(QAbstractItemView::SingleSelection);
//    tv_disk->horizontalHeader()->hide();
//    tv_disk->verticalHeader()->hide();
    // 初始化行号从0开始
    for (int i=0;i<model->rowCount();i++) {
        model->setHeaderData(i,Qt::Vertical,i);
    }
    for (int i=0;i<model->rowCount();i++) {
        model->setHeaderData(i,Qt::Horizontal,i);
    }
    // 设置点击事件
    connect(tv_disk, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
    // 获取数据
    notFreeModel = new QStandardItemModel(ui->tv_notFree);
    ui->tv_notFree->setModel(notFreeModel);
    ui->tv_notFree->setEditTriggers(QTableView::NoEditTriggers);

    updateDiskUI();
}

DiskMonitor::~DiskMonitor()
{
    delete ui;
}

void DiskMonitor::updateDiskUI()
{
    qDebug() << "磁盘监视器：更新数据";
    qMapTemp = CGlobal::dManager->getCurrentBitMap();
    int freeBlockCnt = 0;
    int totalBlock = 0;
    // 清空空闲分区
    notFreeModel->clear();
    while(!qMapTemp.empty()){
        auto item = qMapTemp.front();
        if(item.isFree){
            freeBlockCnt++;
        }
        totalBlock++;
        if (item.x >=0 && item.y >=0 && item.x <32 && item.y <32){
            QStandardItem * qItem =new QStandardItem(QString::fromStdString(item.data));
            model->setItem(item.x,item.y,qItem);
            if (!item.isFree){
                // 染色
                model->setData(model->index(item.x,item.y),QVariant(QBrush(Qt::red)), Qt::BackgroundRole);
                QStandardItem * it = new QStandardItem();
                it->setText(QString::fromStdString(item.data)+"-("+QString::number(item.x)+","+QString::number(item.y)+")");
                notFreeModel->appendRow(it);
            }
            this->bMItem[item.x][item.y] =item;
        } else {
            qDebug() << "警告：试图写入非法UI空间";
        }
        qMapTemp.pop();
    }
    ll_totoal_free->setText(QString::number(freeBlockCnt)+"/"+QString::number(totalBlock));
}

void DiskMonitor::onTableClicked(const QModelIndex &mIndex)
{
    auto item = bMItem[mIndex.row()][mIndex.column()];
    // 判断是否是坐标
    int index = mIndex.row()*32+mIndex.column();
    if(index >= 900){
        ll_page->setText(QString::number(index)+"(对换区)");
    } else {
        ll_page->setText(QString::number(index)+"(普通区)");
    }

    QString textStr = QString("(") +QString::number(item.x) + QString(",") +QString::number(item.y)+QString(")");
    ll_pos->setText(textStr);

    ll_data->setText(QString::fromStdString(item.data));
    if(item.isFree){
        ll_status ->setText("空闲");
    } else {
        ll_status ->setText("已被占用");
    }

}
