#include "pch.h"

/* 忽略VS的安全警告 */
#define _CRT_SECURE_NO_WARNINGS

#include "HashMap.h"
#include"animation.h"
#include <stdio.h>
#include <io.h>
#include <fstream>
#include <iostream>
#include <direct.h>
#include <random>
#include <string>
#include<Windows.h>



using namespace std;

/* 数字的个数 */
int maxNum = 0;

/* 哈希映射的值分块放到的文件的个数 */
int filesNum = 0;

/* 每个小哈希表的地址个数 */
int addrNum = 0;


void createNewFile()
{
	int n;
	cout << "要生成多少个整数？（20亿个以内）" << endl;
	cin >> n;
	if (n <= 0) { Exception(1); return; }

	/* 更新全局变量 */
	maxNum = n;

	/* 计时器 */
	double start = clock();

	/* 伪随机数随机种子 */
	srand((unsigned)time(NULL));
	cout << "正在生成" << maxNum << "个数字到一个大文件，请稍等，可能需要较长时间..." << endl;

	FILE *fout = fopen("numbers.txt", "wb");
	if (!fout) { Exception(5); return; }

	/* 随机生成maxNum个数 */
	for (int i = 1; i <= maxNum; i++)
	{

		int temp = (int)((double)rand() / RAND_MAX * maxNum);
		fwrite(&temp, sizeof(int), 1, fout);

		/* 模拟进度条，方便查看进度 */
		processAnimation(i, maxNum);
	}
	fclose(fout);

	cout << endl << "生成完毕，总共耗时 " << (clock() - start) / CLOCKS_PER_SEC << "秒！" << endl;
	system("pause");

}

/* 加载大文件，同时通过哈希映射到若干文件上 */
void loadFile()
{
	FILE *fin;
	fin = fopen("numbers.txt", "rb");
	if (!fin) { Exception(5); return; }

	cout << "将关键词分配到多少个文件中？" << endl;
	int files;
	cin >> files;

	/* 异常处理 */
	if (files <= 0) { Exception(1); return; }
	if (maxNum%files != 0) { Exception(3); return; }

	/* 获得文件字节大小（end)以及数字个数（len） */
	fpos_t end;
	fpos_t now = -1;
	fseek(fin, 0, SEEK_END);
	fgetpos(fin, &end); //获取文件大小
	long int len = end / sizeof(int);
	rewind(fin);

	/* 修正数字个数，文件个数和小哈希表表长 */
	maxNum = len;
	if (!maxNum) { Exception(2); return; }
	filesNum = files;
	addrNum = maxNum / filesNum;

	cout << "开始加载大文件，需要较长时间，请稍等..." << endl;
	double start = clock();

	/* 规定从缓冲区读取的字节个数 */
	const int buffnum = 1024;
	int buff[buffnum];

	char filePath[20];

	FILE** fouts = new FILE*[filesNum];

	/* 预载所有文件指针，避免频繁开关输出流 */
	for (int order = 0; order < filesNum; order++)
	{
		sprintf(filePath, "Collection\\%d.txt", order);
		remove(filePath);
		fouts[order] = fopen(filePath, "ab+");
	}

	int cur = 0;
	while (now!=end)
	{
		fread(buff, sizeof(int) * buffnum, 1, fin);
		fgetpos(fin, &now);
		/* 进行哈希映射并分到各个小文件 */
		divideIntoFilesByHash(buff, 0, buffnum, fouts, cur);
	}

	cout << "成功通过哈希函数映射值将关键字分配到" << filesNum << "个文件中,，总共耗时 " << (clock() - start) / CLOCKS_PER_SEC << "秒！" << endl;

	/* 关闭所有文件指针 */
	for (int order = 0; order < filesNum; order++)
	{
		fclose(fouts[order]);
	}
	fclose(fin);

	system("pause");
}

/* 返回出现次数最多的 数字数组 和 频次数组 的下标 */
int getMax(int *maxfrequency, int *maxkeys)
{
	int max = -1;
	int cur = -1;
	for (int i = 0; i < filesNum; i++)
	{
		if (max < maxfrequency[i])
		{
			cur = i;
			max = maxfrequency[i];
		}
	}
	return cur;

}


/* 在所有哈希表中寻找出现频次最多的关键词 */
void findMaxOccurrences()
{
	/* 如果没有加载过文件 */
	if (_access("Collection\\0.txt", 0) == -1) { Exception(4); return; }
	if (!addrNum || !filesNum) { Exception(2); return; }

	/* 每个文件出现次数最多的关键词数组以及它们对应的出现频次 */
	int *maxkeys = new int[filesNum];
	int *maxfrequency = new int[filesNum];

	cout << "开始对每个小文件进行哈希表存储和关键词筛选，请稍等..." << endl;
	for (int i = 0; i < filesNum; i++)
	{
		HashMap *hashmap = new HashMap;
		InitHashMap(hashmap);

		char filePath[20];
		sprintf(filePath, "Collection\\%d.txt", i);

		FILE *fin = fopen(filePath, "rb");

		int key;

		fseek(fin, 0, SEEK_END);
		int end = ftell(fin);
		rewind(fin);

		int n = 0;
		while (ftell(fin) != end)
		{
			processAnimation(n++, addrNum);
			fread(&key, sizeof(int), 1, fin);
			add(hashmap, key);
		}
		fclose(fin);

		maxfrequency[i] = -1;
		/* 获取这个文件的频次最高关键词及其频次 */
		findMaxOccurrence(hashmap, maxkeys[i], maxfrequency[i]);
		if (maxfrequency[i] != -1)
		{
			cout << "第" << i + 1 << "个文件的出现次数最多的数字是：" << maxkeys[i] << "，出现了 " << maxfrequency[i] << " 次。" << endl;
		}
		else
		{
			cout << "第" << i + 1 << "个文件没有数字存储。" << endl;
		}
		destory(hashmap);
	}

	/* 移除文件 */
	for (int i = 0; i < filesNum; i++)
	{
		char filePath[20];
		sprintf(filePath, "Collection\\%d.txt", i);
		remove(filePath);
	}

	int maxcur = getMax(maxfrequency, maxkeys);
	cout << endl << "----------------------------------------------------------------↓" << endl;
	cout << "综上，出现次数最多的数字是：" << maxkeys[maxcur] << ", 出现次数是" << maxfrequency[maxcur] << "次" << endl;
	system("pause");
}

void inquire()
{
	cout << "当前的各项参数如下：" << endl;
	cout << "生成的数字个数：";
	if (!maxNum) { cout << "未初始化" << endl; }
	else { cout << maxNum << endl; }
	cout << "分配的文件个数：";
	if (!filesNum) { cout << "未初始化" << endl; }
	else { cout << filesNum << endl; }
	cout << "每个小哈希表的表长：";
	if (!addrNum) { cout << "未初始化" << endl; }
	else { cout << addrNum << endl; }
	system("pause");
}

void manualSetting()
{
	cout << "请输入已存在的大文件的数字个数" << endl;
	int num;
	cin >> num;
	if (num <= 0) { Exception(1); return; }
	maxNum = num;
	cout << "设置成功！" << endl;
	system("pause");
}


//case 5:inquire(); break;
int main()
{
	while (1)
	{
		int opt = menuShow();
		switch (opt)
		{
		case 1:createNewFile(); break;
		case 2:loadFile(); break;
		case 3:findMaxOccurrences(); break;
		case 4:inquire(); break;
		default:exit(0); break;

		}
	}

}
