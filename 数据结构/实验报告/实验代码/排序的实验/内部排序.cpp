#include <iostream>

using namespace std;

typedef struct
{
	int key;
}RedType;

typedef struct
{
	RedType r[1000];
	int length;
}SqList;

void SqListInit(SqList &L)
{
	cout << "输入多少数字？" << endl;
	int m;
	cin >> m;
	//8
	cout << "输入各项数字" << endl;
	//49 38 65 97 76 13 27 49
	for (int i = 1; i <= m; i++)   // 0处不放数字
	{
		int n;
		cin >> n;
		L.r[i].key = n;
	}
	L.length = m;
}

void InsertSort(SqList &L)    					//插入排序 
{
	int j,k;
	for(int i=2;i<=L.length;i++)
	{
		if(L.r[i].key<L.r[i-1].key)
		{
			L.r[0]=L.r[i];
			for(j=i-1;j>0;j--)
			{
				if(L.r[0].key<L.r[j].key)
				{
					k=j;
					L.r[j+1]=L.r[j];
				}
			}
			L.r[k]=L.r[0];
		}
	}
}

void BInsertSort(SqList &L) 				 //折半插入
{
	for(int i=2;i<=L.length;i++)
	{
		L.r[0]=L.r[i];
		int low=1;int high=i-1;
		while(low<=high)
		{
			int m=(low+high)/2;
			if(L.r[0].key<L.r[m].key)
			{
				high=m-1;
			}
			else
			{
				low=m+1;
			}
		}
		for(int j=i-1;j>=high+1;j--)
		{
			L.r[j+1]=L.r[j];
		}
		L.r[high+1]=L.r[0];
	}
 } 
void QuickSort(SqList &L,int low,int high)  	//快排 
{
	if(low<high)
	{
		int m;
		L.r[0].key=L.r[low].key;
		m=L.r[0].key;
		int i=low;
		int j=high;
		while(i<j)
		{
			while(i<j&&L.r[j].key>=m)
			{
				j--;
			}
			while(i<j&&L.r[i].key<=m)
			{
				i++;
			}
			if(i<j)
			{
				int temp;
				temp=L.r[i].key;
				L.r[i].key=L.r[j].key;
				L.r[j].key=temp;
			}
		}
		//调换中枢和第一个 
		L.r[low].key=L.r[i].key;
		L.r[i].key=L.r[0].key;
		
		QuickSort(L,i+1,high);
		QuickSort(L,low,i-1);
	}
}

int FindMin(SqList &L,int begin)
{
	int min=10000;
	int j;
	for(int i=begin;i<=L.length;i++)
	{
		
		if(L.r[i].key<min)
		{
			j=i;
			min=L.r[i].key;
			
		}
	}
	return j;
}

void ChooseSort(SqList &L) 						//选择排序 
{
	for(int i=1;i<=L.length;i++) 
	{
		int j=FindMin(L,i);
		int temp;
		temp = L.r[i].key;
		L.r[i].key=L.r[j].key;
		L.r[j].key=temp;
	}
}
void SqListShow(SqList L)
{
	for(int i=1;i<=L.length;i++)
	{
		cout<<L.r[i].key<<" ";
	}
}

int main()
{
	SqList L;
	SqListInit(L);
	//InsertSort(L);
	//QuickSort(L,1,L.length);
	//BInsertSort(L);
	ChooseSort(L);
	SqListShow(L);
}