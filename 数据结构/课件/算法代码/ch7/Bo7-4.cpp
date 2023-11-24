 // bo7-4.cpp ����ͼ���ڽӶ��ر�洢(�洢�ṹ��c7-4.h����)�Ļ�����������(16��)
 int LocateVex(AMLGraph G,VertexType u)
 { // ��ʼ����: ����ͼG����,u��G�ж�������ͬ����
   // �������: ��G�д��ڶ���u,�򷵻ظö���������ͼ��λ��;���򷵻�-1
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.adjmulist[i].data)==0)
       return i;
   return -1;
 }

 Status CreateGraph(AMLGraph &G)
 { // �����ڽӶ��ر�洢�ṹ,��������ͼG
   int i,j,k,l,IncInfo;
   char s[MAX_INFO];
   VertexType va,vb;
   EBox *p;
   printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1����:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.edgenum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
   for(i=0;i<G.vexnum;++i) // ���춥������
   {
     scanf("%s",G.adjmulist[i].data);
     G.adjmulist[i].firstedge=NULL;
   }
   printf("��˳������ÿ���ߵ������˵�(�Կո���Ϊ���):\n");
   for(k=0;k<G.edgenum;++k) // �����������
   {
     scanf("%s%s%*c",va,vb); // %*c�Ե��س���
     i=LocateVex(G,va); // һ��
     j=LocateVex(G,vb); // ��һ��
     p=(EBox*)malloc(sizeof(EBox));
     p->mark=unvisited; // ���ֵ
     p->ivex=i;
     p->jvex=j;
     p->info=NULL;
     p->ilink=G.adjmulist[i].firstedge; // ���ڱ�ͷ
     G.adjmulist[i].firstedge=p;
     p->jlink=G.adjmulist[j].firstedge; // ���ڱ�ͷ
     G.adjmulist[j].firstedge=p;
     if(IncInfo) // ���������Ϣ
     {
       printf("������û��������Ϣ(<%d���ַ�)��",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         p->info=(char*)malloc((l+1)*sizeof(char));
         strcpy(p->info,s);
       }
     }
   }
   return OK;
 }

 VertexType& GetVex(AMLGraph G,int v)
 { // ��ʼ����: ����ͼG����,v��G��ĳ���������š��������: ����v��ֵ
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return G.adjmulist[v].data;
 }

 Status PutVex(AMLGraph &G,VertexType v,VertexType value)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������
   // �������: ��v����ֵvalue
   int i;
   i=LocateVex(G,v);
   if(i<0) // v����G�Ķ���
     return ERROR;
   strcpy(G.adjmulist[i].data,value);
   return OK;
 }

 int FirstAdjVex(AMLGraph G,VertexType v)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������
   // �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1
   int i;
   i=LocateVex(G,v);
   if(i<0)
     return -1;
   if(G.adjmulist[i].firstedge) // v���ڽӶ���
     if(G.adjmulist[i].firstedge->ivex==i)
       return G.adjmulist[i].firstedge->jvex;
     else
       return G.adjmulist[i].firstedge->ivex;
   else
     return -1;
 }

 int NextAdjVex(AMLGraph G,VertexType v,VertexType w)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������,w��v���ڽӶ���
   // �������: ����v��(�����w��)��һ���ڽӶ������š�
   //           ��w��v�����һ���ڽӵ�,�򷵻�-1
   int i,j;
   EBox *p;
   i=LocateVex(G,v); // i�Ƕ���v�����
   j=LocateVex(G,w); // j�Ƕ���w�����
   if(i<0||j<0) // v��w����G�Ķ���
     return -1;
   p=G.adjmulist[i].firstedge; // pָ�򶥵�v�ĵ�1����
   while(p)
     if(p->ivex==i&&p->jvex!=j) // �����ڽӶ���w(���1)
       p=p->ilink; // ����һ���ڽӶ���
     else if(p->jvex==i&&p->ivex!=j) // �����ڽӶ���w(���2)
       p=p->jlink; // ����һ���ڽӶ���
     else // ���ڽӶ���w
       break;
   if(p&&p->ivex==i&&p->jvex==j) // �ҵ��ڽӶ���w(���1)
   {
     p=p->ilink;
     if(p&&p->ivex==i)
       return p->jvex;
     else if(p&&p->jvex==i)
       return p->ivex;
   }
   if(p&&p->ivex==j&&p->jvex==i) // �ҵ��ڽӶ���w(���2)
   {
     p=p->jlink;
     if(p&&p->ivex==i)
       return p->jvex;
     else if(p&&p->jvex==i)
       return p->ivex;
   }
   return -1;
 }

 Status InsertVex(AMLGraph &G,VertexType v)
 { // ��ʼ����: ����ͼG����,v��G�ж�������ͬ����
   // �������: ��G�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)
   if(G.vexnum==MAX_VERTEX_NUM) // ������������ܲ���
     return ERROR;
   if(LocateVex(G,v)>=0) // ����Ѵ���,���ܲ���
     return ERROR;
   strcpy(G.adjmulist[G.vexnum].data,v);
   G.adjmulist[G.vexnum].firstedge=NULL;
   G.vexnum++;
   return OK;
 }

 Status DeleteArc(AMLGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ����ͼG����,v��w��G����������
   // �������: ��G��ɾ����<v,w>
   int i,j;
   EBox *p,*q;
   i=LocateVex(G,v);
   j=LocateVex(G,w);
   if(i<0||j<0||i==j)
     return ERROR;  // ͼ��û�иõ��
   // ����ʹָ���ɾ���ߵĵ�1��ָ���ƹ�������
   p=G.adjmulist[i].firstedge; // pָ�򶥵�v�ĵ�1����
   if(p&&p->jvex==j) // ��1���߼�Ϊ��ɾ����(���1)
     G.adjmulist[i].firstedge=p->ilink;
   else if(p&&p->ivex==j) // ��1���߼�Ϊ��ɾ����(���2)
     G.adjmulist[i].firstedge=p->jlink;
   else // ��1���߲��Ǵ�ɾ����
   {
     while(p) // �����һ�<v,w>
     {
       if(p->ivex==i&&p->jvex!=j) // ���Ǵ�ɾ����
       {
         q=p;
         p=p->ilink; // ����һ���ڽӶ���
       }
       else if(p->jvex==i&&p->ivex!=j) // ���Ǵ�ɾ����
       {
         q=p;
         p=p->jlink; // ����һ���ڽӶ���
       }
       else // ���ڽӶ���w
         break;
     }
     if(!p) // û�ҵ��ñ�
       return ERROR;
     if(p->ivex==i&&p->jvex==j) // �ҵ���<v,w>(���1)
       if(q->ivex==i)
         q->ilink=p->ilink;
       else
         q->jlink=p->ilink;
     else if(p->ivex==j&&p->jvex==i) // �ҵ���<v,w>(���2)
       if(q->ivex==i)
         q->ilink=p->jlink;
       else
         q->jlink=p->jlink;
   }
   // ��������һ�������Ҵ�ɾ������ɾ��֮
   p=G.adjmulist[j].firstedge; // pָ�򶥵�w�ĵ�1����
   if(p->jvex==i) // ��1���߼�Ϊ��ɾ����(���1)
   {
     G.adjmulist[j].firstedge=p->ilink;
     if(p->info) // �������Ϣ
       free(p->info);
     free(p);
   }
   else if(p->ivex==i) // ��1���߼�Ϊ��ɾ����(���2)
   {
     G.adjmulist[j].firstedge=p->jlink;
     if(p->info) // �������Ϣ
       free(p->info);
     free(p);
   }
   else // ��1���߲��Ǵ�ɾ����
   {
     while(p) // �����һ�<v,w>
       if(p->ivex==j&&p->jvex!=i) // ���Ǵ�ɾ����
       {
         q=p;
         p=p->ilink; // ����һ���ڽӶ���
       }
       else if(p->jvex==j&&p->ivex!=i) // ���Ǵ�ɾ����
       {
         q=p;
         p=p->jlink; // ����һ���ڽӶ���
       }
       else // ���ڽӶ���v
         break;
     if(p->ivex==i&&p->jvex==j) // �ҵ���<v,w>(���1)
     {
       if(q->ivex==j)
         q->ilink=p->jlink;
       else
         q->jlink=p->jlink;
       if(p->info) // �������Ϣ
         free(p->info);
       free(p);
     }
     else if(p->ivex==j&&p->jvex==i) // �ҵ���<v,w>(���2)
     {
       if(q->ivex==j)
         q->ilink=p->ilink;
       else
         q->jlink=p->ilink;
       if(p->info) // �������Ϣ
         free(p->info);
       free(p);
     }
   }
   G.edgenum--;
   return OK;
 }

 Status DeleteVex(AMLGraph &G,VertexType v)
 { // ��ʼ����: ����ͼG����,v��G��ĳ������
   // �������: ɾ��G�ж���v������صı�
   int i,j;
   VertexType w;
   EBox *p;
   i=LocateVex(G,v); // iΪ��ɾ����������
   if(i<0)
     return ERROR;
   for(j=0;j<G.vexnum;j++) // ɾ���붥��v�����ı�(����еĻ�)
   {
     if(j==i)
       continue;
     strcpy(w,GetVex(G,j)); // w�ǵ�j�������ֵ
     DeleteArc(G,v,w);
   }
   for(j=i+1;j<G.vexnum;j++) // ���ڶ���v����Ķ������ż�1
     G.adjmulist[j-1]=G.adjmulist[j];
   G.vexnum--; // ��������1
   for(j=i;j<G.vexnum;j++) // �޸Ķ�������
   {
     p=G.adjmulist[j].firstedge;
     if(p)
     {
       if(p->ivex==j+1)
       {
         p->ivex--;
         p=p->ilink;
       }
       else
       {
         p->jvex--;
         p=p->jlink;
       }
     }
   }
   return OK;
 }

 void DestroyGraph(AMLGraph &G)
 {
   int i;
   for(i=G.vexnum-1;i>=0;i--)
     DeleteVex(G,G.adjmulist[i].data);
 }

 Status InsertArc(AMLGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ����ͼG����,v��W��G����������
   // �������: ��G������<v,w>
   int i,j,l,IncInfo;
   char s[MAX_INFO];
   EBox *p;
   i=LocateVex(G,v); // һ��
   j=LocateVex(G,w); // ��һ��
   if(i<0||j<0)
     return ERROR;
   p=(EBox*)malloc(sizeof(EBox));
   p->mark=unvisited;
   p->ivex=i;
   p->jvex=j;
   p->info=NULL;
   p->ilink=G.adjmulist[i].firstedge; // ���ڱ�ͷ
   G.adjmulist[i].firstedge=p;
   p->jlink=G.adjmulist[j].firstedge; // ���ڱ�ͷ
   G.adjmulist[j].firstedge=p;
   printf("�ñ��Ƿ��������Ϣ(1:�� 0:��): ");
   scanf("%d%*c",&IncInfo); // %*c�Ե��س���
   if(IncInfo) // ���������Ϣ
   {
     printf("������ñߵ������Ϣ(<%d���ַ�)��",MAX_INFO);
     gets(s);
     l=strlen(s);
     if(l)
     {
       p->info=(char*)malloc((l+1)*sizeof(char));
       strcpy(p->info,s);
     }
   }
   G.edgenum++;
   return OK;
 }

 Boolean visite[MAX_VERTEX_NUM]; // ���ʱ�־����(ȫ����)
 Status(*VisitFunc)(VertexType v);
 void DFS(AMLGraph G,int v)
 {
   int j;
   EBox *p;
   VisitFunc(G.adjmulist[v].data);
   visite[v]=TRUE;
   p=G.adjmulist[v].firstedge;
   while(p)
   {
     j=p->ivex==v?p->jvex:p->ivex;
     if(!visite[j])
       DFS(G,j);
     p=p->ivex==v?p->ilink:p->jlink;
   }
 }

 void DFSTraverse(AMLGraph G,Status(*visit)(VertexType))
 { // ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.4
   // �������: �ӵ�1��������,������ȱ���ͼG,����ÿ��������ú���Visit
   //           һ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ��
   int v;
   VisitFunc=visit;
   for(v=0;v<G.vexnum;v++)
     visite[v]=FALSE;
   for(v=0;v<G.vexnum;v++)
     if(!visite[v])
       DFS(G,v);
   printf("\n");
 }

 typedef int QElemType; // ��������
 #include"c3-2.h" // BFSTraverse()��
 #include"bo3-2.cpp" // BFSTraverse()��
 void BFSTraverse(AMLGraph G,Status(*Visit)(VertexType))
 { // ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.6
   // �������: �ӵ�1��������,��������ȷǵݹ����ͼG,����ÿ��������ú���
   //           Visitһ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ�ܡ�
   //           ʹ�ø�������Q�ͷ��ʱ�־����visite
   int v,u,w;
   VertexType w1,u1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;v++)
     visite[v]=FALSE; // �ó�ֵ
   InitQueue(Q); // �ÿյĸ�������Q
   for(v=0;v<G.vexnum;v++)
     if(!visite[v]) // v��δ����
     {
       visite[v]=TRUE; // ���÷��ʱ�־ΪTRUE(�ѷ���)
       Visit(G.adjmulist[v].data);
       EnQueue(Q,v); // v�����
       while(!QueueEmpty(Q)) // ���в���
       {
         DeQueue(Q,u); // ��ͷԪ�س��Ӳ���Ϊu
         strcpy(u1,GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,GetVex(G,w))))
           if(!visite[w]) // wΪu����δ���ʵ��ڽӶ�������
           {
             visite[w]=TRUE;
             Visit(G.adjmulist[w].data);
             EnQueue(Q,w);
           }
       }
     }
   printf("\n");
 }

 void MarkUnvizited(AMLGraph G)
 { // �ñߵķ��ʱ��Ϊδ������
   int i;
   EBox *p;
   for(i=0;i<G.vexnum;i++)
   {
     p=G.adjmulist[i].firstedge;
     while(p)
     {
       p->mark=unvisited;
       if(p->ivex==i)
         p=p->ilink;
       else
         p=p->jlink;
     }
   }
 }

 void Display(AMLGraph G)
 { // �������ͼ���ڽӶ��ر�G
   int i;
   EBox *p;
   MarkUnvizited(G); // �ñߵķ��ʱ��Ϊδ������
   printf("%d�����㣺\n",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     printf("%s ",G.adjmulist[i].data);
   printf("\n%d����:\n",G.edgenum);
   for(i=0;i<G.vexnum;i++)
   {
     p=G.adjmulist[i].firstedge;
     while(p)
       if(p->ivex==i) // �ߵ�i����ö����й�
       {
         if(!p->mark) // ֻ���һ��
         {
           printf("%s��%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
           p->mark=visited;
           if(p->info) // ���������Ϣ
             printf("�����Ϣ: %s ",p->info);
         }
         p=p->ilink;
       }
       else // �ߵ�j����ö����й�
       {
         if(!p->mark) // ֻ���һ��
         {
           printf("%s��%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
           p->mark=visited;
           if(p->info) // ���������Ϣ
             printf("�����Ϣ: %s ",p->info);
         }
         p=p->jlink;
       }
     printf("\n");
   }
 }
