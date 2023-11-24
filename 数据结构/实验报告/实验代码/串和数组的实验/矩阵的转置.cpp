#include "pch.h"
#include <iostream>

using namespace std;

typedef struct {
	int row, col;   //���������� row �� col ��
	int elem;      //�洢������
}Triple;

typedef struct {
	Triple data[100];   //����Ԫ�����ݹ��ɵ�����
	int rows, cols, num;  //��ѹ��ǰ���������������������Ԫ����
}TSMatrix,*TSM;

void TSMatrixInit(TSMatrix *M,int a[100][100])
{
	cout << "���������к��� ��" << endl;
	int m, n, i, j;
	cin >> m;
	cin >> n;
	cout << "���� " << m << "�� " << n << "�еľ���" << endl;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	M->rows = i;
	M->cols = j;
	int k = 0;		//������
	for (i = 0; i < M->rows; i++)
	{
		for (j = 0; j < M->cols; j++)
		{
			if (a[i][j])  //�����0
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

void TransTSMatrix(TSMatrix *M,TSMatrix *T)  //����ת��
{
	int colbegin[100];   //��¼ת��ǰ����ÿһ�е�һ������Ԫ��ǡ��λ�õ����鼯��
	int colnum[100];     //��¼ÿһ�еķ���Ԫ���������鼯��           
	colbegin[0] = 0;     //��һ�е�һ������Ԫ��¼Ϊ1��example: colnum[0]=2 =>colbegin[1]=0+2=2;
	int k = 1; //������
	for (int m = 0; m < M->cols; m++)  //ÿ�з���Ԫ��ʼ��0
	{
		colnum[m] = 0;
	}
	for (int i = 0; i < M->num; i++)   //��¼ÿ�з���Ԫ����
	{
		colnum[M->data[i].col]++;
	}
	for (int j = 0; j < M->cols; j++)  //��¼ÿ����ʼ����Ԫλ
	{
		colbegin[k] = colbegin[k - 1] + colnum[j];
		k++;
	}
	//��ʼת��
	T->cols = M->rows;
	T->rows = M->cols;
	T->num = M->num;
	for (int i = 0; i < M->num; i++)
	{
		int co;
		co = M->data[i].col;   //��i�����ݵ�������co
		int q;
		q = colbegin[co];      //��������Ӧ�����е���ʼλ��
		T->data[q].row = M->data[q].col;
		T->data[q].col = M->data[q].row;
		T->data[q].elem = M->data[q].elem;
		colbegin[co]++;        //���ж�Ӧ����ʼλ��++
	}
}

void TSMatrixShow(TSMatrix *T)
{
	cout << "ת�ú�Ϊ ��" << endl;
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