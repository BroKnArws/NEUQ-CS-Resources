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

bool SearchBTreeNode(BTreeNode *T, int num,BTreeNode *&q,BTreeNode *&cur)      //q:双亲结点
{
	if (T)
	{
		if (T->data == num)
		{
			cur = T;                                                           //cur:该数据结点
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
	if (!cur->lchild)//左子树不在就接右子树
	{
		p->rchild = cur->rchild;
	}
	else if (!cur->rchild)//右子树不在就接左子树
	{
		p->lchild = cur->lchild;
	}
	else if (cur->lchild && cur->rchild)//左右子树都有
	{
		BTreeNode *pre = cur->lchild;   //找cur的中序前驱
		//如果这个前驱的右子树存在
		if (pre->rchild)
		{
			BTreeNode *ppre = pre;
			while (pre->rchild)
			{
				ppre = pre;
				pre = pre->rchild;
			}
			cur->data = pre->data;      //前驱替换该点
			if (pre->lchild)            //如果这个前驱也有前驱
			{
				ppre->rchild = pre->lchild;  //这个点的前驱作为它下面的一系列前驱的前驱的后继，这样就不会丢失这个点下面的所有数据。
			}
			pre = NULL;
		}
		//如果不存在,也就是这个前驱就是该点的左子树根结点
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
	cout << "输入你要插入的数据" << endl;
	cin >> num;
	if (!SearchBTreeNode(ptr, num,q,cur))
	{
		cout << "未能找到该数据，现进行插入操作：" << endl;
		BTreeNodeInsert(q, num);
		cout << "插入完毕" << endl;
	}
	BTreeShow(ptr);
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		q = ptr;  //重置
		cout << "请输入要删除的数据" << endl;
		int delnum;
		cin >> delnum;
		if (!SearchBTreeNode(ptr, delnum, q, cur))
		{
			cout << "该数据不存在，无法删除" << endl;
		}
		else
		{
			cout << "删除结果为" << endl;
			BTreeNodeDelete(q, cur, delnum);
			BTreeShow(ptr);
			cout << endl;
		}
	}
}
//45 12 3 -1 -1 37 24 -1 -1 -1 53 -1 100 61 -1 90 78 -1 -1 -1 -1