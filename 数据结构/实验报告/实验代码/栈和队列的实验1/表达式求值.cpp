#include <iostream>
#include <string>

using namespace std;

typedef struct Stack
{
	char*base;
	char*top;
	int stacksize;
}Stack;

void InitStack(Stack *S)  //��ʼ��
{
	S->base = S->top = (char*)malloc(100 * sizeof(char));
	S->stacksize = 100;
}

void StackPush(Stack *S, char c,int flag) //ѹջ
{
	if (!flag)
	{
		*(S->top)++ = c;
	}
	else
	{
		S->top = S->top - 2;
		*(S->top)++ = c;
	}
}
void StackPop(Stack *S)  //ɾ
{
	if (S->top == S->base)
	{
		cout << "��ջ." << endl;
		return;
	}
	S->top--;
}

int char_to_int(char s)   //תint
{
	return int(s) - 48;
}

char PriorityComparison(Stack *S, char c)  //��������ȼ��Ƚ�
{
	char *p = S->top - 1;
	char prior[7][7] =
	{ {'>','>','<','<','<','>','>'},
	{'>','>','<','<','<','>','>'},
	 {'>','>','>','>','<','>','>'},
	 {'>','>','>','>','<','>','>'},
	 {'<','<','<','<','<','=',' '},
	 {'>','>','>','>',' ','>','>'},
	 {'<','<','<','<','<',' ','='} };

	char Operator[7] = { '+','-','*','/','(',')','#' };
	int m = 0; int n = 0;
	while (Operator[n] != c) { n++; }
	while (Operator[m] != *p) { m++; };
	return prior[m][n];
}

void StackDestory(Stack *OPND, Stack *OPTR)  //��ջ
{
	free(OPND->base);
	free(OPTR->base);
	OPND->base = OPND->base = NULL;
	OPND->stacksize = OPTR->stacksize = 0;
}

int Operate(int num1,char s,int num2)  //����
{
	switch (s)
	{
	case '+':return num1 + num2; break;
	case'-':return num1 - num2; break;
	case'*':return num1 * num2; break;
	case'/':return num1 / num2; break;
	}
}


int main()
{
	Stack OPND, OPTR;
	string s;
	while (1)
	{
		cout << "������ʽ��" << endl;
		cin >> s;
		InitStack(&OPND); InitStack(&OPTR);
		StackPush(&OPTR, '#', 0);
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				StackPush(&OPND, s[i], 0);
			}
			else if (PriorityComparison(&OPTR, s[i]) == '<')  //���ȶȵ͵Ĵ���
			{
				StackPush(&OPTR, s[i], 0);
			}
			else if (PriorityComparison(&OPTR, s[i]) == '=')
			{
				StackPop(&OPTR);
			}
			else if (PriorityComparison(&OPTR, s[i]) == '>') //���ȶȸߵ��������㣨����ָȥ���ŵ����㣩
			{
				if (OPND.top - 2)
				{
					char num1 = *(OPND.top - 2);
					char num2 = *(OPND.top - 1);
					StackPush(&OPND, '0' + char(Operate(char_to_int(num1), *(OPTR.top - 1), char_to_int(num2))), 1);
					StackPop(&OPTR);
					if (s[i] == ')')  //���Ŷ�ɾһ�Σ���Ϊ���˸����š�(+)
					{
						StackPop(&OPTR);
					}
					else
					{
						StackPush(&OPTR, s[i], 0);
					}
				}

			}
		}
		//��Ϻ����ʣ�µ�ֵ
		while (*(OPTR.top) != '#' &&*(OPTR.top - 1) != '#')
		{
			if (OPND.top - 2)
			{
				char num1 = *(OPND.top - 2);
				char num2 = *(OPND.top - 1);
				StackPush(&OPND, '0' + (Operate(char_to_int(num1), *(OPTR.top - 1), char_to_int(num2))), 1);
				// int to char
				StackPop(&OPTR);
			}
		}
		//char to int
		cout << int(*(OPND.top - 1)) - 48 << endl;
		StackDestory(&OPND,&OPTR);

	}

}