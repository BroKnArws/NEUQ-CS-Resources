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
}TSMatrix,*TSM;

void TSMatrixInit(TSMatrix *M,int a[100][100])
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

void TransTSMatrix(TSMatrix *M,TSMatrix *T)  //快速转置
{
	int colbegin[100];   //记录转置前矩阵每一列第一个非零元的恰当位置的数组集合
	int colnum[100];     //记录每一列的非零元数量的数组集合           
	colbegin[0] = 0;     //第一列第一个非零元记录为1，example: colnum[0]=2 =>colbegin[1]=0+2=2;
	int k = 1; //计数器
	for (int m = 0; m < M->cols; m++)  //每列非零元初始化0
	{
		colnum[m] = 0;
	}
	for (int i = 0; i < M->num; i++)   //记录每列非零元个数
	{
		colnum[M->data[i].col]++;
	}
	for (int j = 0; j < M->cols; j++)  //记录每列起始非零元位
	{
		colbegin[k] = colbegin[k - 1] + colnum[j];
		k++;
	}
	//开始转置
	T->cols = M->rows;
	T->rows = M->cols;
	T->num = M->num;
	for (int i = 0; i < M->num; i++)
	{
		int co;
		co = M->data[i].col;   //第i个数据的列数给co
		int q;
		q = colbegin[co];      //此列数对应到该列的起始位置
		T->data[q].row = M->data[q].col;
		T->data[q].col = M->data[q].row;
		T->data[q].elem = M->data[q].elem;
		colbegin[co]++;        //该列对应的起始位置++
	}
}

void TSMatrixShow(TSMatrix *T)
{
	cout << "转置后为 ：" << endl;
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
	TSM M, T;
	int a[100][100];
	M = new TSMatrix;
	T = new TSMatrix;
	TSMatrixInit(M,a);
	TransTSMatrix(M, T);
	TSMatrixShow(T);
}