 // algo7-7.cpp ʵ���㷨7.16�ĳ���
 #define MAX_NAME 5 // �����ַ�������󳤶�+1
 #define MAX_INFO 20 // �����Ϣ�ַ�������󳤶�+1
 typedef int VRType;
 typedef char VertexType[MAX_NAME];
 typedef char InfoType;
 #include"c1.h"
 #include"c7-1.h"
 #include"bo7-1.cpp"
 typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

 void ShortestPath_FLOYD(MGraph G,PathMatrix &P,DistancMatrix &D)
 { // ��Floyd�㷨��������G�и��Զ���v��w֮������·��P[v][w]����
   // ��Ȩ����D[v][w]����P[v][w][u]ΪTRUE,��u�Ǵ�v��w��ǰ������
   // ·���ϵĶ��㡣�㷨7.16
   int u,v,w,i;
   for(v=0;v<G.vexnum;v++) // ���Խ��֮���ʼ��֪·��������
     for(w=0;w<G.vexnum;w++)
     {
       D[v][w]=G.arcs[v][w].adj;
       for(u=0;u<G.vexnum;u++)
         P[v][w][u]=FALSE;
       if(D[v][w]<INFINITY) // ��v��w��ֱ��·��
       {
         P[v][w][v]=TRUE;
         P[v][w][w]=TRUE;
       }
     }
   for(u=0;u<G.vexnum;u++)
     for(v=0;v<G.vexnum;v++)
       for(w=0;w<G.vexnum;w++)
         if(D[v][u]+D[u][w]<D[v][w]) // ��v��u��w��һ��·������
         {
           D[v][w]=D[v][u]+D[u][w];
           for(i=0;i<G.vexnum;i++)
             P[v][w][i]=P[v][u][i]||P[u][w][i];
         }
 }

 void main()
 {
   MGraph g;
   int i,j,k,l,m,n;
   PathMatrix p;
   DistancMatrix d;
   CreateDN(g);
   for(i=0;i<g.vexnum;i++)
     g.arcs[i][i].adj=0; // ShortestPath_FLOYD()Ҫ��Խ�Ԫ��ֵΪ0
   printf("�ڽӾ���:\n");
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
       printf("%11d",g.arcs[i][j]);
     printf("\n");
   }
   ShortestPath_FLOYD(g,p,d);
   printf("d����:\n");
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
       printf("%6d",d[i][j]);
     printf("\n");
   }
   for(i=0;i<g.vexnum;i++)
     for(j=0;j<g.vexnum;j++)
       printf("%s��%s����̾���Ϊ%d\n",g.vexs[i],g.vexs[j],d[i][j]);
   printf("p����:\n");
   l=strlen(g.vexs[0]); // ���������ַ����ĳ���
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
     {
       if(i!=j)
       {
         m=0; // ռλ�ո�
         for(k=0;k<g.vexnum;k++)
           if(p[i][j][k]==1)
             printf("%s",g.vexs[k]);
           else
             m++;
         for(n=0;n<m*l;n++) // ���ռλ�ո�
           printf(" ");
       }
       else
         for(k=0;k<g.vexnum*l;k++) // ���ռλ�ո�
           printf(" ");
       printf("   "); // �������Ԫ��֮��ļ��
     }
     printf("\n");
   }
 }
