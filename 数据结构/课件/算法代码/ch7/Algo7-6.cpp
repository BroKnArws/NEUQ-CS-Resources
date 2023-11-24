 // algo7-6.cpp ʵ���㷨7.15�ĳ��򡣵Ͻ�˹�����㷨��ʵ��
 #include"c1.h"
 #define MAX_NAME 5 // �����ַ�������󳤶�+1
 #define MAX_INFO 20 // �����Ϣ�ַ�������󳤶�+1
 typedef int VRType;
 typedef char InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h"
 typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 typedef int ShortPathTable[MAX_VERTEX_NUM];
 #include"bo7-1.cpp"

 void ShortestPath_DIJ(MGraph G,int v0,PathMatrix &P,ShortPathTable &D)
 { // ��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����
   // D[v]����P[v][w]ΪTRUE,��w�Ǵ�v0��v��ǰ������·���ϵĶ��㡣
   // final[v]ΪTRUE���ҽ���v��S,���Ѿ���ô�v0��v�����·�� �㷨7.15
   int v,w,i,j,min;
   Status final[MAX_VERTEX_NUM];
   for(v=0;v<G.vexnum;++v)
   {
     final[v]=FALSE;
     D[v]=G.arcs[v0][v].adj;
     for(w=0;w<G.vexnum;++w)
       P[v][w]=FALSE; // ���·��
     if(D[v]<INFINITY)
     {
       P[v][v0]=TRUE;
       P[v][v]=TRUE;
     }
   }
   D[v0]=0;
   final[v0]=TRUE; // ��ʼ��,v0��������S��
   for(i=1;i<G.vexnum;++i) // ����G.vexnum-1������
   { // ��ʼ��ѭ��,ÿ�����v0��ĳ��v��������·��,����v��S��
     min=INFINITY; // ��ǰ��֪��v0������������
     for(w=0;w<G.vexnum;++w)
       if(!final[w]) // w������V-S��
         if(D[w]<min)
         {
           v=w;
           min=D[w];
         } // w������v0�������
     final[v]=TRUE; // ��v0���������v����S��
     for(w=0;w<G.vexnum;++w) // ���µ�ǰ���·��������
     {
       if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+G.arcs[v][w].adj<D[w]))
       { // �޸�D[w]��P[w],w��V-S
         D[w]=min+G.arcs[v][w].adj;
         for(j=0;j<G.vexnum;++j)
           P[w][j]=P[v][j];
         P[w][w]=TRUE;
       }
     }
   }
 }

 void main()
 {
   int i,j,v0=0; // v0ΪԴ��
   MGraph g;
   PathMatrix p;
   ShortPathTable d;
   CreateDN(g);
   ShortestPath_DIJ(g,v0,p,d);
   printf("���·������p[i][j]����:\n");
   for(i=0;i<g.vexnum;++i)
   {
     for(j=0;j<g.vexnum;++j)
       printf("%2d",p[i][j]);
     printf("\n");
   }
   printf("%s������������·������Ϊ��\n",g.vexs[0]);
   for(i=1;i<g.vexnum;++i)
     printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
 }
