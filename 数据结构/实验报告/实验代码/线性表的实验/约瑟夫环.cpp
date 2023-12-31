#include "pch.h"
#include <iostream>
#include <malloc.h>

using namespace std;

typedef struct LNode
{
	int num;
	int data;
	struct LNode *next;
}LNode,*LinkList;

LinkList ListBuild()
{
	LinkList head = (LinkList)malloc(sizeof(LNode));
	LinkList p = head;
	cout << "有多少人(n值) ?" << endl;
	int n;
	cin >> n;
	cout << "输入每个人的密码：" << endl;
	for (int i = 1; i <= n; i++)
	{
		p->next = (LinkList)malloc(sizeof(LNode));
		p = p->next;
		cin >> p->data;
		p->num = i;
	}
	p->next = head->next;
	p = p->next;
	free(head);
	return p;
}

void Joseph(LinkList p)
{
	cout << "开始值(m值) ?" << endl;
	int num;
	cin >> num;
	LinkList q = p;
	while (p)
	{
		for (int i = 1; i < num; i++)
		{
			q = p;
			p = p->next;
		}
		cout << p->num << " ";
		if (p->next == p)
		{
			free(p);
			break;
		}
		q->next = p->next;
		num = p->data;
		free(p);
		p = q->next;
	}
}
int main()
	
{
	LinkList p = ListBuild();
	Joseph(p);
}
