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

/* ��ϣ�����������Ǳ� */
int Hash(int key)
{
	return key % addrNum;
}



/* ���ϣ���в���ؼ��� */
void add(HashMap *hashmap, int key)
{
	int address = Hash(key);
	HashNode *p = hashmap->adr[address].firstout;
	HashNode *temp = p;
	/* flag=0 ��������ͬ�ؼ��� flag=1 ������ͬ�ؼ��� */
	int flag = 0;
	while (p)
	{
		/* ����г�ͻ������Ӹùؼ��ʵĴ�Ƶ */
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
	/* ���û�г�ͻ������ӹؼ�������β */
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

			/* !����ʹ��hash��������Ϊ����Ƕ��������ݵĹ�ϣӳ�䣬�����Ƕ�С�ļ����ݵĹ�ϣӳ�� */
			int value = key[start] % maxNum;

			int order = value / period;

			/* ����ϣֵ���л��֣�ÿ���ļ��洢һ������Ĺ�ϣֵ��Ӧ�Ĺؼ��� */
			fwrite(&key[start], sizeof(int), 1, fouts[order]);
			processAnimation(cur++, maxNum);
			start++;
		}

	}

}

/* ���������ϣ�������Ƶ�Լ�����Ƶ��Ӧ�Ĺؼ��� */
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