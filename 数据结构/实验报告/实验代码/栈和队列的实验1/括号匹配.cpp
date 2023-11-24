#include<iostream>
#include<malloc.h>

using namespace std;

typedef struct Stack{
	char *base;
	char *top;
	int size;
}Stack;

void StackBuild(Stack *S)
{
	S->base = S->top = (char*)malloc(100 * sizeof(char));
	S->size = 100;

}

void StackConnection(Stack *S)
{
	if (S->top - S->base >= S->size)
	{
		S->base = (char*)realloc(S->base, (S->size + 100) * sizeof(char));
		S->top = S->base + S->size;
		S->size += 100;
	}
	cout << "What character ?" << endl;
	char InsertChar;
	cin >> InsertChar;
	if (!(S->top == S->base))
	{
		char *p = S->top - 1;
		if ((*p == '{'&&InsertChar == '}') || (*p == '('&&InsertChar == ')') || (*p == '['&&InsertChar == ']'))
		{
			S->top--;
			return;
		}
	}
	*(S->top)++ = InsertChar;

}

void StackShow(Stack *S)
{
	if (S->top == S->base)
	{
		cout << "Empty Stack." << endl;
		return;
	}
	char *p = S->base;
	while (p!=S->top)
	{
		cout << *p << " ";
		p++;
	}
	cout << endl;
}


int main()
{
	Stack S;
	//test.
	StackBuild(&S);
	//ÊäÈë¡°[([][])]¡°¼ìÑé¡£
	StackConnection(&S);
	StackConnection(&S);
	StackConnection(&S);
	StackConnection(&S);
	StackConnection(&S);
	StackConnection(&S);
	StackConnection(&S);
	StackConnection(&S);
	StackShow(&S);

}