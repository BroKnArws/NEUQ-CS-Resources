#pragma once
#include<iostream>


/* ���ֵĸ��� */
extern int maxNum;

/* ��ϣӳ���ֵ�ֿ�ŵ����ļ��ĸ��� */
extern int filesNum;

/* ÿ��С��ϣ��ĵ�ַ���� */
extern int addrNum;

using namespace std;

/* �����ÿ����� */
typedef struct HashNode {
	/* �ؼ��� */
	int key;
	/* ��¼����Ƶ�� */
	int value;
	/* ͬ��ַ����һ���ؼ��ֽ�� */
	HashNode *next;
};

/* �������� */
typedef struct
{
	HashNode* firstout;

}*HashList, HashElem;

/* ������ϣ�� */
typedef struct HashMap {
	HashList adr;
	/* �� */
	int num;
}HashMap;


/* ��ʼ����ϣ�� */
void InitHashMap(HashMap *hashmap);

/* ��ϣ���� */
int Hash(int key);

/* �����ļ����������ָ��ݹ�ϣֵ���䵽��ͬ�ļ���ȥ */
void divideIntoFilesByHash(int key[], int start, int end, FILE* fouts[], int &cur);

/* ���ϣ���в���ؼ��� */
void add(HashMap *hashmap, int key);

/* ���������ϣ�������Ƶ�Լ�����Ƶ��Ӧ�Ĺؼ��� */
void findMaxOccurrence(HashMap *hashmap, int &maxkey, int &maxFrequency);

/* ���ٹ�ϣ�� */
void destory(HashMap *hashmap);