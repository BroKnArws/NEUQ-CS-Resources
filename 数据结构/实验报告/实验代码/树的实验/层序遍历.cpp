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
void LevelOrderTraverse(BTreeNode *&T)
{
	BTreeNode* s[100];
	int p=1;
	int q=2; 
	s[1]=T;
	while(p<q)
{
	if(s[p]->lchild)
	{
		s[q]=s[p]->lchild;
		q++;
	}
	if(s[p]->rchild)
	{
		s[q]=s[p]->rchild;
		q++;
	}
	p++;
}
cout<<"²ãÐò±éÀúÎª"<<endl;
for(int i=1;i<=q-1;i++)
{
	cout<<s[i]->data;
}	
}


/*typedef struct Quene{
	BTreeNode** front;
	BTreeNode** rear;
	int size;
}Quene£» */

/*void QueneInit(Quene &Q)
{
	Q.front=Q.rear=new Quene[100];
}
void levels2(BTreeNode *T,Quene &Q)
{
	BTreeNode **s=&Q.rear;
	(*Q.rear)++=T;
	while(s<q)
	{
	if(*s->lchild)
	{
	(*Q.rear)++=*s->lchild;
	}
	if(*s->rchild)
	{
	(*Q.rear)++=*s->rchild;
    }
    s++;
}
    while(Q.front<Q.rear)
    {
    cout<<Q.rear->data;
}
	
}
}*/

int main()
{
	BTreeNode T;
	BTreeNode *ptr=&T;
	BTreeBuild(ptr);
	LevelOrderTraverse(ptr);
}
