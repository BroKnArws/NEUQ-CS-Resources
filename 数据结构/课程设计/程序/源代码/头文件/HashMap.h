#pragma once
#include<iostream>


/* 数字的个数 */
extern int maxNum;

/* 哈希映射的值分块放到的文件的个数 */
extern int filesNum;

/* 每个小哈希表的地址个数 */
extern int addrNum;

using namespace std;

/* 链表的每个结点 */
typedef struct HashNode {
	/* 关键字 */
	int key;
	/* 记录出现频次 */
	int value;
	/* 同地址的下一个关键字结点 */
	HashNode *next;
};

/* 数组链表 */
typedef struct
{
	HashNode* firstout;

}*HashList, HashElem;

/* 整个哈希表 */
typedef struct HashMap {
	HashList adr;
	/* 表长 */
	int num;
}HashMap;


/* 初始化哈希表 */
void InitHashMap(HashMap *hashmap);

/* 哈希函数 */
int Hash(int key);

/* 将大文件的所有数字根据哈希值分配到不同文件中去 */
void divideIntoFilesByHash(int key[], int start, int end, FILE* fouts[], int &cur);

/* 向哈希表中插入关键字 */
void add(HashMap *hashmap, int key);

/* 返回这个哈希表的最大词频以及最大词频对应的关键词 */
void findMaxOccurrence(HashMap *hashmap, int &maxkey, int &maxFrequency);

/* 销毁哈希表 */
void destory(HashMap *hashmap);