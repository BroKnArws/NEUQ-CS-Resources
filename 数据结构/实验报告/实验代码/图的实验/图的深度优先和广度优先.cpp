#include<iostream>

using namespace std;

typedef struct ArcNode {
	int adj;
	ArcNode *next;
}ArcNode;

typedef struct VNode
{
	int data;
	ArcNode *firstout;
}VNodeList[100];

typedef struct Graph {
	VNodeList vertices;
	int vexnum, arcnum;
};

void GraphInit(Graph &G)
{
	cout << "���뻡������" << endl;
	int arcnum;
	cin >> arcnum;
	cout << "���붥�������" << endl;
	int vexnum;
	cin >> vexnum;
	G.arcnum = arcnum;
	G.vexnum = vexnum;
	for (int i = 0; i < vexnum; i++)
	{
		G.vertices[i].data = i + 1;
		G.vertices[i].firstout = NULL;
	}
	cout << "�������뻡����� �� �����յ�" << endl;
	for (int i = 0; i < arcnum; i++)
	{
		int arcbegin, arcend;
		cin >> arcbegin;
		cin >> arcend;
		ArcNode *p = new ArcNode;
		p->adj = arcend - 1;
		if (G.vertices[arcbegin - 1].firstout == NULL)   //һ����������������洢��ʽ��������ò��м�ķ�ʽ������Ⱥ͹�ȱ������ҿ�ʼ
		{
			p->next = G.vertices[arcbegin - 1].firstout;
			G.vertices[arcbegin - 1].firstout = p;
		}
		else
		{
			ArcNode *q = G.vertices[arcbegin - 1].firstout;
			while (q->next != NULL)
			{
				q = q->next;
			}
			p->next = NULL;
			q->next = p;
		}
	}
	cout << "Init Success" << endl;
}

void DFS(Graph &G, int visited[100], int i)
{
	if (!visited[i])
	{
		visited[i] = 1;
		cout << G.vertices[i].data << " ";
		ArcNode *p = G.vertices[i].firstout;
		while (p)  
	    {  
           if (!visited[p->adj])  
          {  
               DFS(G, visited, p->adj);   
           }  
          p = p->next;  
       }  

	}
}

void showDFS(Graph &G)
{
	int visited[100];
	for (int i = G.vexnum - 1; i >= 0; i--)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		if (!visited[i])
		{
			DFS(G, visited, i);
		}
	}
}

void BrandFirst(Graph &G)
{
	int visited[100];
	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = 0;
	}
	int Quene[100];
	int front, rear;
	front = rear = 0;
	Quene[rear++] = 0;
	visited[0] = 1;
	while (front < rear)
	{
		ArcNode *p = G.vertices[Quene[front]].firstout;
		cout << G.vertices[Quene[front]].data << " ";
		while (p)
		{
			if (!visited[p->adj])
			{
				visited[p->adj] = 1;
				Quene[rear++] = p->adj;
			}
			p = p->next;
		}
		front++;
	}
}
int main()
{
	Graph* G = new Graph;
	GraphInit(*G);
	cout << "�����������Ϊ" << endl;
	showDFS(*G);
	cout << endl;
	cout << "�����������Ϊ" << endl;
	BrandFirst(*G);
}
//1 2 2 4 4 8 2 5 5 8 1 3 3 6 6 7 3 7(����ͼ)
//1 2 2 1 2 4 4 2 4 8 8 4 2 5 5 2 5 8 8 5 1 3 3 1 3 6 6 3 6 7 7 6 3 7 7 3(����ͼ)