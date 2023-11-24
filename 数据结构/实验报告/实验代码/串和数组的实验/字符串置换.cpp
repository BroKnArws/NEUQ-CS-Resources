#include "pch.h"

#include<iostream>
#include<malloc.h>
#include<vector>
#include<string>

using namespace std;


typedef struct Hstring
{
	char *ch;
	int length;
}Hstring;

void StringBuild(Hstring *S)
{
	if (S->ch = (char*)malloc(100 * sizeof(char)))
	{
		S->length = 100;
	}
	else
	{
		return;
	}
}

void Replace(Hstring &S, Hstring T, Hstring V)
{
	cout << "请输入 S" << endl;
	cin >> S.ch;
	cout << "请输入 S 的字串" << endl;
	cin >> T.ch;
	int S_length = strlen(S.ch);
	int T_length = strlen(T.ch);
	int i = 0;
	int t = 0;
	bool sign = 0;
	for (i = 0; i < S_length; i++)
	{
		if (S.ch[i] == T.ch[0])
		{
			for (int a = 0; a < T_length; a++)
			{
				if (S.ch[a + i] != T.ch[a])
				{
					sign = 0;
					break;
				}
				sign = 1;
			}
		}
		if (sign)
		{
			t = i;
			break;
		}
	}
	if (!sign)
	{
		cout << "找不到该子串" << endl;
		return;
	}
	else
	{
		cout << "成功找到该字串，请输入要替换的串：" << endl;
		cin >> V.ch;
		int V_length = strlen(V.ch);
		if (V_length > T_length)
		{
			int more = V_length - T_length;
			for (int k = 0; k < more; k++)
			{
				char *q = &S.ch[S_length-1];
				char *p = &S.ch[t + T_length-1];
				while (q > p)
				{
					*(q + 1) = *q;
					q--;
				}
				S_length++;
			}
		}
		int a = 0;
		for (a = 0; a < V_length; a++)
		{
				S.ch[t + a] = V.ch[a];
		}
		if (V_length < T_length)
		{
			S.ch[t + a] = '\0';
		}
		else
		{
			S.ch[S_length] = '\0';
		}
	}
}

void HstringShow(Hstring &S)
{
	int S_length = strlen(S.ch);
	for (int i = 0; i < S_length; i++)
	{
		cout << S.ch[i];
	}
	cout << endl;
}

int main()
{
	Hstring S, T, V;
	StringBuild(&S); StringBuild(&T); StringBuild(&V);
	Replace(S, T, V);
	HstringShow(S);
}