#include "pch.h"
#include <iostream>

using namespace std;

typedef struct {
	int row, col;   //该数据所在 row 行 col 列
	int elem;      //存储的数据
}Triple;

typedef struct {
	Triple data[100];   //非零元的数据构成的数组
	int rows, cols, num;  //该压缩前矩阵的行数，列数，非零元个数
}TSMatrix, *TSM;

void TSMatrixInit(TSMatrix *M, int a[100][100])
{
	cout << "输入矩阵的行和列 ：" << endl;
	int m, n, i, j;
	cin >> m;
	cin >> n;
	cout << "输入 " << m << "行 " << n << "列的矩阵" << endl;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	M->rows = i;
	M->cols = j;
	int k = 0;		//计数器
	for (i = 0; i < M->rows; i++)
	{
		for (j = 0; j < M->cols; j++)
		{
			if (a[i][j])  //如果非0
			{
				M->data[k].elem = a[i][j];
				M->data[k].row = i;
				M->data[k].col = j;
				k++;
			}
		}
	}
	M->num = k;

}

void TSMatrixAdd(TSMatrix *M, TSMatrix *T,TSMatrix *S)
{
	int k = M->num;
	S->num = M->num; S->rows = M->rows; S->cols = M->cols;
	for (int i = 0; i < M->num; i++)
	{
		S->data[i].elem = M->data[i].elem;
		S->data[i].row = M->data[i].row;
		S->data[i].col = M->data[i].col;
	}
	bool flag = 1;
	for (int i = 0; i < M->num; i++)
	{
		flag = 1;
		for (int j = 0; j < k; j++)
		{
			if (T->data[i].row == S->data[j].row&&T->data[i].col==S->data[j].col)
			{
				S->data[j].elem += T->data[i].elem;
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			S->data[k].elem = T->data[i].elem;
			S->data[k].col = T->data[i].col;
			S->data[k].row = T->data[i].row;
			k++;
			S->num++;
		}

	}
}

void TSMatrixShow(TSMatrix *T)
{
	cout << "相加后为 ：" << endl;
	bool sign = 1;
	for (int i = 0; i < T->rows; i++)
	{
		for (int j = 0; j < T->cols; j++)
		{
			sign = 1;
			for (int k = 0; k < T->num; k++)
			{
				if (T->data[k].row == i && T->data[k].col == j)
				{
					cout << T->data[k].elem << " ";
					sign = 0;
				}
			}
			if (sign)
			{
				cout << int(0) << " ";
			}

		}
		cout << endl;
	}
}

int main()
{
	int a[100][100];
	TSM M, T,S;
	M = new TSMatrix;
	T = new TSMatrix;
	S = new TSMatrix;
	TSMatrixInit(M, a);
	TSMatrixInit(T, a);
	TSMatrixAdd(M, T, S);
	TSMatrixShow(S);

}