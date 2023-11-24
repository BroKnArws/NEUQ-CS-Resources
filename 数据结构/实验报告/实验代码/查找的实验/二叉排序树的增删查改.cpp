#include "pch.h"
#include <iostream>

using namespace std;

typedef struct BTreeNode
{
	int data;
	BTreeNode *lchild;
	BTreeNode *rchild;
}BTreeNode,*BTN;

void BTreeBuild(BTreeNode* &T)
{
	int data;
	cin >> data;
	if (data != -1)
	{
		T = new BTreeNode;
		T->data = data;
		BTreeBuild(T->lchild);
		BTreeBuild(T->rchild);
	}
	else
	{
		T = NULL;
	}
}

void BTreeShow(BTreeNode* T)
{
	if (T)
	{
		BTreeShow(T->lchild);
		cout << T->data << " ";
		BTreeShow(T->rchild);
	}
}

bool SearchBTreeNode(BTreeNode *T, int num,BTreeNode *&q,BTreeNode *&cur)      //q:˫�׽��
{
	if (T)
	{
		if (T->data == num)
		{
			cur = T;                                                           //cur:�����ݽ��
			return true;
		}
		if (T->data > num)
		{
			q = T;
			return SearchBTreeNode(T->lchild, num, q,cur);
		}
		else
		{
			q = T;
			return SearchBTreeNode(T->rchild, num, q,cur);
		}
	}
	else
	{
		return false;
	}
}

void BTreeNodeInsert(BTreeNode *&q,int num)
{
	if (q->data > num)
	{
		q->lchild = new BTreeNode;
		q->lchild->data = num;
		q->lchild->lchild = q->lchild->rchild = NULL;
	}
	else
	{
		q->rchild = new BTreeNode;
		q->rchild->data = num;
		q->rchild->lchild = q->rchild->rchild = NULL;
	}
}

void BTreeNodeDelete(BTreeNode *&p,BTreeNode *&cur, int num)
{
	if (!cur->lchild)//���������ھͽ�������
	{
		p->rchild = cur->rchild;
	}
	else if (!cur->rchild)//���������ھͽ�������
	{
		p->lchild = cur->lchild;
	}
	else if (cur->lchild && cur->rchild)//������������
	{
		BTreeNode *pre = cur->lchild;   //��cur������ǰ��
		//������ǰ��������������
		if (pre->rchild)
		{
			BTreeNode *ppre = pre;
			while (pre->rchild)
			{
				ppre = pre;
				pre = pre->rchild;
			}
			cur->data = pre->data;      //ǰ���滻�õ�
			if (pre->lchild)            //������ǰ��Ҳ��ǰ��
			{
				ppre->rchild = pre->lchild;  //������ǰ����Ϊ�������һϵ��ǰ����ǰ���ĺ�̣������Ͳ��ᶪʧ�����������������ݡ�
			}
			pre = NULL;
		}
		//���������,Ҳ�������ǰ�����Ǹõ�������������
		else
		{
			p->lchild = pre->lchild;
			free(pre);
		}
	}

}
int main()
{
	BTreeNode *T;
	T = new BTreeNode;
	BTN ptr = T;
	BTN q = T;
	BTN cur = NULL;
	BTreeBuild(ptr);
	BTreeShow(ptr);
	int num;
	cout << "������Ҫ���������" << endl;
	cin >> num;
	if (!SearchBTreeNode(ptr, num,q,cur))
	{
		cout << "δ���ҵ������ݣ��ֽ��в��������" << endl;
		BTreeNodeInsert(q, num);
		cout << "�������" << endl;
	}
	BTreeShow(ptr);
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		q = ptr;  //����
		cout << "������Ҫɾ��������" << endl;
		int delnum;
		cin >> delnum;
		if (!SearchBTreeNode(ptr, delnum, q, cur))
		{
			cout << "�����ݲ����ڣ��޷�ɾ��" << endl;
		}
		else
		{
			cout << "ɾ�����Ϊ" << endl;
			BTreeNodeDelete(q, cur, delnum);
			BTreeShow(ptr);
			cout << endl;
		}
	}
}
//45 12 3 -1 -1 37 24 -1 -1 -1 53 -1 100 61 -1 90 78 -1 -1 -1 -1