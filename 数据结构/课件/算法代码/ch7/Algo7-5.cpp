 // algo7-5.cpp ��ؼ�·����ʵ���㷨7.13��7.14�ĳ���
 #include"c1.h"
 #define MAX_NAME 5 // �����ַ�������󳤶�+1
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; // �ַ�������
 #include"c7-2.h"
 #include"bo7-2.cpp"

 int ve[MAX_VERTEX_NUM]; // ȫ�ֱ���(�����㷨7.13���㷨7.14)

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
 Status TopologicalOrder(ALGraph G,SqStack &T)
 { // �㷨7.13  ������G�����ڽӱ�洢�ṹ,��������¼������緢��ʱ��ve
   // (ȫ�ֱ���)��TΪ�������ж���ջ,SΪ����ȶ���ջ����G�޻�·,����ջT
   // ����G��һ����������,�Һ���ֵΪOK,����ΪERROR
   int j,k,count,indegree[MAX_VERTEX_NUM];
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree);//�Ը����������indegree[0..vernum-1]
   InitStack(S); // ��ʼ��ջ
   for(j=0;j<G.vexnum;++j) // ������ȶ���ջS
     if(!indegree[j])
       Push(S,j); // ���Ϊ0�߽�ջ
   InitStack(T); // ��ʼ���������ж���ջ
   count=0; // ������������
   for(j=0;j<G.vexnum;++j) // ��ʼ��ve[]=0 (��Сֵ)
     ve[j]=0;
   while(!StackEmpty(S))
   { // ջ����
     Pop(S,j);
     Push(T,j); // j�Ŷ�����Tջ������
     ++count;
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     { // ��j�Ŷ����ÿ���ڽӵ����ȼ�1
       k=p->adjvex;
       if(--indegree[k]==0) // ����ȼ�Ϊ0,����ջ
         Push(S,k);
       if(ve[j]+*(p->info)>ve[k])
         ve[k]=ve[j]+*(p->info);
     }
   }
   if(count<G.vexnum)
   {
     printf("���������л�·\n");
     return ERROR;
   }
   else
     return OK;
 }

 Status CriticalPath(ALGraph G)
 { // �㷨7.14 GΪ������,���G�ĸ���ؼ��
   int vl[MAX_VERTEX_NUM];
   SqStack T;
   int i,j,k,ee,el;
   ArcNode *p;
   char dut,tag;
   if(!TopologicalOrder(G,T)) // ��������
     return ERROR;
   j=ve[0];
   for(i=1;i<G.vexnum;i++) // j=Max(ve[]) ��ɵ��ֵ
     if(ve[i]>j)
       j=ve[i];
   for(i=0;i<G.vexnum;i++) // ��ʼ�������¼�����ٷ���ʱ��(���ֵ)
     vl[i]=j; // ��ɵ�����緢��ʱ��
   while(!StackEmpty(T)) // ������������������vlֵ
     for(Pop(T,j),p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info); // dut<j,k>
       if(vl[k]-dut<vl[j])
         vl[j]=vl[k]-dut;
     }
   printf(" j  k  dut  ee  el  tag\n");
   for(j=0;j<G.vexnum;++j) // ��ee,el�͹ؼ��
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info);
       ee=ve[j];
       el=vl[k]-dut;
       tag=(ee==el)?'*':' ';
       printf("%2d %2d %3d %3d %3d    %c\n",j,k,dut,ee,el,tag); // ����ؼ��
     }
   printf("�ؼ��Ϊ:\n");
   for(j=0;j<G.vexnum;++j) // ͬ��
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info);
       if(ve[j]==vl[k]-dut)
         printf("%s��%s\n",G.vertices[j].data,G.vertices[k].data); // ����ؼ��
     }
   return OK;
 }

 void main()
 {
   ALGraph h;
   printf("��ѡ��������\n");
   CreateGraph(h);
   Display(h);
   CriticalPath(h);
 }
