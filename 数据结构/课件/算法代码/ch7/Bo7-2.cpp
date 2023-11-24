 // bo7-2.cpp ͼ���ڽӱ�洢(�洢�ṹ��c7-2.h����)�Ļ�������(15��)
 int LocateVex(ALGraph G,VertexType u)
 { // ��ʼ����: ͼG����,u��G�ж�������ͬ����
   // �������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vertices[i].data)==0)
       return i;
   return -1;
 }

 Status CreateGraph(ALGraph &G)
 { // �����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG(��һ����������4��ͼ)
   int i,j,k;
   int w; // Ȩֵ
   VertexType va,vb;
   ArcNode *p;
   printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3): ");
   scanf("%d",&G.kind);
   printf("������ͼ�Ķ�����,����: ");
   scanf("%d,%d",&G.vexnum,&G.arcnum);
   printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
   for(i=0;i<G.vexnum;++i) // ���춥������
   {
     scanf("%s",G.vertices[i].data);
     G.vertices[i].firstarc=NULL;
   }
   if(G.kind==1||G.kind==3) // ��
     printf("��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���):\n");
   else // ͼ
     printf("��˳������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���):\n");
   for(k=0;k<G.arcnum;++k) // �����������
   {
     if(G.kind==1||G.kind==3) // ��
       scanf("%d%s%s",&w,va,vb);
     else // ͼ
       scanf("%s%s",va,vb);
     i=LocateVex(G,va); // ��β
     j=LocateVex(G,vb); // ��ͷ
     p=(ArcNode*)malloc(sizeof(ArcNode));
     p->adjvex=j;
     if(G.kind==1||G.kind==3) // ��
     {
       p->info=(int *)malloc(sizeof(int));
       *(p->info)=w;
     }
     else
       p->info=NULL; // ͼ
     p->nextarc=G.vertices[i].firstarc; // ���ڱ�ͷ
     G.vertices[i].firstarc=p;
     if(G.kind>=2) // ����ͼ����,�����ڶ�������
     {
       p=(ArcNode*)malloc(sizeof(ArcNode));
       p->adjvex=i;
       if(G.kind==3) // ������
       {
         p->info=(int*)malloc(sizeof(int));
         *(p->info)=w;
       }
       else
         p->info=NULL; // ����ͼ
       p->nextarc=G.vertices[j].firstarc; // ���ڱ�ͷ
       G.vertices[j].firstarc=p;
     }
   }
   return OK;
 }

 void DestroyGraph(ALGraph &G)
 { // ��ʼ����: ͼG���ڡ��������: ����ͼG
   int i;
   ArcNode *p,*q;
   G.vexnum=0;
   G.arcnum=0;
   for(i=0;i<G.vexnum;++i)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       q=p->nextarc;
       if(G.kind%2) // ��
         free(p->info);
       free(p);
       p=q;
     }
   }
 }

 VertexType& GetVex(ALGraph G,int v)
 { // ��ʼ����: ͼG����,v��G��ĳ���������š��������: ����v��ֵ
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return G.vertices[v].data;
 }

 Status PutVex(ALGraph &G,VertexType v,VertexType value)
 { // ��ʼ����: ͼG����,v��G��ĳ������
   // �������: ��v����ֵvalue
   int i;
   i=LocateVex(G,v);
   if(i>-1) // v��G�Ķ���
   {
     strcpy(G.vertices[i].data,value);
     return OK;
   }
   return ERROR;
 }

 int FirstAdjVex(ALGraph G,VertexType v)
 { // ��ʼ����: ͼG����,v��G��ĳ������
   // �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1
   ArcNode *p;
   int v1;
   v1=LocateVex(G,v); // v1Ϊ����v��ͼG�е����
   p=G.vertices[v1].firstarc;
   if(p)
     return p->adjvex;
   else
     return -1;
 }

 int NextAdjVex(ALGraph G,VertexType v,VertexType w)
 { // ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ���
   // �������: ����v��(�����w��)��һ���ڽӶ������š�
   //           ��w��v�����һ���ڽӵ�,�򷵻�-1
   ArcNode *p;
   int v1,w1;
   v1=LocateVex(G,v); // v1Ϊ����v��ͼG�е����
   w1=LocateVex(G,w); // w1Ϊ����w��ͼG�е����
   p=G.vertices[v1].firstarc;
   while(p&&p->adjvex!=w1) // ָ��p��������ָ���㲻��w
     p=p->nextarc;
   if(!p||!p->nextarc) // û�ҵ�w��w�����һ���ڽӵ�
     return -1;
   else // p->adjvex==w
     return p->nextarc->adjvex; // ����v��(�����w��)��һ���ڽӶ�������
 }

 void InsertVex(ALGraph &G,VertexType v)
 { // ��ʼ����: ͼG����,v��ͼ�ж�������ͬ����
   // �������: ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)
   strcpy(G.vertices[G.vexnum].data,v); // �����¶�������
   G.vertices[G.vexnum].firstarc=NULL;
   G.vexnum++; // ͼG�Ķ�������1
 }

 Status DeleteVex(ALGraph &G,VertexType v)
 { // ��ʼ����: ͼG����,v��G��ĳ������
   // �������: ɾ��G�ж���v������صĻ�
   int i,j;
   ArcNode *p,*q;
   j=LocateVex(G,v); // j�Ƕ���v�����
   if(j<0) // v����ͼG�Ķ���
     return ERROR;
   p=G.vertices[j].firstarc; // ɾ����vΪ���ȵĻ����
   while(p)
   {
     q=p;
     p=p->nextarc;
     if(G.kind%2) // ��
       free(q->info);
     free(q);
     G.arcnum--; // ���������1
   }
   G.vexnum--; // ��������1
   for(i=j;i<G.vexnum;i++) // ����v����Ķ���ǰ��
     G.vertices[i]=G.vertices[i+1];
   for(i=0;i<G.vexnum;i++) // ɾ����vΪ��ȵĻ�����ұ�Ҫʱ�޸ı���Ķ���λ��ֵ
   {
     p=G.vertices[i].firstarc; // ָ���1�������
     while(p) // �л�
     {
       if(p->adjvex==j)
       {
         if(p==G.vertices[i].firstarc) // ��ɾ����ǵ�1�����
         {
           G.vertices[i].firstarc=p->nextarc;
           if(G.kind%2) // ��
             free(p->info);
           free(p);
           p=G.vertices[i].firstarc;
           if(G.kind<2) // ����
             G.arcnum--; // ���������1
         }
         else
         {
           q->nextarc=p->nextarc;
           if(G.kind%2) // ��
             free(p->info);
           free(p);
           p=q->nextarc;
           if(G.kind<2) // ����
             G.arcnum--; // ���������1
         }
       }
       else
       {
         if(p->adjvex>j)
           p->adjvex--; // �޸ı���Ķ���λ��ֵ(���)
         q=p;
         p=p->nextarc;
       }
     }
   }
   return OK;
 }

 Status InsertArc(ALGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ͼG����,v��w��G����������
   // �������: ��G������<v,w>,��G�������,������Գƻ�<w,v>
   ArcNode *p;
   int w1,i,j;
   i=LocateVex(G,v); // ��β��ߵ����
   j=LocateVex(G,w); // ��ͷ��ߵ����
   if(i<0||j<0)
     return ERROR;
   G.arcnum++; // ͼG�Ļ���ߵ���Ŀ��1
   if(G.kind%2) // ��
   {
     printf("�����뻡(��)%s��%s��Ȩֵ: ",v,w);
     scanf("%d",&w1);
   }
   p=(ArcNode*)malloc(sizeof(ArcNode));
   p->adjvex=j;
   if(G.kind%2) // ��
   {
     p->info=(int*)malloc(sizeof(int));
     *(p->info)=w1;
   }
   else
     p->info=NULL;
   p->nextarc=G.vertices[i].firstarc; // ���ڱ�ͷ
   G.vertices[i].firstarc=p;
   if(G.kind>=2) // ����,������һ������
   {
     p=(ArcNode*)malloc(sizeof(ArcNode));
     p->adjvex=i;
     if(G.kind==3) // ������
     {
       p->info=(int*)malloc(sizeof(int));
       *(p->info)=w1;
     }
     else
       p->info=NULL;
     p->nextarc=G.vertices[j].firstarc; // ���ڱ�ͷ
     G.vertices[j].firstarc=p;
   }
   return OK;
 }

 Status DeleteArc(ALGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ͼG����,v��w��G����������
   // �������: ��G��ɾ����<v,w>,��G�������,��ɾ���Գƻ�<w,v>
   ArcNode *p,*q;
   int i,j;
   i=LocateVex(G,v); // i�Ƕ���v(��β)�����
   j=LocateVex(G,w); // j�Ƕ���w(��ͷ)�����
   if(i<0||j<0||i==j)
     return ERROR;
   p=G.vertices[i].firstarc; // pָ�򶥵�v�ĵ�һ������
   while(p&&p->adjvex!=j) // p��������ָ֮�����Ǵ�ɾ����<v,w>
   { // pָ����һ����
     q=p;
     p=p->nextarc;
   }
   if(p&&p->adjvex==j) // �ҵ���<v,w>
   {
     if(p==G.vertices[i].firstarc) // p��ָ�ǵ�1����
       G.vertices[i].firstarc=p->nextarc; // ָ����һ����
     else
       q->nextarc=p->nextarc; // ָ����һ����
     if(G.kind%2) // ��
       free(p->info);
     free(p); // �ͷŴ˽��
     G.arcnum--; // ���������1
   }
   if(G.kind>=2) // ����,ɾ���Գƻ�<w,v>
   {
     p=G.vertices[j].firstarc; // pָ�򶥵�w�ĵ�һ������
     while(p&&p->adjvex!=i) // p��������ָ֮�����Ǵ�ɾ����<w,v>
     { // pָ����һ����
       q=p;
       p=p->nextarc;
     }
     if(p&&p->adjvex==i) // �ҵ���<w,v>
     {
       if(p==G.vertices[j].firstarc) // p��ָ�ǵ�1����
         G.vertices[j].firstarc=p->nextarc; // ָ����һ����
       else
         q->nextarc=p->nextarc; // ָ����һ����
       if(G.kind==3) // ������
         free(p->info);
       free(p); // �ͷŴ˽��
     }
   }
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; // ���ʱ�־����(ȫ����)
 void(*VisitFunc)(char* v); // ��������(ȫ����)
 void DFS(ALGraph G,int v)
 { // �ӵ�v����������ݹ��������ȱ���ͼG���㷨7.5
   int w;
   VertexType v1,w1;
   strcpy(v1,GetVex(G,v));
   visited[v]=TRUE; // ���÷��ʱ�־ΪTRUE(�ѷ���)
   VisitFunc(G.vertices[v].data); // ���ʵ�v������
   for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,GetVex(G,w))))
     if(!visited[w])
       DFS(G,w); // ��v����δ���ʵ��ڽӵ�w�ݹ����DFS
 }

 void DFSTraverse(ALGraph G,void(*Visit)(char*))
 { // ��ͼG��������ȱ������㷨7.4
   int v;
   VisitFunc=Visit; // ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ�����
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; // ���ʱ�־�����ʼ��
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); // ����δ���ʵĶ������DFS
   printf("\n");
 }

 typedef int QElemType; // ��������
 #include"c3-2.h"
 #include"bo3-2.cpp"
 void BFSTraverse(ALGraph G,void(*Visit)(char*))
 {//��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited���㷨7.6
   int v,u,w;
   VertexType u1,w1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; // �ó�ֵ
   InitQueue(Q); // �ÿյĸ�������Q
   for(v=0;v<G.vexnum;v++) // �������ͨͼ,ֻv=0�ͱ���ȫͼ
     if(!visited[v]) // v��δ����
     {
       visited[v]=TRUE;
       Visit(G.vertices[v].data);
       EnQueue(Q,v); // v�����
       while(!QueueEmpty(Q)) // ���в���
       {
         DeQueue(Q,u); // ��ͷԪ�س��Ӳ���Ϊu
         strcpy(u1,GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,GetVex(G,w))))
           if(!visited[w]) // wΪu����δ���ʵ��ڽӶ���
           {
             visited[w]=TRUE;
             Visit(G.vertices[w].data);
             EnQueue(Q,w); // w���
           }
       }
     }
   printf("\n");
 }

 void Display(ALGraph G)
 { // ���ͼ���ڽӾ���G
   int i;
   ArcNode *p;
   switch(G.kind)
   {
     case DG: printf("����ͼ\n");
              break;
     case DN: printf("������\n");
              break;
     case AG: printf("����ͼ\n");
              break;
     case AN: printf("������\n");
   }
   printf("%d�����㣺\n",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     printf("%s ",G.vertices[i].data);
   printf("\n%d����(��):\n",G.arcnum);
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       if(G.kind<=1) // ����
       {
         printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
         if(G.kind==DN) // ��
           printf(":%d ",*(p->info));
       }
       else // ����(�����������)
       {
         if(i<p->adjvex)
         {
           printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
           if(G.kind==AN) // ��
             printf(":%d ",*(p->info));
         }
       }
       p=p->nextarc;
     }
     printf("\n");
   }
 }
