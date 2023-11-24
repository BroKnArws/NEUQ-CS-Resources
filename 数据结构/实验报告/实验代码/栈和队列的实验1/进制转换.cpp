#include <iostream>
#include <string>

using namespace std;

typedef struct Stack
{
	int*base;
	int*top;
	int stacksize;
}Stack;

void InitStack(Stack *S)  //��ʼ��
{
	S->base = S->top = new int[100];
	S->stacksize = 100;
}

void StackPush(Stack &S, int c) //ѹջ
{
	*S.top = c;
	S.top++;
}
void StackPop(Stack *S)  //ɾ��
{
	if (S->top == S->base)
	{
		cout << "��ջ." << endl;
		return;
	}
	S->top--;
}

void StackShow(Stack S)
{
	int *p = S.top-1;
	while (p >S.base)
	{
		cout << *p;
		p--;
	}
	cout << *p;
}

void BinaryConversion(int num)
{
	cout << "��Ҫת��Ϊ������ ��" << endl;
	int n;
	cin >> n;
	Stack S;
	InitStack(&S);
	while (num)
	{
		StackPush(S, num % n);
		num = num / n;
	}
	StackShow(S);

}

int main()
{
	Stack S;
	int num;
	cout << "������Ҫ��ת��������" << endl;
	cin >> num;
	BinaryConversion(num);
}