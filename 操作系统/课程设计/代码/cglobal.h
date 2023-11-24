#ifndef CGLOBAL_H
#define CGLOBAL_H

#include "disk_manager.h"
#include "folder_manager.h"
#include "memory_manager.h"
#include <QSemaphore>
#include <QWidget>

class CGlobal
{
public:
    CGlobal();

    // 磁盘管理
    static DiskManager* dManager;
    static FolderManager* fManager;

    static QSemaphore* mSem;
    // 内存管理器，其内存为互斥量
    static MemoryManager* mManager;

    // 公有变量
    static QSemaphore* genThreadSem;
    static QSemaphore* delThreadSem;


};


#endif // CGLOBAL_H
