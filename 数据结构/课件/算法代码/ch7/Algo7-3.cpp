 // algo7-3.cpp ʵ���㷨7.10��7.11�ĳ���
 #include"c1.h"
 #define MAX_NAME 2 // �����ַ�������󳤶�+1
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; // �ַ�������
 #include"c7-2.h"
 #include"bo7-2.cpp"

 int count; // ȫ����count�Է��ʼ���
 int low[MAX_VERTEX_NUM];

 void DFSArticul(ALGraph G,int v0)
 { // �ӵ�v0���������������ȱ���ͼG�����Ҳ�����ؽڵ㡣�㷨7.11
   int min,w;
   ArcNode *p;
   visited[v0]=min=++count; // v0�ǵ�count�����ʵĶ���
   for(p=G.vertices[v0].firstarc;p;p=p->nextarc) // ��v0��ÿ���ڽӶ�����
   {
     w=p->adjvex; // wΪv0���ڽӶ���
     if(visited[w]==0) // wδ�����ʣ���v0�ĺ���
     {
       DFSArticul(G,w); // ����ǰ���low[w]
       if(low[w]<min)
         min=low[w];
       if(low[w]>=visited[v0])
         printf("%d %s\n",v0,G.vertices[v0].data); // �ؽڵ�
     }
     else if(visited[w]<min)
       min=visited[w]; // w�ѷ��ʣ�w��v0���������ϵ�����
   }
   low[v0]=min;
 }

 void FindArticul(ALGraph G)
 { // ��ͨͼG���ڽӱ����洢�ṹ�����Ҳ����G��ȫ���ؽڵ㡣�㷨7.10
   // ȫ����count�Է��ʼ�����
   int i,v;
   ArcNode *p;
   count=1;
   low[0]=visited[0]=1; // �趨�ڽӱ���0�Ŷ���Ϊ�������ĸ�
   for(i=1;i<G.vexnum;++i)
     visited[i]=0; // ���ඥ����δ����
   p=G.vertices[0].firstarc;
   v=p->adjvex;
   DFSArticul(G,v); // �ӵ�v�������������Ȳ��ҹؽڵ�
   if(count<G.vexnum) // �������ĸ���������������
   {
     printf("%d %s\n",0,G.vertices[0].data); // ���ǹؽڵ㣬���
     while(p->nextarc)
     {
       p=p->nextarc;
       v=p->adjvex;
       if(visited[v]==0)
         DFSArticul(G,v);
     }
   }
 }

 void main()
 {
   int i;
   ALGraph g;
   printf("��ѡ������ͼ\n");
   CreateGraph(g);
   printf("����ؽڵ㣺\n");
   FindArticul(g);
   printf(" i G.vertices[i].data visited[i] low[i]\n");
   for(i=0;i<g.vexnum;++i)
     printf("%2d %9s %14d %8d\n",i,g.vertices[i].data,visited[i],low[i]);
 }
