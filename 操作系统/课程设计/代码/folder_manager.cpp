#include "folder_manager.h"
#include "data_define.h"
#include <queue>
#include <fstream>

FolderManager::FolderManager(DiskManager * dManager)
{
        this->dManager = dManager;

        std::ifstream os("folder.json");
        if (os.is_open()){
            cereal::JSONInputArchive archieve(os);
            this->serialize(archieve);
            for(int i=0;i<128;i++){
                fileLocks[i] = false;
            }
        } else {
            for(int i=0;i<128;i++){
                fileTable[i].fileName = "";
                fileTable[i].fileSize = 0;
                fileTable[i].owner = "";
                fileTable[i].type = 0;
                fileLocks[i] = false;
            }
        }

}

// 按照指针指向的FolderElement删除目录项
int FolderManager::deleteData(FCB* element){
    // 删除磁盘中FCB
    for(int i=0;i<128;i++){
        if(element->fileName == fileTable[i].fileName){
            if (fileLocks[i]){
                //上锁了
                return STATUS_BUSY;
            } else {
                // 删除磁盘中的文件
                int status = this->dManager->receiveF_delete(element);
                // 删除目录项中的文件
                fileTable[i].fileName = "";
                fileTable[i].fileSize = 0;
                return status;
            }
        }
    }
}

// 输出信息：获取所有文件
queue<FCB*> FolderManager::getFiles(){
        queue<FCB*> q;
        for(int i=0;i<128;i++){
            if(fileTable[i].fileName != ""){
                q.push(&fileTable[i]);
            }
            else continue;
        }
        return q;
}

// 创建新文件，注意：添加时记得往element里面填写tm时间数据
int FolderManager::generateData(string data,string fileName,string owner){
        for(int k=0;k<128;k++){
            if(fileTable[k].fileName == fileName){
                return STATUS_SAME_FILE;
            }
        }
        // 获取时间
        for(int i=0;i<128;i++){
            if(fileTable[i].fileName == ""){
                fileTable[i].fileName = fileName;
                fileTable[i].owner = owner;//等待进一步优化
                int a;
                a = data.size();
                int b;
                if(a%4 == 0){
                    b = a/4;
                }
                else b = (a/4)+1;
                fileTable[i].fileSize = b;
                time_t t = time(nullptr);
                fileTable[i].createTime = *localtime(&t);               
                return this->dManager->receiveF_add(&fileTable[i],data);
            }
        }
        // 最多存放128个块
        return STATUS_ERR;
}

// 读取数据
string FolderManager::getData(FCB * element){
    string data_read = this->dManager->receiveF_read(element);
    return data_read;
}
int FolderManager::lockFile(FCB * fcb){
    for(int i=0;i<128;i++){
        if(fcb->fileName == fileTable[i].fileName){
            fileLocks[i] = true;
        }
    }
    return STATUS_OK;
}
int FolderManager::unlockFile(FCB * fcb){
    for(int i=0;i<128;i++){
        if(fcb->fileName == fileTable[i].fileName){
            fileLocks[i] = false;
        }
    }
    return STATUS_OK;
}
