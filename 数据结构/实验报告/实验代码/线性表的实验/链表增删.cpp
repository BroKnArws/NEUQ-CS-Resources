#include <iostream>

using namespace std;

typedef struct List{
	char data;
	struct List *next;
}LNode, *LinkList;

void BuildList(LinkList head)
{
		LinkList p = head;
		for (int i = 0; i < 26; i++)
		{
			LinkList s = (LinkList)malloc(sizeof(LNode));
			s->data = 'a' + i;
			s->next = p->next;
			p->next = s;
			p = p->next;
		}
		cout << "Successfully Build !" << endl;
}

void ListDelete(LinkList head)
{
	if (head->next)
	{
		cout << "Please input the character you want to DELETE:" << endl;
		char DelChar;
		cin >> DelChar;
		if (DelChar<'A' || (DelChar > 'Z'&&DelChar < 'a') || DelChar>'z')
		{
			cout << "ERROR:NOT CHARACTER." << endl;
			return;
		}
		LinkList p = head;
		while (p)
		{
			if (p->next == NULL)
			{
				break;
			}
			if (p->next->data == DelChar)
			{
				LinkList q = p->next;
				p->next = p->next->next;
				free(q);
				cout << "Successfully Delete !" << endl;
				return;
			}
			else
			{
				p = p->next;
			}
		}
		cout << "ERROR: Can't find the character." << endl;
	}
	else
	{
		cout << "ERROR: Empty List." << endl;
	}
}

void ListInsert(LinkList head)
{
	if (head->next)
	{
		bool flag = 0;
		cout << "Please input the character you want to INSERT :" << endl;
		char InsertChar;
		cin >> InsertChar;
		if (InsertChar<'A' || (InsertChar > 'Z'&&InsertChar < 'a') || InsertChar>'z')
		{
			cout << "ERROR:NOT CHARACTER." << endl;
			return;
		}
		if (InsertChar >= 'A'&&InsertChar <= 'Z')
		{
			flag = 1;
			InsertChar += 32;
		}
		LinkList p = head->next;
		LinkList s = head;
		int num = 1;
		while (p)
		{
			if (p->data >= InsertChar)
			{
				LinkList q = (LinkList)malloc(sizeof(LNode));
				q->next = s->next;
				s->next = q;
				if (flag)
				{
					InsertChar -= 32;
				}
				q->data = InsertChar;
				cout << "Successfully Insert !" << endl;
				return;
			}
			if (p->next == NULL)
			{
				LinkList q = (LinkList)malloc(sizeof(LNode));
				q->next = p->next;
				if (flag)
				{
					InsertChar -= 32;
				}
				q->data = InsertChar;
				p->next = q;
				cout << "Successfully Insert !" << endl;
				return;
			}
			else
			{
				s = p;
				p = p->next;
			}
		}
	}
	else
	{
		cout << "ERROR :Empty List." << endl;
	}
}
void ListShow(LinkList head)
{
	if (head->next)
	{
		LinkList p = head->next;
		while (p)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
	else
	{
		cout << "ERROR :Empty List." << endl;
		return;
	}
}
void ListFind(LinkList head)
{
	if (head->next)
	{
		cout << "Please input the character you want to find:" << endl;
		char FindChar;
		cin >> FindChar;
		LinkList p = head->next;
		int num = 1;
		while (p)
		{
			if (p->data == FindChar)
			{
				cout << "Successfully Find It ! And It's Location Is " << num;
				return;
			}
			else
			{
				num++;
				p = p->next;

			}
		}
		cout << "ERROR :Can't Find The Character." << endl;
	}
	else
	{
		cout << "ERROR :Empty List." << endl;
	}
}
int main()
{
	LinkList head = (LinkList)malloc(sizeof(LNode));
	head->next = NULL;
	while (1)
	{
		cout << "Please input the number: " << endl;
		int num;
		cin >> num;
		switch (num)
		{
		case 1:BuildList(head); break;
		case 2:ListDelete(head); break;
		case 3:ListInsert(head); break;
		case 4:ListFind(head); break;
		case 5:ListShow(head); break;
		}
	}
}
