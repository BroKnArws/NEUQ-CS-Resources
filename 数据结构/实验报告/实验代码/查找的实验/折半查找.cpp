#include"pch.h"
#include<iostream>
#include<string>

using namespace std;

void HalfFold(int num[1000], int point, int size)
{
	int mid, max, min;
	max = size - 1;
	min = 0;
	while (min <= max)
	{
		mid = (min + max) / 2;
		if (num[mid] == point)
		{
			cout << mid + 1;
			return;
		}
		if (num[mid] > point)
		{
			max = mid - 1;
		}
		if (num[mid] < point)
		{
			min = mid + 1;
		}
	}
	cout << "Not Found" << endl;
}

int HalfFold_recursive(int num[1000],int point, int min, int max)
{
	if (min > max)
	{
		return -1;
	}
	int mid = (min + max) / 2;
	if (num[mid] == point)
	{
		return mid + 1;
	}
	if (num[mid] > point)
	{
		max = mid - 1;
	}
	if (num[mid] < point)
	{
		min = mid + 1;
	}
	return HalfFold_recursive(num, point, min, max);
}

int main()
{
	cout << "输入一串数字，进行折半查找" << endl;
	int num[1000];
	cout << "输入数字的个数：" << endl;
	int sc;
	cin >> sc;
	cout << "依次输入每个数字：" << endl;
	for (int i = 0; i < sc; i++)
	{
		cin >> num[i];
	}
	cout << "输入你要查找的数字" << endl;
	int point;
	cin >> point;
	int result = HalfFold_recursive(num, point, 0, sc - 1);
	if (result!=-1)
	{
		cout << result << endl;
	}
	else
	{
		cout << "Not Found";
	}
}