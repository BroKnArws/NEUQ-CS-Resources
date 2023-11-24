 // bo7-3.cpp ����ͼ��ʮ������洢(�洢�ṹ��c7-3.h����)�Ļ�������(15��)
 int LocateVex(OLGraph G,VertexType u)
 { // ���ض���u������ͼG�е�λ��(���),�粻�����򷵻�-1
   int i;
   for(i=0;i<G.vexnum;++i) // ��ѭ�����Ҹý��
     if(!strcmp(G.xlist[i].data,u))
       return i;
   return -1;
 }

 Status CreateDG(OLGraph &G)
 { // ����ʮ������洢��ʾ,��������ͼG���㷨7.3
   int i,j,k;
   int IncInfo;
   char str[MAX_Info];
   ArcBox *p;
   VertexType v1,v2;
   printf("����������ͼ�Ķ�����,����,���Ƿ�������Ϣ(��:1����:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_VERTEX_NAME);
   for(i=0;i<G.vexnum;++i)
   { // �����ͷ����
     scanf("%s",&G.xlist[i].data); // ���붥��ֵ
     G.xlist[i].firstin=NULL; // ��ʼ��ָ��
     G.xlist[i].firstout=NULL;
   }
   printf("������%d�����Ļ�β�ͻ�ͷ(�ո�Ϊ���):\n",G.arcnum);
   for(k=0;k<G.arcnum;++k)
   { // �������������ʮ������
     scanf("%s%s",&v1,&v2);
     i=LocateVex(G,v1); // ȷ��v1��v2��G�е�λ��
     j=LocateVex(G,v2);
     p=(ArcBox *)malloc(sizeof(ArcBox)); // ���������(�ٶ����㹻�ռ�)
     p->tailvex=i; // �Ի���㸳ֵ
     p->headvex=j;
     p->hlink=G.xlist[j].firstin; // ������뻡�ͳ��������ͷ�Ĳ���
     p->tlink=G.xlist[i].firstout;
     G.xlist[j].firstin=G.xlist[i].firstout=p;
     if(IncInfo)
     { // �������������Ϣ��������
       printf("������û��������Ϣ(<%d���ַ�): ",MAX_Info);
       scanf("%s",str);
       p->info=(InfoType *)malloc((strlen(str)+1)*sizeof(InfoType));
       strcpy(p->info,str);
     }
     else // �������������Ϣ
       p->info=NULL;
   }
   return OK;
 }

 void DestroyGraph(OLGraph &G)
 { // ��ʼ����: ����ͼG����
   // �������: ��������ͼG
   int j;
   ArcBox *p,*q;
   for(j=0;j<G.vexnum;j++) // �����ж���
   {
     p=G.xlist[j].firstout; // ���������
     while(p)
     {
       q=p;
       p=p->tlink;
       if(q->info)
         free(q->info);
       free(q);
     }
   }
   G.arcnum=0;
   G.vexnum=0;
 }

 VertexType& GetVex(OLGraph G,int v)
 { // ��ʼ����:����ͼG����,v��G��ĳ���������š��������:����v��ֵ
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return G.xlist[v].data;
 }

 Status PutVex(OLGraph &G,VertexType v,VertexType value)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������
   // �������: ��v����ֵvalue
   int i;
   i=LocateVex(G,v);
   if(i<0) // v����G�Ķ���
     return ERROR;
   strcpy(G.xlist[i].data,value);
   return OK;
 }

 int FirstAdjVex(OLGraph G,VertexType v)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������
   // �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1
   int i;
   ArcBox *p;
   i=LocateVex(G,v);
   p=G.xlist[i].firstout; // pָ�򶥵�v�ĵ�1������
   if(p)
     return p->headvex;
   else
     return -1;
 }

 int NextAdjVex(OLGraph G,VertexType v,VertexType w)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������,w��v���ڽӶ���
   // �������: ����v��(�����w��)��һ���ڽӶ�������,
   //           ��w��v�����һ���ڽӶ���,�򷵻�-1
   int i,j;
   ArcBox *p;
   i=LocateVex(G,v); // i�Ƕ���v�����
   j=LocateVex(G,w); // j�Ƕ���w�����
   p=G.xlist[i].firstout; // pָ�򶥵�v�ĵ�1������
   while(p&&p->headvex!=j)
     p=p->tlink;
   if(p) // w����v�����һ���ڽӶ���
     p=p->tlink; // pָ�������w����һ���ڽӶ���
   if(p) // ����һ���ڽӶ���
     return p->headvex;
   else
     return -1;
 }

 void InsertVex(OLGraph &G,VertexType v)
 { // ��ʼ����: ����ͼG����,v������ͼG�ж�������ͬ����
   // �������: ������ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)
   strcpy(G.xlist[G.vexnum].data,v);
   G.xlist[G.vexnum].firstin=G.xlist[G.vexnum].firstout=NULL;
   G.vexnum++;
 }

 Status DeleteVex(OLGraph &G,VertexType v)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������
   // �������: ɾ��G�ж���v������صĻ�
   int j,k;
   ArcBox *p,*q;
   k=LocateVex(G,v); // k�Ƕ���v�����
   if(k<0) // v����ͼG�Ķ���
     return ERROR;
   // ����ɾ������v�ĳ���
   for(j=0;j<G.vexnum;j++) // ����v�ĳ���������������뻡
   {
     if(j==k)
       continue;
     p=G.xlist[j].firstin; // ������������뻡������ɾ������v�ĳ���
     while(p)
       if(p->tailvex==k&&p==G.xlist[j].firstin) // ��ɾ���Ϊ�׽��
       {
         G.xlist[j].firstin=p->hlink;
         break;
       }
       else if(p->tailvex!=k) // û�ҵ���ɾ���
       {
         q=p;
         p=p->hlink;
       }
       else // �ҵ���ɾ����Ҳ����׽��
       {
         q->hlink=p->hlink;
         break;
       }
   }
   p=G.xlist[k].firstout; // ɾ���붥��v�йصĳ���
   while(p)
   {
     q=p->tlink; // qָ��p����һ������
     if(p->info) // �ͷ�p
       free(p->info);
     free(p);
     G.arcnum--;
     p=q;
   }
   // ����ɾ������v���뻡
   for(j=0;j<G.vexnum;j++) // ����v���뻡����������ĳ���
   {
     if(j==k)
       continue;
     p=G.xlist[j].firstout; // ����������ĳ���������ɾ������v���뻡
     while(p)
       if(p->headvex==k&&p==G.xlist[j].firstout) // ��ɾ���Ϊ�׽��
       {
         G.xlist[j].firstout=p->tlink;
         break;
       }
       else if(p->headvex!=k) // û�ҵ���ɾ���
       {
         q=p;
         p=p->tlink;
       }
       else // �ҵ���ɾ����Ҳ����׽��
       {
	 q->tlink=p->tlink;
         break;
       }
   }
   p=G.xlist[k].firstin; // ɾ���붥��v�йص��뻡
   while(p)
   {
     q=p->hlink; // qָ��p����һ���뻡
     if(p->info) // �ͷ�p
       free(p->info);
     free(p);
     G.arcnum--;
     p=q;
   }
   for(j=k+1;j<G.vexnum;j++) // ���>k�Ķ���������ǰ��
     G.xlist[j-1]=G.xlist[j];
   G.vexnum--; // ��������1
   for(j=0;j<G.vexnum;j++) // ������>k��Ҫ��1
   {
     p=G.xlist[j].firstout; // �������
     while(p)
     {
       if(p->tailvex>k)
         p->tailvex--; // ���-1
       if(p->headvex>k)
         p->headvex--; // ���-1
       p=p->tlink;
     }
   }
   return OK;
 }

 Status InsertArc(OLGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ����ͼG����,v��w��G����������
   // �������: ��G������<v,w>
   int i,j;
   int IncInfo;
   char str[MAX_Info];
   ArcBox *p;
   i=LocateVex(G,v); // ��β�����
   j=LocateVex(G,w); // ��ͷ�����
   if(i<0||j<0)
     return ERROR;
   p=(ArcBox *)malloc(sizeof(ArcBox)); // �����½��
   p->tailvex=i; // ���½�㸳ֵ
   p->headvex=j;
   p->hlink=G.xlist[j].firstin; // �����뻡�ͳ�������ͷ
   p->tlink=G.xlist[i].firstout;
   G.xlist[j].firstin=G.xlist[i].firstout=p;
   G.arcnum++; // ������1
   printf("Ҫ����Ļ��Ƿ���������Ϣ(��: 1,��: 0): ");
   scanf("%d",&IncInfo);
   if(IncInfo)
   {
     printf("������û��������Ϣ(<%d���ַ�): ",MAX_Info);
     scanf("%s",str);
     p->info=(InfoType *)malloc((strlen(str)+1)*sizeof(InfoType));
     strcpy(p->info,str);
   }
   else
     p->info=NULL;
   return OK;
 }

 Status DeleteArc(OLGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ����ͼG����,v��w��G����������
   // �������: ��G��ɾ����<v,w>
   int i,j;
   ArcBox *p1,*p2;
   i=LocateVex(G,v); // ��β�����
   j=LocateVex(G,w); // ��ͷ�����
   if(i<0||j<0||i==j)
     return ERROR;
   p2=G.xlist[i].firstout; // �������ӳ���������ɾȥ
   if(p2&&p2->headvex==j) // ��1�����Ϊ��ɾ�����
     G.xlist[i].firstout=p2->tlink;
   else
   {
     while(p2&&p2->headvex!=j) // �����
     {
       p1=p2;
       p2=p2->tlink;
     }
     if(p2) // û����β
       p1->tlink=p2->tlink;
   }
   p2=G.xlist[j].firstin; // ���������뻡������ɾȥ
   if(p2&&p2->tailvex==i)
     G.xlist[j].firstin=p2->hlink;
   else
   {
     while(p2&&p2->tailvex!=i)
     {
       p1=p2;
       p2=p2->hlink;
     }
     if(p2) // û����β
       p1->hlink=p2->hlink;
   }
   if(p2->info) // �ͷŻ����
     free(p2->info);
   free(p2);
   G.arcnum--; // ������1
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; // ���ʱ�־����
 Status(*VisitFunc)(VertexType); // ��������
 void DFS(OLGraph G,int i) // DFSTraverse()����
 {
   ArcBox *p;
   visited[i]=TRUE; // ���ʱ�־������1(�ѱ�����)
   VisitFunc(G.xlist[i].data); // ������i������
   p=G.xlist[i].firstout; // pָ���i������ĳ���
   while(p&&visited[p->headvex]) // pû����β�Ҹû���ͷ�����ѱ�����
     p=p->tlink; // ������һ�����
   if(p&&!visited[p->headvex]) // �û���ͷ����δ������
     DFS(G,p->headvex); // �ݹ����DFS()
 }

 void DFSTraverse(OLGraph G,Status(*Visit)(VertexType))
 { // ��ʼ����: ����ͼG����,v��G��ĳ������,Visit�Ƕ����Ӧ�ú���
   // �������: �ӵ�1��������,��������ȵݹ��������ͼG,����ÿ���������
   //           ����Visitһ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ��
   int i;
   for(i=0;i<G.vexnum;i++)
     visited[i]=FALSE; // ���ʱ�־�����ó�ֵ(δ������)
   VisitFunc=Visit;
   for(i=0;i<G.vexnum;i++) // �����0��ʼ,��������δ�����ʹ��Ķ���
     if(!visited[i])
       DFS(G,i);
   printf("\n");
 }

 typedef int QElemType;
 #include"c3-3.h"
 #include"bo3-3.cpp"
 void BFSTraverse(OLGraph G,Status(*Visit)(VertexType))
 { // ��ʼ����: ����ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.6
   // �������: �ӵ�1��������,��������ȷǵݹ��������ͼG,����ÿ���������
   //           ����Visitһ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ�ܡ�
   //           ʹ�ø�������Q�ͷ��ʱ�־����visited
   int v,u,w;
   VertexType u1,w1;
   SqQueue Q;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE;
   InitQueue(Q);
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
     {
       visited[v]=TRUE;
       Visit(G.xlist[v].data);
       EnQueue(Q,v);
       while(!QueueEmpty(Q))
       {
         DeQueue(Q,u);
         strcpy(u1,GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,GetVex(G,w))))
           if(!visited[w]) // wΪu����δ���ʵ��ڽӶ�������
           {
             visited[w]=TRUE;
             Visit(G.xlist[w].data);
             EnQueue(Q,w);
           }
       }
     }
   printf("\n");
 }

 void Display(OLGraph G)
 { // �������ͼG
   int i;
   ArcBox *p;
   printf("��%d������,%d����:\n",G.vexnum,G.arcnum);
   for(i=0;i<G.vexnum;i++)
   {
     printf("����%s: ���: ",G.xlist[i].data);
     p=G.xlist[i].firstin;
     while(p)
     {
       printf("%s ",G.xlist[p->tailvex].data);
       p=p->hlink;
     }
     printf("����: ");
     p=G.xlist[i].firstout;
     while(p)
     {
       printf("%s ",G.xlist[p->headvex].data);
       if(p->info) // �û��������Ϣ
         printf("����Ϣ: %s ",p->info);
       p=p->tlink;
     }
     printf("\n");
   }
 }
