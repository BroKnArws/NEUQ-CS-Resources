#include "cglobal.h"


CGlobal::CGlobal()
{

}

// 初始化内存互斥信号量
QSemaphore* CGlobal::mSem = new QSemaphore(1);
QSemaphore* CGlobal::delThreadSem = new QSemaphore(1);
QSemaphore* CGlobal::genThreadSem = new QSemaphore(1);
// 初始化管理器
DiskManager* CGlobal::dManager = new DiskManager();
FolderManager* CGlobal::fManager = new FolderManager(CGlobal::dManager);
MemoryManager* CGlobal::mManager = new MemoryManager(CGlobal::dManager);
