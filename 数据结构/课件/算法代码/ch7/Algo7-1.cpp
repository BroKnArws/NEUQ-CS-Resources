 // algo7-1.cpp �����㷨7.7��7.8
 #include"c1.h"
 #define MAX_NAME 2 // �����ַ�������󳤶�+1
 typedef char ElemType[MAX_NAME];
 typedef ElemType TElemType;
 #include"c6-5.h"
 typedef int InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-2.h"
 #include"bo7-2.cpp"

 void DFSTree(ALGraph G,int v,CSTree &T)
 { // �ӵ�v���������������ȱ���ͼG,������TΪ�������������㷨7.8
   Boolean first=TRUE;
   int w;
   CSTree p,q;
   VertexType v1,w1;
   visited[v]=TRUE;
   strcpy(v1,GetVex(G,v));
   for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,GetVex(G,w)))) // w����Ϊv���ڽӶ���
     if(!visited[w]) // w���㲻��������
     {
       p=(CSTree)malloc(sizeof(CSNode)); // ���亢�ӽ��
       strcpy(p->data,GetVex(G,w));
       p->firstchild=NULL;
       p->nextsibling=NULL;
       if(first)
       { // w��v�ĵ�һ��δ�����ʵ��ڽӶ���
         T->firstchild=p;
         first=FALSE; // �Ǹ��ĵ�һ�����ӽ��
       }
       else // w��v������δ�����ʵ��ڽӶ���
	 q->nextsibling=p; // ����һ�ڽӶ�����ֵܽ��ý��
       q=p;
       DFSTree(G,w,q); // �ӵ�w���������������ȱ���ͼG,������������q
     }
 }

 void DFSForest(ALGraph G,CSTree &T)
 { // ��������ͼG�������������ɭ�ֵ�(����)����(��)�ֵ�����T���㷨7.7
   CSTree p,q;
   int v;
   T=NULL;
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; // ����ֵ
   for(v=0;v<G.vexnum;++v) // �ӵ�0����������
     if(!visited[v]) // ��v�����㲻��������
     { // ��v����Ϊ�µ��������ĸ����
       p=(CSTree)malloc(sizeof(CSNode)); // ��������
       strcpy(p->data,GetVex(G,v));
       p->firstchild=NULL;
       p->nextsibling=NULL;
       if(!T) // �ǵ�һ���������ĸ�(T�ĸ�)
         T=p;
       else // �������������ĸ�(ǰһ�õĸ��ģ��ֵܣ�)
         q->nextsibling=p;
       q=p; // qָʾ��ǰ�������ĸ�
       DFSTree(G,v,p); // ������pΪ����������
     }
 }

 void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { // �ȸ��������ӣ��ֵܶ�������ṹ����T(bo6-5.cpp��)
   if(T)
   {
     Visit(T->data); // �ȷ��ʸ����
     PreOrderTraverse(T->firstchild,Visit); // ���ȸ�������������
     PreOrderTraverse(T->nextsibling,Visit); // ����ȸ�������һ���ֵ�����
   }
 }

 void print(char *i)
 {
   printf("%s ",i);
 }

 void main()
 {
   ALGraph g;
   CSTree t;
   printf("��ѡ������ͼ\n");
   CreateGraph(g);
   Display(g);
   DFSForest(g,t);
   printf("�����������ɭ�֣�\n");
   PreOrderTraverse(t,print);
   printf("\n");
 }
