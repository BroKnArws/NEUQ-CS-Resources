#include "disk_manager.h"
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#define BlockNum     1024      //磁盘块的数目(编号从0开始)
#define BlockSize    4         //磁盘块大小
#define SystemSize   1024*4     //磁盘总容量
#define exchange_x   (900-1)/32       //对换区首址x
#define exchange_y   (900-1)%32       //对换区首址y
#define BLOCK_SIZE   4
// 初始化函数
DiskManager::DiskManager()
{
    std::ifstream os("disk.json");
    if (os.is_open()){
        cereal::JSONInputArchive archieve(os);
        this->serialize(archieve);
    } else {
        //分配1024*4B空间
        for(int i=0;i<1024;i++){
            Map[i].isFree = true;
            Map[i].x = (i)/32;
            Map[i].y = (i)%32;
            Map[i].data = nullData;
            disk[i] = nullData;
        }
    }
}
//生成第三层索引，并并根据blocks赋值，
Index_block_three indexBlockThree(int blocks[],int start,int end)
{
    Index_block_three ans;
    int j = 0;
    for(int i = start; i < end; i++)
    {
        ans.blocks[j++] = blocks[i];
    }
    return ans;
}


//给定一个文件的长度，给出模拟分配占用的磁盘块的情况
Index_File DiskManager::indexFile(int filesize)
{
    //计算该文件需要多少盘块
    int block_num = filesize % BLOCK_SIZE == 0 ? filesize / BLOCK_SIZE : filesize / BLOCK_SIZE + 1;
    //定义保存所有盘块号的数组
    int blocks[block_num];
    //初始化数组
    memset(blocks,0,sizeof(int) * block_num);

    //模拟系统分配空闲盘块号
    for(int i = 0; i < block_num; i++)
    {
        int temp = rand() % MAX_BLOCK_NUMBER;
        if(this->Map[temp].isFree == false)
        {
            temp = rand() % MAX_BLOCK_NUMBER;
        }
        this->Map[temp].isFree =true;
        blocks[i] = temp;
    }

    Index_File indexfile;
    indexfile.fileSize = filesize;
    //直接地址
    if(block_num <= 10)
    {
        for(int i = 0; i < block_num; i++)
        {
            indexfile.addr[i] = blocks[i];
        }
    }
        //一次间址
    else if(block_num <= MAX_NUMBER_IN_BLOCK + 10)
    {
        for(int i = 0; i < 10; i++)
        {
            indexfile.addr[i] = blocks[i];
        }
        indexfile.addr10 = indexBlockThree(blocks,10,block_num);
    }

    return indexfile;
}
//对换区磁盘分配
int DiskManager::changeBlock(FCB *e,string data,int number){
    for(int i=900;i<1024;i++){
        if(this->Map[i].isFree){
            this->Map[i].isFree = false;
            this->Map[i].fileName = e->fileName;
            this->Map[i].data = data;
            this->Map[i].pageNumber = number;
            this->disk[i] = data;
            return STATUS_OK;
        }
    }
    return STATUS_BUSY;
}
//删除对换区空间
int DiskManager::deleteBlock(FCB *e){
    for(int i=900;i<1024;i++){
        if(e->fileName == this->Map[i].fileName){
            this->Map[i].isFree = true;
            this->Map[i].fileName = nullName;
            this->Map[i].data = nullData;
            this->disk[i] = nullData;
        }
    }
    return STATUS_OK;
}
//释放盘块
int DiskManager::ReleaseBlock(FCB *e){
    for(int i=0;i<1024;i++){
        if(e->fileName == this->Map[i].fileName){
            this->Map[i].isFree = true;
            this->Map[i].fileName = nullName;
            this->Map[i].data = nullData;
            this->disk[i] = nullData;
        }
    }
    return STATUS_OK;
}
// 从内存接收对换数据  换入数据
int DiskManager::receiveM(FCB* e,int pageNumber,string data){
    if (pageNumber == -1){
        // 如果是空页，则直接返回
        return STATUS_OK;
    }
    for(int i=900;i<1024;i++){
        if(pageNumber == this->Map[i].pageNumber && e->fileName == this->Map[i].fileName){
            return STATUS_OK;
        }
    }
    changeBlock(e,data,pageNumber);
    return STATUS_OK;
}
//给内存输出对换数据  换出数据
string DiskManager::returnM(FCB* e,int number){
    string dataReturn;
    for(int i=900;i<1024;i++){
        if(number == this->Map[i].pageNumber && e->fileName == this->Map[i].fileName){
            dataReturn = this->Map[i].data;
            return dataReturn;
        }
    }
    return dataReturn;
}

// 目录管理申请删除
int DiskManager::receiveF_delete(FCB * e){
    for(int i=0;i<900;i++){
        if(Map[i].fileName == e->fileName){
            Map[i].isFree = true;
            Map[i].fileName = nullName;
            Map[i].data = nullData;
            disk[i] = nullData;
        }
    }
    return STATUS_OK;
}

// 目录管理申请添加
int DiskManager::receiveF_add(FCB *e,string data){
    // data在UI上限定死了，最大为96
    int a;
    a = data.size();
    e->iFile = indexFile(a);

    int fnumber = e->fileSize;
    int b[24] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    for(int i=0;i<10;i++){
        b[i] = e->iFile.addr[i];
    }
    switch (fnumber){
        case 11:{
            b[10] = e->iFile.addr10.blocks[0];
            break;
        }
        case 12:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 13:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 14:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 15:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 16:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 17:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 18:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 19:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 20:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 21:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 22:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 23:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 24:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        default:break;
    }
    for(int i=0,j=0;i<fnumber,j<a;i++,j=j+4){
        if((j+4)>=(a-1)){
            this->Map[b[i]].isFree = false;
            this->Map[b[i]].fileName = e->fileName;
            this->Map[b[i]].data = data.substr(j,a-j);
            this->disk[b[i]] = data.substr(j,a-j);
        }
        else{
            this->Map[b[i]].isFree = false;
            this->Map[b[i]].fileName = e->fileName;
            this->Map[b[i]].data = data.substr(j,4);
            this->disk[b[i]] = data.substr(j,4);
        }
    }
    //else return STATUS_ERR;
    return STATUS_OK;
}

// 目录管理申请读取
string DiskManager::receiveF_read(FCB* e){
    int fnumber = e->fileSize;
    int b[24] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    for(int i=0;i<10;i++){
        b[i] = e->iFile.addr[i];
    }
    switch (fnumber){
        case 11:{
            b[10] = e->iFile.addr10.blocks[0];
            break;
        }
        case 12:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 13:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 14:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 15:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 16:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 17:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 18:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 19:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 20:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 21:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 22:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 23:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        case 24:{
            b[10] = e->iFile.addr10.blocks[0];
            b[11] = e->iFile.addr10.blocks[1];
            break;
        }
        default:break;
    }
    string a;
    for(int j=0;j<fnumber;j++){
        a.append(Map[b[j]].data);
    }
    return a;
}


// 输出接口，输出位示图，注意：输出当前位示图中的每一个元素，用queue传值
queue<BitMapItem> DiskManager::getCurrentBitMap(){
    queue<BitMapItem> q;
    for(int i=0;i<1024;i++)q.push(this->Map[i]);
    return q;
}
