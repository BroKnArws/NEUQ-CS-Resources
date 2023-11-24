#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H
#define MAX_NUMBER_IN_BLOCK 2
#define MAX_BLOCK_NUMBER 900
#include <string>
#include <time.h>
#include <queue>
#include <iostream>
#include <QString>

// 序列化存盘
#include "cereal/archives/json.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/base_class.hpp"

// 目录项定义
using namespace std;

#define nullName "NUll"
#define nullData "NULL"
#define errorData "ERROR_RETURN"
// 正常返回
#define STATUS_OK 0
// 线程阻塞状态
#define STATUS_BUSY -1
// 内存/磁盘已满
#define STATUS_FULL -2
// 错误
#define STATUS_ERR -3
#define STATUS_MEMORY_EXIST -4
#define STATUS_EXCHANGE_PAGE -5
#define STATUS_SAME_FILE -6

//定义主文件目录MFD
typedef struct MFD
{
    //用户名
    char usrName[14];
    //用户密码
    char usrPwd[14];
    //用户的UFD所在的物理块号
    int link;
}MFD;

//定义一次间址的索引块；
struct Index_block_three
{
    int blocks[MAX_NUMBER_IN_BLOCK];

    template<class Archive>
    void serialize(Archive & ar){
        ar(CEREAL_NVP(blocks));
    }
};


//定义单级索引的数据结构
typedef struct Index_File
{
    //文件名
    string fileName;
    //文件大小
    int fileSize;
    //定义10个直接地址项
    int addr[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    //定义一次间址的地址项
    Index_block_three addr10;

    // 序列化函数
    template<class Archive>
    void serialize(Archive & ar){
        ar(CEREAL_NVP(fileName),CEREAL_NVP(fileSize),CEREAL_NVP(addr),CEREAL_NVP(addr10));
    }

}Index_File;

// cereal不支持tm类型
//typedef struct mTm{
//    int	tm_sec;		/* seconds after the minute [0-60] */
//    int	tm_min;		/* minutes after the hour [0-59] */
//    int	tm_hour;	/* hours since midnight [0-23] */
//    int	tm_mday;	/* day of the month [1-31] */
//    int	tm_mon;		/* months since January [0-11] */
//    int	tm_year;	/* years since 1900 */
//    int	tm_wday;	/* days since Sunday [0-6] */
//    int	tm_yday;	/* days since January 1 [0-365] */
//    int	tm_isdst;	/* Daylight Savings Time flag */
//    long	tm_gmtoff;	/* offset from UTC in seconds */
//    char	*tm_zone;	/* timezone abbreviation */

//    template<class Archive>
//    void serialize(Archive & ar){
//        ar(CEREAL_NVP(tm_sec),CEREAL_NVP(tm_min),CEREAL_NVP(tm_hour),CEREAL_NVP(tm_mday),CEREAL_NVP(tm_mon),CEREAL_NVP(tm_year),CEREAL_NVP(tm_wday));
//        // 存/取
//        ar(CEREAL_NVP(tm_yday),CEREAL_NVP(tm_isdst),CEREAL_NVP(tm_gmtoff)
//    }

//} Mtm;

typedef struct FCB{
    // 文件结构，文件为0，文件夹为1
    int type;
    string fileName;//文件名
    int fileSize;//文件块数
    string owner;
    // tm为C++标准时间struct
    //     struct tm {
    //       int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
    //       int tm_min;   // 分，范围从 0 到 59
    //       int tm_hour;  // 小时，范围从 0 到 23
    //       int tm_mday;  // 一月中的第几天，范围从 1 到 31
    //       int tm_mon;   // 月，范围从 0 到 11
    //       int tm_year;  // 自 1900 年起的年数
    //       int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
    //       int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
    //       int tm_isdst; // 夏令时
    //     }
    bool isInUse; // 是否正在使用
    tm createTime; // 创建的时间
    // 在磁盘中存放的地址
    Index_File iFile;

    // 序列化函数
    template<class Archive>
    void serialize(Archive & ar){
        ar(CEREAL_NVP(type),CEREAL_NVP(fileName),CEREAL_NVP(type),CEREAL_NVP(owner),CEREAL_NVP(fileSize),CEREAL_NVP(isInUse),CEREAL_NVP(iFile));
        // 存取时间
        ar(CEREAL_NVP(createTime.tm_min),CEREAL_NVP(createTime.tm_mon),CEREAL_NVP(createTime.tm_sec),CEREAL_NVP(createTime.tm_hour),CEREAL_NVP(createTime.tm_mday));
        ar(CEREAL_NVP(createTime.tm_wday),CEREAL_NVP(createTime.tm_yday),CEREAL_NVP(createTime.tm_year),CEREAL_NVP(createTime.tm_isdst));
    }

}FCB;

typedef struct BlockTime{
    //提供数据块进入模拟内存的时间
    tm enterTime;
    //访问时间
    tm accessTime;
} BlockTime;

// 线程管理模块
typedef struct TCB{
    FCB * fcb;
    string data;
    bool isAlloc = false; //分配后要把isAlloc改为true
    vector<int> mBlock = {-1,-1,-1,-1}; //4个block的内存块号
} TCB;

// 输出数据
void outputStr(string s);
QString parseTM(tm t);
QString parseTMSimple(tm t);

// 位示图表示，用于存放
typedef struct BitMapItem{
    bool isFree = true;
    string data;//注意，这个data最多只能有4个字符， 1个块4B
    string fileName;
    int pageNumber = -1;
    int x = -1; //位示图x轴，二维数组第1个下标
    int y = -1; //位示图y轴，二维数组第2个下标

    // 序列化函数
    template<class Archive>
    void serialize(Archive & ar){
        ar(CEREAL_NVP(isFree),CEREAL_NVP(data),CEREAL_NVP(fileName),CEREAL_NVP(pageNumber),CEREAL_NVP(x),CEREAL_NVP(y));
    }

} BitFreeMap;

// 内存块状况
typedef struct MemoryBlockItem{
    int id; //内存块号
    bool isFree = true;
    string data;//注意，这个data最多只能有4个字符， 1个块4B
    BlockTime time;
}MemoryBlockItem;


typedef struct ReadStat{
    int code; // 返回值
    string data; // 返回数据
    int mBlock; // 发生全局LRU置换的话，置换的是哪一块
}  ReadStat;


#endif // DATA_DEFINE_H
