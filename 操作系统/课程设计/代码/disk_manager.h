#ifndef DISKMANAGER_H
#define DISKMANAGER_H
#define BLOCK_SIZE   4
#include <queue>
#include "data_define.h"
// 序列化存盘
#include "cereal/archives/json.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/string.hpp"

class DiskManager
{
public:
    //磁盘空间
    string disk[1024];

    //位示图
    BitMapItem Map[1024];

    // 构造函数
    DiskManager();

    //删除对换区数据
    int deleteBlock(FCB *e);

    //磁盘分配
    int changeBlock(FCB *e,string dt,int number);

    //释放盘块
    int ReleaseBlock(FCB *e);

    // 从内存接收对换数据  换入数据
    int receiveM(FCB * e,int pageNumber,string data);

    //对内存输出对换数据   换出数据
    string returnM(FCB* e,int number);

    // 目录管理申请删除
    int receiveF_delete(FCB * e);

    // 目录管理申请添加
    int receiveF_add(FCB *e,string data);

    // 目录管理申请读取
    string receiveF_read(FCB* e);

    // 输出接口，输出位示图，注意：输出当前位示图中的每一个元素，用queue传值
    queue<BitMapItem> getCurrentBitMap();

    //根据文件大小分配索引的盘块号
    Index_File indexFile(int filesize);

    // 序列化函数
    template<class Archive>
    void serialize(Archive & ar){
        ar(CEREAL_NVP(disk),CEREAL_NVP(Map));
    }

};



#endif // DISKMANAGER_H
