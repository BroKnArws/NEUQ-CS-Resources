 // algo7-4.cpp �������ͼ��һ���������С�ʵ���㷨7.12�ĳ���
 #include"c1.h"
 #define MAX_NAME 5 // �����ַ�������󳤶�
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; // �ַ�������
 #include"c7-2.h"
 #include"bo7-2.cpp"

 void FindInDegree(ALGraph G,int indegree[])
 { // �󶥵����ȣ��㷨7.12��7.13����
   int i;
   ArcNode *p;
   for(i=0;i<G.vexnum;i++)
     indegree[i]=0; // ����ֵ
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       indegree[p->adjvex]++;
       p=p->nextarc;
     }
   }
 }

 typedef int SElemType; // ջ����
 #include"c3-1.h"
 #include"bo3-1.cpp"
 Status TopologicalSort(ALGraph G)
 { // ����ͼG�����ڽӱ�洢�ṹ����G�޻�·,�����G�Ķ����һ���������в�����OK,
   // ���򷵻�ERROR���㷨7.12
   int i,k,count,indegree[MAX_VERTEX_NUM];
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree); // �Ը����������indegree[0..vernum-1]
   InitStack(S); // ��ʼ��ջ
   for(i=0;i<G.vexnum;++i) // ������ȶ���ջS
     if(!indegree[i])
       Push(S,i); // ���Ϊ0�߽�ջ
   count=0; // ������������
   while(!StackEmpty(S))
   { // ջ����
     Pop(S,i);
     printf("%s ",G.vertices[i].data); // ���i�Ŷ��㲢����
     ++count;
     for(p=G.vertices[i].firstarc;p;p=p->nextarc)
     { // ��i�Ŷ����ÿ���ڽӵ����ȼ�1
       k=p->adjvex;
       if(!(--indegree[k])) // ����ȼ�Ϊ0,����ջ
         Push(S,k);
     }
   }
   if(count<G.vexnum)
   {
     printf("������ͼ�л�·\n");
     return ERROR;
   }
   else
   {
     printf("Ϊһ���������С�\n");
     return OK;
   }
 }

 void main()
 {
   ALGraph f;
   printf("��ѡ������ͼ\n");
   CreateGraph(f);
   Display(f);
   TopologicalSort(f);
 }
