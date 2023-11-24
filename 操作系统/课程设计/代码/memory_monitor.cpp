#include "memory_monitor.h"
#include "ui_memory_monitor.h"

MemoryMonitor::MemoryMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MemoryMonitor)
{
    ui->setupUi(this);
    this->setWindowTitle("内存监视器");
    // 关闭即销毁
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    // 定义
    tv_memory = ui->tv_memory;

    model = new QStandardItemModel(tv_memory);
    // 4列，内存号，内存内容，是否空闲，最近一次访问时间
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"内存号");
    model->setHeaderData(1,Qt::Horizontal,"内存内容");
    model->setHeaderData(2,Qt::Horizontal,"是否空闲");
    model->setHeaderData(3,Qt::Horizontal,"最近访问时间");
    // 设置属性
    tv_memory->setModel(model);
    tv_memory->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    tv_memory->setEditTriggers(QTableView::NoEditTriggers);
    tv_memory->setRowHeight(0,50);
    tv_memory->setSelectionMode(QAbstractItemView::SingleSelection);
    tv_memory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tv_memory->verticalHeader()->hide();

    // 刷新数据
    updateMemoryUI();
}

MemoryMonitor::~MemoryMonitor()
{
    delete ui;
}

// 刷新UI
void MemoryMonitor::updateMemoryUI()
{
    qDebug() << "内存监视器：更新数据";
    queue<MemoryBlockItem> items = CGlobal::mManager->getCurrentMemoryBlock();
    // 清空表格
    //model->removeRows(0,model->rowCount());

    int cnt = 0;
    while(!items.empty()){
        auto qitem = items.front();
        QStandardItem * id =new QStandardItem();
        QStandardItem * data =new QStandardItem();
        QStandardItem * isAlloc =new QStandardItem();
        QStandardItem * lTime = new QStandardItem();

        id->setTextAlignment(Qt::AlignCenter);
        data->setTextAlignment(Qt::AlignCenter);
        isAlloc->setTextAlignment(Qt::AlignCenter);
        lTime->setTextAlignment(Qt::AlignCenter);

        id->setText(QString::number(qitem.id));
        data->setText(QString::fromStdString(qitem.data));
        lTime->setText(parseTMSimple(qitem.time.accessTime));

        model->setItem(cnt,0,id);
        model->setItem(cnt,1,data);
        model->setItem(cnt,3,lTime);

        if(qitem.isFree){
            isAlloc->setText("是");
        }   else {
            isAlloc->setText("否");
        }
        model->setItem(cnt,2,isAlloc);
        items.pop();
        cnt++;
    }
}

