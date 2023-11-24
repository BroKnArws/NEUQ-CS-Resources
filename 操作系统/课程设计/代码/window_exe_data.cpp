#include "window_exe_data.h"
#include "ui_window_exe_data.h"

window_exe_data::window_exe_data(QWidget *parent,TCB* tcb) :
    QWidget(parent),
    ui(new Ui::window_exe_data)
{
    ui->setupUi(this);
    this->tcb = tcb;
    fileSelected = nullptr;
    this->setWindowTitle("数据执行");
    // 关闭即销毁
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    // 定义
    lv_fileList = ui->lv_fileList;
    ll_owner = ui->text_owner;
    ll_fileName = ui->text_fileName;
    ll_fileSize = ui->text_fileSize;
    ll_createTime = ui->text_createTime;
    ll_loadFile = ui->text_loadFiles;
    nb_pageNumber = ui->nb_pageNumber;
    tb_outputBuffer = ui->tb_outputBuffer;
    // 是否已经打开文件
    isInUse = false;

    model = new QStandardItemModel();
    lv_fileList->setModel(model);
    connect(lv_fileList,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));

    updateFiles();
}

window_exe_data::~window_exe_data()
{
    delete ui;
}

// 读入按钮被按下
void window_exe_data::on_pushButton_clicked()
{
    // 加锁
    CGlobal::mSem->acquire();
    //ui->pushButton->setDisabled(true);
    // 获取页号数
    int page = nb_pageNumber->value();
    // 在内存中读取数据
    auto status = CGlobal::mManager->read(tcb,page);
    // 通过string来判断
    if (status.code == STATUS_OK){
        // 没有发生换页

    } else if (status.code == STATUS_MEMORY_EXIST){
        // 直接引用内存
        QMessageBox * box = new QMessageBox();
        box->setText("内存中已存在该页，内存块号为："+QString::number(status.mBlock));
        box->exec();
    }
    else if (status.code == STATUS_EXCHANGE_PAGE){
        // 发生了换页
        QMessageBox * box = new QMessageBox();
        box->setText("发生LRU全局置换，替换的内存块号为："+QString::number(status.mBlock));
        box->exec();
    }
    // 更新UI
    tb_outputBuffer->append("第"+QString::number(page)+"页数据："+QString::fromStdString(status.data));
    // 通知主线程
    emit notifyUpdate();
    // 解锁
    CGlobal::mSem->release();
}

// 更新文件列表
void window_exe_data::updateFiles()
{
    qDebug() << "执行线程：更新文件列表";
    model->clear();
    queue<FCB*> q = CGlobal::fManager->getFiles();
    // 备份一份
    while(!q.empty()){
        FCB* fcb = q.front();
        QStandardItem * item = new QStandardItem();
        item->setEditable(false);
        item->setText(QString::fromStdString(fcb->fileName));
        model->appendRow(item);
        q.pop();
        tmpFCB.push_back(fcb);
    }
}

// 锁定一个数据执行线程只能访问一个文件，要访问第二个文件需要打开多个窗口
void window_exe_data::on_btn_load_clicked()
{
    // fileSelected 指向选中文件的指针
    if(fileSelected == nullptr){
        auto box = new QMessageBox();
        box->setText("未选择文件");
        box->exec();
    } else {
        tcb->fcb = fileSelected;
        // 在tcb中加入读入的数据
        tcb->data = CGlobal::fManager->getData(tcb->fcb);
        // 上锁，在窗口关闭的时候解锁
        int status = CGlobal::mManager->allocMemory(tcb);
        if (status == STATUS_OK){
            CGlobal::fManager->lockFile(fileSelected);
            isInUse = true;
            // 在创建数据执行线程时，已经在FCB中分配了4个内存，所以直接禁用调入内存等
            ((QPushButton*)sender())->setEnabled(false);
            lv_fileList->setDisabled(true);
            ll_loadFile->setText(QString::fromStdString(fileSelected->fileName));
            // 设置页号范围
            int blockSize = fileSelected->fileSize;
            if (blockSize <= 0){
                nb_pageNumber->setRange(0,0);
                // 不允许读入
            } else {
                nb_pageNumber->setRange(0,blockSize-1);
                ui->pushButton->setEnabled(true);
            }
            emit notifyUpdate();
        } else {
            QMessageBox *box = new QMessageBox();
            box->setText("内存不足，无法打开更多的执行线程，请关闭一些执行线程再重试");
            box->exec();
        }
    }
}

void window_exe_data::showClick(QModelIndex index)
{
    FCB* fcb = tmpFCB.at(index.row());
    ll_owner->setText(QString::fromStdString(fcb->owner));
    ll_fileName->setText(QString::fromStdString(fcb->fileName));
    ll_fileSize->setText(QString::number(fcb->fileSize));
    ll_createTime->setText(parseTM(fcb->createTime));
    fileSelected = fcb;
}

void window_exe_data::closeEvent(QCloseEvent *event)
{
    // TODO 清除内存，先获取信号量
    CGlobal::mSem->acquire();
    int status = CGlobal::mManager->freeBlock(this->tcb);
    if(status == STATUS_OK){
        qDebug() << "内存管理器返回正常，内存已清除" ;
    } else {
        qDebug() << "警告！内存泄露，清除失败" ;
    }

    if (isInUse && fileSelected != nullptr){
        // 解锁
        CGlobal::fManager->unlockFile(fileSelected);
    }

    CGlobal::mSem->release();
    // 发射信号
    emit notifyUpdate();
}
