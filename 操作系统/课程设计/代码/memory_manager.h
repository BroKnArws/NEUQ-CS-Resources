#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <QString>
#include <QRandomGenerator>
#include "data_define.h"
#include "disk_manager.h"

typedef struct MemoryBlock{
    //内存块链表
    int free_length = 0;  //空闲块的数量
    MemoryBlockItem block_item;
    MemoryBlock* next;
}MemoryBlock, *MemoryBlockList;

typedef struct BlockPage{
    //线程的页块对应
    int block_id;  //每个线程页对应的内存块号，-1为不在内存中
    int page_id;   //线程页号
    string page_data;  //每页数据
}BlockPage;

typedef struct PageTable{
    //存放内存页号-TCB-文件页号-数据页表的链
    TCB *tcb;  //线程标识
    vector<BlockPage> table;  //线程的页表中的数据结构
    PageTable * next;
} * TableList;

class MemoryManager
{
public:
    //声明一个内存块链表
    MemoryBlockList mem_list;

    //声明映射表
    TableList tableList;

    DiskManager * dManager;

    // 构造函数
    MemoryManager(DiskManager * dManager);

    // 分配内存，分配成功isAlloc <- true.
    int allocMemory(TCB *t);

    // 释放TCB里面的数据
    int freeBlock(TCB *t);

    // 从内存读取数据，index
    ReadStat read(TCB *t,int pageIndex);

//    // 回写数据
//    int writeBack(TCB* t,int pageIndex);
//
    // 读取换出页的数据
    string loadWriteBackData(TCB* t,int pageIndex);

    // 输出当前MemoryBlock的状态
    queue<MemoryBlockItem> getCurrentMemoryBlock();

    //更新内存块调用时间
    static void reGetAccessTime(MemoryBlock *mb);

    //更新内存块分配时间
    static void getEnterTime(MemoryBlock *mb);

    //更新页表链
    void creatPageTable(TCB *t);

    //处理缺页
    int loosePage(TCB *t, int pageIndex, string data);

    //页面置换算法
    int LRU(TCB *t, int pageIndex, string data);

    //获取最近最久未访问的内存块号
    int lruBlockId();
};

#endif // MEMORYMANAGER_H
