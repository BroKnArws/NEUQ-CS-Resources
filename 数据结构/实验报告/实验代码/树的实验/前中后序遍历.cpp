#include <iostream>

using namespace std;

typedef struct BTreeNode
{
	BTreeNode *lchild;
	BTreeNode *rchild;
	char data;
};
void BTreeBuild(BTreeNode *&T)
{
	char s;
	cin>>s;
	if(s!='#')
	{
		T=new BTreeNode;
		T->data=s;
		BTreeBuild(T->lchild);
		BTreeBuild(T->rchild);
	}
	else
	{
		T=NULL;
	}
}

void PreOrderTraverse(BTreeNode *&T)
{
	if(T)
	{
		cout<<T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BTreeNode *&T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		cout<<T->data;
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BTreeNode *&T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout<<T->data;
	}
}
int main()
{
	BTreeNode T;
	BTreeNode *ptr=&T;
	cout<<"��������ڵ��ֵ"<<endl; 
	BTreeBuild(ptr);
	cout<<"ǰ�����Ϊ"<<endl;
	PreOrderTraverse(ptr);
	cout<<endl;
	cout<<"�������Ϊ"<<endl;
	InOrderTraverse(ptr);
	cout<<endl;
	cout<<"�������Ϊ"<<endl;
	PostOrderTraverse(ptr);
	cout<<endl;
}
