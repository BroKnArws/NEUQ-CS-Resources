#include <iostream>
#include <string>

using namespace std;

typedef struct Stack
{
	int*base;
	int*top;
	int stacksize;
}Stack;

void InitStack(Stack *S)  //初始化
{
	S->base = S->top = new int[100];
	S->stacksize = 100;
}

void StackPush(Stack &S, int c) //压栈
{
	*S.top = c;
	S.top++;
}
void StackPop(Stack *S)  //删除
{
	if (S->top == S->base)
	{
		cout << "空栈." << endl;
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
	cout << "需要转换为几进制 ？" << endl;
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
	cout << "输入需要被转换的数字" << endl;
	cin >> num;
	BinaryConversion(num);
}