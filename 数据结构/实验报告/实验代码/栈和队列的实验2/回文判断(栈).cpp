#include "pch.h"
#include <iostream>
#include<malloc.h>
#include<string>

using namespace std;

typedef struct Quene
{
	char *front;
	char *rear;
	int length;
}Quene;

typedef struct Stack {
	char *base;
	char *top;
	int length;
}Stack;

void QSBuild(Quene *Q, Stack *S)
{
	Q->front = Q->rear = (char*)malloc(100 * sizeof(char));
	S->base = S->top = (char*)malloc(100 * sizeof(char));
}

void QInit(Quene *Q)
{
	string s;
	cin >> s;
	for (int i = 0; i < s.length(); i++)
	{
		*(Q->rear) = s[i];
		Q->rear++;
	}
}

void Judge(Quene *Q, Stack *S)
{
	while (Q->front < Q->rear)
	{
		*(S->top) = *(Q->front);
		char *q = Q->rear - 1;
		if (*q == *(S->top))
		{
			S->top++;
			Q->front++;
			Q->rear--;
		}
		else
		{
			cout << "False" << endl;
			return;
		}
	}
	cout << "True" << endl;
	return;
}
int main()
{
	Quene Q;
	Stack S;
	QSBuild(&Q, &S);
	cout << "Please Input the Characters:" << endl;
	QInit(&Q);
	Judge(&Q, &S);

}