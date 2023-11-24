#include "memory_manager.h"
#include <QString>
// 构造函数
MemoryManager::MemoryManager(DiskManager * dManager)
{
    this->dManager = dManager;
    mem_list = new MemoryBlock();
    mem_list->next = nullptr;
    for(int i = 0; i < 16; i++){  //初始化16个块的内存块链表
        auto mb = new MemoryBlock();
        mb->block_item.id = 15-i;
        mb->next = mem_list->next;
        mem_list->next = mb;
        mem_list->free_length++;
    }
    tableList = new PageTable();
    tableList->next = nullptr;
}

// 分配内存，分配成功isAlloc <- true.并且修改TCB中的block内存号
int MemoryManager::allocMemory(TCB *t){
    //分配内存空间
    if(mem_list->free_length >= 4){
        t->isAlloc = true;
        int mblock_num = 0;
        for(auto i = mem_list->next; i != nullptr && mblock_num < 4; i = i->next){
            if(i->block_item.isFree){
                t->mBlock[mblock_num] = i->block_item.id;  //给线程分配4个块的块号
                i->block_item.isFree = false;
                ++mblock_num;
                --mem_list->free_length;
                //更新内存块访问时间和分配时间
                getEnterTime(i);
                reGetAccessTime(i);
            }
        }
        //创建线程页表，并加入到页表链中
        //创建该线程的页表
        creatPageTable(t);
        return STATUS_OK;
    }
    return STATUS_FULL;
}

// 释放TCB里面的数据
int MemoryManager::freeBlock(TCB *t){
    //删除对换区
    //调用删除对换区函数
    if (t->fcb != nullptr){
        this->dManager->deleteBlock(t->fcb);
    }
    //更新页表链
    for(auto i = tableList; i->next != nullptr; i = i->next){
        if(i->next->tcb == t){
            auto p = i->next;
            i->next = p->next;
            free(p);
            break;
        }
    }
    //回收内存块，改变内存块状态
    for(int v : t->mBlock){
        for(auto i = mem_list->next; i != nullptr; i = i->next){
            if(i->block_item.id == v){
                //将对应块号的内存块释放
                i->block_item.isFree = true;
                ++mem_list->free_length;
                i->block_item.data = "";
                i->block_item.time.accessTime.tm_min = 0;
                i->block_item.time.accessTime.tm_sec = 0;
                i->block_item.time.accessTime.tm_hour = 0;
                break;
            }
        }
    }
    t->mBlock = {-1,-1,-1,-1};  //该TCB状态还原
    t->isAlloc = false;

    return STATUS_OK;
}

void MemoryManager::creatPageTable(TCB *t){
    //创建线程页表，并加入到页表链中
    //创建该线程的页表
    auto new_table = new PageTable();
    new_table->tcb = t;
    string s;  //创建线程页表新的页表项
    for(int k = 0; k < new_table->tcb->data.size(); ++k){
        //读取该线程数据
        s += new_table->tcb->data[k];
        if((k+1)%4 == 0 || k == (t->data.size()-1)){
            BlockPage table_item;
            table_item.page_id = k/4;  //填入页号
            table_item.block_id = -1;  //最开始没有页在内存中，每页对应的内存块号都是-1
            table_item.page_data = s;
            new_table->table.push_back(table_item);  //把页表项加入页表
            s = "";
        }
    }
    //加入页表链
    new_table->next = tableList->next;
    tableList->next = new_table;
}

// 从内存读取数据，pageIndex是页号
ReadStat MemoryManager::read(TCB *t, int pageIndex){
    ReadStat rst;
    string aim_data;
    for(auto i = tableList->next; i != nullptr; i = i->next){  //遍历页表链
        if(i->tcb == t){  //找到页表链中该线程的页表，t是调用的线程，i是该线程的页表
            bool page_out = true;  //越界标识
            bool loose_page = true;  //缺页标识
            //寻找页表中的目标页,若寻找到，把page_out改为false
            for(auto & j : i->table){
                //寻找到了目标页
                if(j.page_id == pageIndex){
                    //先将数据传给线程
                    aim_data = j.page_data;
                    page_out = false;
                    //该页已在内存中
                    if(j.block_id != -1){
                        loose_page = false;  //不缺页，页在内存中
                        rst.code = STATUS_MEMORY_EXIST;
                        rst.mBlock = j.block_id;
                        //更新内存块调用时间,并传内存块中的数据
                        for(auto memItem = mem_list->next; memItem != nullptr; memItem = memItem->next){
                            if(memItem->block_item.id == j.block_id){
//                                aim_data = memItem->block_item.data;
                                reGetAccessTime(memItem);
                                break;
                            }
                        }//访问结束
                    }
                    break;
                }
            }
            //没找到页
            if(page_out){
                rst.data = "页面越界";
                rst.code = 0;
                rst.mBlock = -1;
                return rst;
            }
            //缺页
            if(loose_page){
                //询问对换区
                string change_data = loadWriteBackData(t, pageIndex);
                //缺页处理
                rst.code = STATUS_EXCHANGE_PAGE;
                rst.mBlock = loosePage(t, pageIndex, aim_data);
            }
            break;
        }
    }
    rst.data = aim_data;
    return rst;
}

//// 回写数据，需要将strIndex/4转成页号
//int MemoryManager::writeBack(TCB* t,int pageIndex){
//
//}
//
// 读取从对换区请求的数据
string MemoryManager::loadWriteBackData(TCB*t,int pageIndex){
    string change_data;
    change_data = this->dManager->returnM(t->fcb, pageIndex);
    return change_data;
}

// 输出当前MemoryBlock的状态
queue<MemoryBlockItem> MemoryManager::getCurrentMemoryBlock(){
    queue<MemoryBlockItem> aim_queue;
    for(auto i = mem_list->next; i != nullptr; i = i->next){
        aim_queue.push(i->block_item);
    }
    return aim_queue;
}

//缺页处理
int MemoryManager::loosePage(TCB*t,int pageIndex, string data) {
    int aim_block = -1;  //要返回的内存块号
    //判断TCB中的内存块是否被用完
    bool all_used = true;
    for(auto v = tableList->next; v != nullptr; v = v->next){
        //定位到该TCB对应的页表，v就是页表
        if(v->tcb == t){
            int mblock_id;
            for(int i = 0; i < t->mBlock.size(); i++){
                mblock_id = t->mBlock[i];
                bool if_used = false;
                //查询线程的页表,判断该内存块是否被分配页
                for(auto & j : v->table){
                    if(j.block_id == mblock_id){
                        if_used = true;  //该tcb内存块已被分配页
                        break;
                    }
                }
                //该tcb内存块没被分配页，分配进去
                if(!if_used) {
                    all_used = false;//并不是全都被分页了
                    aim_block = mblock_id;
                    //更新页表项
                    for (auto &j : v->table) {
                        if (j.page_id == pageIndex) {
                            j.block_id = mblock_id;  //把块号填入页表项中
                            break;
                        }
                    }
                    //更新内存块链表
                    for(auto memItem = mem_list->next; memItem != nullptr; memItem = memItem->next){
                        if(memItem->block_item.id == mblock_id){
                            //向内存块中填装数据
                            memItem->block_item.data = data;
                            //更新访问时间
                            reGetAccessTime(memItem);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

    //tcb中的内存块都已被分配页
    if(all_used){
        //从空闲内存块区拿块
        if(mem_list->free_length >= 1){  //如果有空闲块
            int id = -1;
            //更新内存块链
            for(auto memItem = mem_list->next; memItem != nullptr; memItem = memItem->next){
                if(memItem->block_item.isFree){
                    //找到一个空闲块，并改变其状态
                    memItem->block_item.isFree = false;
                    //记录该内存块块号
                    id = memItem->block_item.id;
                    //更新内存块访问时间和分配时间
                    getEnterTime(memItem);
                    reGetAccessTime(memItem);
                    //往内存块中装入数据
                    memItem->block_item.data = data;
                    //空闲块数量减一
                    --mem_list->free_length;
                    break;
                }
            }
            //更新TCB中的信息,将新得的块号加入mblock数组
            t->mBlock.push_back(id);
            aim_block = id;
            //更新页表
            for(auto tb = tableList->next; tb != nullptr; tb = tb->next){
                if(tb->tcb == t){
                    //更新页表项
                    for (auto &j : tb->table) {
                        if (j.page_id == pageIndex) {
                            j.block_id = id;  //把块号填入页表项中
                            break;
                        }
                    }
                    break;
                }
            }
        }
        //无空闲块，置换
        else{
            aim_block = LRU(t, pageIndex, data);
        }

    }
    return aim_block;
}

//更新内存块分配时间
void MemoryManager::getEnterTime(MemoryBlock* mb) {
    time_t t =time(0);
    mb->block_item.time.enterTime = *localtime(&t);
}

//更新内存块被访问时间
void MemoryManager::reGetAccessTime(MemoryBlock* mb){
    time_t t =time(0);
    mb->block_item.time.accessTime = *localtime(&t);
}

//最近最久未访问
int MemoryManager::LRU(TCB *t, int pageIndex, string data) {
    //得到要被置换的页的内存块块号和换出的数据
    int lru_block = lruBlockId();
    string change_data;
    //定位内存块
    for(auto memItem = mem_list->next; memItem != nullptr; memItem = memItem->next){
        if(memItem->block_item.id == lru_block){
            change_data = memItem->block_item.data;
            //将目标页的数据装入该内存块
            memItem->block_item.data = data;
            //更新内存块访问时间
            reGetAccessTime(memItem);
            break;
        }
    }
    //确定被置换出的逻辑页和该页所属的fcb
    int change_page = -1;
    FCB * f = nullptr;
    //定位被置换的线程的页表和页表项
    PageTable * p = nullptr;
    for(auto tb = tableList->next; tb != nullptr; tb = tb->next){
        for(int i : tb->tcb->mBlock){
            if(i == lru_block){
                f = tb->tcb->fcb;
                p = tb;
                break;
            }
        }
        if(f != nullptr) break;
    }
    //定位到了被换线程的页表
    if(p != nullptr){
        //找到该页表中的页块对应
        for(auto & i : p->table){
            if(i.block_id == lru_block){
                //找到被换出的页
                change_page = i.page_id;
                i.block_id = -1;  //被置换后，该页处于未在内存状态
                break;
            }
        }
        //更新被置换的TCB的mblock,把块号从被置换线程中删去
        vector<int>::iterator it;
        for(it = p->tcb->mBlock.begin(); it != p->tcb->mBlock.end();){
            if(*it == lru_block){
                it = p->tcb->mBlock.erase(it);
            }
            else ++it;
        }
    }
    //更新执行线程的TCB的mblock,把块加到调用线程中
    int n = 0;
    for(int m : t->mBlock){
        if(m == lru_block){
            n = 1;
            break;
        }
    }
    if(n == 0){
        t->mBlock.push_back(lru_block);
    };
    //更新执行线程的页表项
    for(auto tb = tableList->next; tb != nullptr; tb = tb->next){
        if(tb->tcb == t){
            for(auto & i : tb->table){
                if(i.page_id == pageIndex){
                    i.block_id = lru_block;
                    break;
                }
            }
            break;
        }
    }
    //送回对换区数据，f,change_page,change_data
    this->dManager->receiveM(f, change_page, change_data);

    return lru_block;
}

int MemoryManager::lruBlockId() {
    //返回最近最久未访问的内存块号
    int lru_block = 0;
    //遍历内存块链表，寻找访问时间最久远的内存块
    MemoryBlock* aim_item = mem_list->next;
    for(auto memItem = mem_list->next->next; memItem != nullptr; memItem = memItem->next){
        //判断时间远近,有些未加页的内存块访问时间保持初始是一样的，选取第一个查询到的块
        if(aim_item->block_item.time.accessTime.tm_hour > memItem->block_item.time.accessTime.tm_hour){
            aim_item = memItem;
        }
        else if(aim_item->block_item.time.accessTime.tm_hour == memItem->block_item.time.accessTime.tm_hour){
            if(aim_item->block_item.time.accessTime.tm_min > memItem->block_item.time.accessTime.tm_min){
                aim_item = memItem;
            }
            else if(aim_item->block_item.time.accessTime.tm_min == memItem->block_item.time.accessTime.tm_min){
                if(aim_item->block_item.time.accessTime.tm_sec > memItem->block_item.time.accessTime.tm_sec){
                    aim_item = memItem;
                }
            }
        }
    }
    lru_block = aim_item->block_item.id;
    return lru_block;
}

