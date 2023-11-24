#include "pch.h"
#include <iostream>
#include <malloc.h>

using namespace std;

typedef struct Quene
{
	int *num;
	int *Pch;
	int front;
	int rear;
	bool* isfull;
};

void QueneBuild(Quene *Q)
{
	cout << "有多少只猴子？" << endl;
	int n;
	cin >> n;
	Q->num = (int*)malloc(100 * sizeof(int));
	Q->Pch = (int*)malloc(100 * sizeof(int));
	Q->isfull = (bool*)malloc(100 * sizeof(bool));
	Q->front = Q->rear = 0;
	for (int i = 0; i < n; i++)
	{
		Q->num[i] = i + 1;
		Q->Pch[i] = 0;
		Q->isfull[i] = false;
		Q->rear++;
	}
}

void DividePeach(Quene *Q)
{
	cout << "每只猴子可以分到多少桃？" << endl;
	int m;
	cin >> m;
	cout << "筐里最大的桃子数是？ " << endl;
	int k;
	cin >> k;
	int elemnum = Q->rear;
	int b = 0;   //从0开始
	int isfullnum = 0;
	int BOXnum = 0;
	while (isfullnum != Q->rear)
	{
		for (int n = 1; n <= k; n++)
		{
			BOXnum += n;
			if (b == Q->rear)
			{
				b = 0;
			}
			if (!(Q->Pch[b] + BOXnum >= m) && !(Q->isfull[b]))
			{
				Q->Pch[b] += n;
				BOXnum = 0;
			}
			else if (!(Q->isfull[b]))
			{
				BOXnum -= m - Q->Pch[b];
				Q->Pch[b] = m;
				cout << Q->num[b] << " ";
				Q->isfull[b] = true;
				isfullnum++;
			}
			b++;
		}
	}
}
void QueneShow(Quene *Q)
{
	for (int i = 0; i < Q->rear; i++)
	{
		cout << "Q.num: " << Q->num[i] << " Q.Pch: " << Q->Pch[i] << " ";
		cout << endl;
	}
}
int main()
{
	Quene Q;
	QueneBuild(&Q);
	DividePeach(&Q);
}