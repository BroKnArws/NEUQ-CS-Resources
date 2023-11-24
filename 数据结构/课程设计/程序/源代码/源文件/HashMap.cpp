#include"pch.h"

#define _CRT_SECURE_NO_WARNINGS

#include"animation.h"
#include"HashMap.h"


void InitHashMap(HashMap *hashmap)
{
	hashmap->adr = new HashElem[addrNum];
	for (int i = 0; i < addrNum; i++)
	{
		hashmap->adr[i].firstout = NULL;
	}
	hashmap->num = addrNum;
}

/* 哈希函数，除数是表长 */
int Hash(int key)
{
	return key % addrNum;
}



/* 向哈希表中插入关键字 */
void add(HashMap *hashmap, int key)
{
	int address = Hash(key);
	HashNode *p = hashmap->adr[address].firstout;
	HashNode *temp = p;
	/* flag=0 不存在相同关键字 flag=1 存在相同关键字 */
	int flag = 0;
	while (p)
	{
		/* 如果有冲突，则添加该关键词的词频 */
		if (p->key == key)
		{
			p->value++;
			flag = 1;
			break;
		}
		else
		{
			temp = p;
			p = p->next;
		}
	}
	/* 如果没有冲突，则添加关键词至表尾 */
	if (!flag)
	{
		if (temp == p)
		{
			p = new HashNode;
			p->next = hashmap->adr[address].firstout;
			hashmap->adr[address].firstout = p;
		}
		else
		{
			p = new HashNode;
			p->next = temp->next;
			temp->next = p;
		}
		p->value = 1;
		p->key = key;
	}
}



void divideIntoFilesByHash(int key[], int start, int end, FILE* fouts[], int &cur)
{
	while (start < end)
	{
		if (key[start] < 0)
		{
			break;
		}
		else
		{
			int period = addrNum;

			/* !不能使用hash函数，因为这个是对所有数据的哈希映射，而不是对小文件数据的哈希映射 */
			int value = key[start] % maxNum;

			int order = value / period;

			/* 将哈希值进行划分，每个文件存储一定区间的哈希值对应的关键字 */
			fwrite(&key[start], sizeof(int), 1, fouts[order]);
			processAnimation(cur++, maxNum);
			start++;
		}

	}

}

/* 返回这个哈希表的最大词频以及最大词频对应的关键词 */
void findMaxOccurrence(HashMap *hashmap, int &maxkey, int &maxFrequency)
{
	maxkey = -1;
	maxFrequency = -1;
	for (int i = 0; i < hashmap->num; i++)
	{
		HashNode *p = hashmap->adr[i].firstout;
		while (p)
		{
			if (p->value > maxFrequency)
			{
				maxkey = p->key;
				maxFrequency = p->value;
			}
			p = p->next;
		}
	}
}

void destory(HashMap *hashmap)
{
	for (int i = 0; i < hashmap->num; i++)
	{
		HashNode *p = hashmap->adr[i].firstout;
		HashNode *q = p;
		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}
	}
	delete[] hashmap->adr;
	delete hashmap;
}