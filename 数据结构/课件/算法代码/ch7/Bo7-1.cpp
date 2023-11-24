 // bo7-1.cpp ͼ������(�ڽӾ���)�洢(�洢�ṹ��c7-1.h����)�Ļ�������(20��)
 int LocateVex(MGraph G,VertexType u)
 { // ��ʼ����:ͼG����,u��G�ж�������ͬ����
   // �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vexs[i])==0)
       return i;
   return -1;
 }

 Status CreateFAG(MGraph &G)
 { // ��������(�ڽӾ���)��ʾ��,���ļ�����û�������Ϣ������ͼG
   int i,j,k;
   char filename[13];
   VertexType va,vb;
   FILE *graphlist;
   printf("�����������ļ���(f7-1.dat)��");
   scanf("%s",filename);
   graphlist=fopen(filename,"r");
   fscanf(graphlist,"%d",&G.vexnum);
   fscanf(graphlist,"%d",&G.arcnum);
   for(i=0;i<G.vexnum;++i) // ���춥������
     fscanf(graphlist,"%s",G.vexs[i]);
   for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
     for(j=0;j<G.vexnum;++j)
     {
       G.arcs[i][j].adj=0; // ͼ
       G.arcs[i][j].info=NULL; // û�������Ϣ
     }
   for(k=0;k<G.arcnum;++k)
   {
     fscanf(graphlist,"%s%s",va,vb);
     i=LocateVex(G,va);
     j=LocateVex(G,vb);
     G.arcs[i][j].adj=G.arcs[j][i].adj=1; // ����ͼ
   }
   fclose(graphlist);
   G.kind=AG;
   return OK;
 }

 Status CreateDG(MGraph &G)
 { // ��������(�ڽӾ���)��ʾ��,��������ͼG
   int i,j,k,l,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
   for(i=0;i<G.vexnum;++i) // ���춥������
     scanf("%s",G.vexs[i]);
   for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
     for(j=0;j<G.vexnum;++j)
     {
       G.arcs[i][j].adj=0; // ͼ
       G.arcs[i][j].info=NULL;
     }
   printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���): \n",G.arcnum);
   for(k=0;k<G.arcnum;++k)
   {
     scanf("%s%s%*c",va,vb);  // %*c�Ե��س���
     i=LocateVex(G,va);
     j=LocateVex(G,vb);
     G.arcs[i][j].adj=1; // ����ͼ
     if(IncInfo)
     {
       printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         info=(char*)malloc((l+1)*sizeof(char));
         strcpy(info,s);
         G.arcs[i][j].info=info; // ����
       }
     }
   }
   G.kind=DG;
   return OK;
 }

 Status CreateDN(MGraph &G)
 { // ��������(�ڽӾ���)��ʾ��,����������G
   int i,j,k,w,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
   for(i=0;i<G.vexnum;++i) // ���춥������
     scanf("%s",G.vexs[i]);
   for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
     for(j=0;j<G.vexnum;++j)
     {
       G.arcs[i][j].adj=INFINITY; // ��
       G.arcs[i][j].info=NULL;
     }
   printf("������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���): \n",G.arcnum);
   for(k=0;k<G.arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w);  // %*c�Ե��س���
     i=LocateVex(G,va);
     j=LocateVex(G,vb);
     G.arcs[i][j].adj=w; // ������
     if(IncInfo)
     {
       printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         info=(char*)malloc((w+1)*sizeof(char));
         strcpy(info,s);
         G.arcs[i][j].info=info; // ����
       }
     }
   }
   G.kind=DN;
   return OK;
 }

 Status CreateAG(MGraph &G)
 { // ��������(�ڽӾ���)��ʾ��,��������ͼG
   int i,j,k,l,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
   for(i=0;i<G.vexnum;++i) // ���춥������
     scanf("%s",G.vexs[i]);
   for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
     for(j=0;j<G.vexnum;++j)
     {
       G.arcs[i][j].adj=0; // ͼ
       G.arcs[i][j].info=NULL;
     }
   printf("������%d���ߵĶ���1 ����2(�Կո���Ϊ���): \n",G.arcnum);
   for(k=0;k<G.arcnum;++k)
   {
     scanf("%s%s%*c",va,vb); // %*c�Ե��س���
     i=LocateVex(G,va);
     j=LocateVex(G,vb);
     G.arcs[i][j].adj=G.arcs[j][i].adj=1; // ����ͼ
     if(IncInfo)
     {
       printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         info=(char*)malloc((l+1)*sizeof(char));
         strcpy(info,s);
         G.arcs[i][j].info=G.arcs[j][i].info=info; // ����
       }
     }
   }
   G.kind=AG;
   return OK;
 }

 Status CreateAN(MGraph &G)
 { // ��������(�ڽӾ���)��ʾ��,����������G���㷨7.2
   int i,j,k,w,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
   for(i=0;i<G.vexnum;++i) // ���춥������
     scanf("%s",G.vexs[i]);
   for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
     for(j=0;j<G.vexnum;++j)
     {
       G.arcs[i][j].adj=INFINITY; // ��
       G.arcs[i][j].info=NULL;
     }
   printf("������%d���ߵĶ���1 ����2 Ȩֵ(�Կո���Ϊ���): \n",G.arcnum);
   for(k=0;k<G.arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w); // %*c�Ե��س���
     i=LocateVex(G,va);
     j=LocateVex(G,vb);
     G.arcs[i][j].adj=G.arcs[j][i].adj=w; // ����
     if(IncInfo)
     {
       printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         info=(char*)malloc((w+1)*sizeof(char));
         strcpy(info,s);
         G.arcs[i][j].info=G.arcs[j][i].info=info; // ����
       }
     }
   }
   G.kind=AN;
   return OK;
 }

 Status CreateGraph(MGraph &G)
 { // ��������(�ڽӾ���)��ʾ��,����ͼG���㷨7.1
   printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3): ");
   scanf("%d",&G.kind);
   switch(G.kind)
   {
     case DG: return CreateDG(G); // ��������ͼ
     case DN: return CreateDN(G); // ����������
     case AG: return CreateAG(G); // ��������ͼ
     case AN: return CreateAN(G); // ����������
     default: return ERROR;
   }
 }

 void DestroyGraph(MGraph &G)
 { // ��ʼ����: ͼG���ڡ��������: ����ͼG
   int i,j;
   if(G.kind<2) // ����
     for(i=0;i<G.vexnum;i++) // �ͷŻ��������Ϣ(����еĻ�)
     {
       for(j=0;j<G.vexnum;j++)
         if(G.arcs[i][j].adj==1&&G.kind==0||G.arcs[i][j].adj!=INFINITY&&G.kind==1) // ����ͼ�Ļ�||�������Ļ�
           if(G.arcs[i][j].info) // �������Ϣ
           {
             free(G.arcs[i][j].info);
             G.arcs[i][j].info=NULL;
           }
     }
   else // ����
     for(i=0;i<G.vexnum;i++) // �ͷűߵ������Ϣ(����еĻ�)
       for(j=i+1;j<G.vexnum;j++)
         if(G.arcs[i][j].adj==1&&G.kind==2||G.arcs[i][j].adj!=INFINITY&&G.kind==3) // ����ͼ�ı�||�������ı�
           if(G.arcs[i][j].info) // �������Ϣ
           {
             free(G.arcs[i][j].info);
             G.arcs[i][j].info=G.arcs[j][i].info=NULL;
           }
   G.vexnum=0;
   G.arcnum=0;
 }

 VertexType& GetVex(MGraph G,int v)
 { // ��ʼ����: ͼG���ڣ�v��G��ĳ���������š��������: ����v��ֵ
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return G.vexs[v];
 }

 Status PutVex(MGraph &G,VertexType v,VertexType value)
 { // ��ʼ����: ͼG���ڣ�v��G��ĳ�����㡣�������: ��v����ֵvalue
   int k;
   k=LocateVex(G,v); // kΪ����v��ͼG�е����
   if(k<0)
     return ERROR;
   strcpy(G.vexs[k],value);
   return OK;
 }

 int FirstAdjVex(MGraph G,VertexType v)
 { // ��ʼ����: ͼG����,v��G��ĳ������
   // �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1
   int i,j=0,k;
   k=LocateVex(G,v); // kΪ����v��ͼG�е����
   if(G.kind==DN||G.kind==AN) // ��
     j=INFINITY;
   for(i=0;i<G.vexnum;i++)
     if(G.arcs[k][i].adj!=j)
       return i;
   return -1;
 }

 int NextAdjVex(MGraph G,VertexType v,VertexType w)
 { // ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ���
   // �������: ����v��(�����w��)��һ���ڽӶ�������,
   //           ��w��v�����һ���ڽӶ���,�򷵻�-1
   int i,j=0,k1,k2;
   k1=LocateVex(G,v); // k1Ϊ����v��ͼG�е����
   k2=LocateVex(G,w); // k2Ϊ����w��ͼG�е����
   if(G.kind==DN||G.kind==AN) // ��
     j=INFINITY;
   for(i=k2+1;i<G.vexnum;i++)
     if(G.arcs[k1][i].adj!=j)
       return i;
   return -1;
 }

 void InsertVex(MGraph &G,VertexType v)
 { // ��ʼ����: ͼG����,v��ͼG�ж�������ͬ����
   // �������: ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)
   int i;
   strcpy(G.vexs[G.vexnum],v); // �����¶�������
   for(i=0;i<=G.vexnum;i++)
   {
     if(G.kind%2) // ��
     {
       G.arcs[G.vexnum][i].adj=INFINITY; // ��ʼ�������ڽӾ����ֵ(�ޱ߻�)
       G.arcs[i][G.vexnum].adj=INFINITY; // ��ʼ�������ڽӾ����ֵ(�ޱ߻�)
     }
     else // ͼ
     {
       G.arcs[G.vexnum][i].adj=0; // ��ʼ�������ڽӾ����ֵ(�ޱ߻�)
       G.arcs[i][G.vexnum].adj=0; // ��ʼ�������ڽӾ����ֵ(�ޱ߻�)
     }
     G.arcs[G.vexnum][i].info=NULL; // ��ʼ�������Ϣָ��
     G.arcs[i][G.vexnum].info=NULL;
   }
   G.vexnum+=1; // ͼG�Ķ�������1
 }

 Status DeleteVex(MGraph &G,VertexType v)
 { // ��ʼ����: ͼG����,v��G��ĳ�����㡣�������: ɾ��G�ж���v������صĻ�
   int i,j,k;
   VRType m=0;
   k=LocateVex(G,v); // kΪ��ɾ������v�����
   if(k<0) // v����ͼG�Ķ���
     return ERROR;
   if(G.kind==DN||G.kind==AN) // ��
     m=INFINITY;
   for(j=0;j<G.vexnum;j++)
     if(G.arcs[j][k].adj!=m) // ���뻡���
     {
       if(G.arcs[j][k].info) // �������Ϣ
         free(G.arcs[j][k].info); // �ͷ������Ϣ
       G.arcnum--; // �޸Ļ���
     }
   if(G.kind==DG||G.kind==DN) // ����
     for(j=0;j<G.vexnum;j++)
       if(G.arcs[k][j].adj!=m) // �г���
       {
         if(G.arcs[k][j].info) // �������Ϣ
           free(G.arcs[k][j].info); // �ͷ������Ϣ
         G.arcnum--; // �޸Ļ���
       }
   for(j=k+1;j<G.vexnum;j++) // ���k����Ķ�����������ǰ��
     strcpy(G.vexs[j-1],G.vexs[j]);
   for(i=0;i<G.vexnum;i++)
     for(j=k+1;j<G.vexnum;j++)
       G.arcs[i][j-1]=G.arcs[i][j]; // �ƶ���ɾ������֮��ľ���Ԫ��
   for(i=0;i<G.vexnum;i++)
     for(j=k+1;j<G.vexnum;j++)
       G.arcs[j-1][i]=G.arcs[j][i]; // �ƶ���ɾ������֮�µľ���Ԫ��
   G.vexnum--; // ����ͼ�Ķ�����
   return OK;
 }

 Status InsertArc(MGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ͼG����,v��W��G����������
   // �������: ��G������<v,w>,��G�������,������Գƻ�<w,v>
   int i,l,v1,w1;
   char *info,s[MAX_INFO];
   v1=LocateVex(G,v); // β
   w1=LocateVex(G,w); // ͷ
   if(v1<0||w1<0)
     return ERROR;
   G.arcnum++; // ���������1
   if(G.kind%2) // ��
   {
     printf("������˻���ߵ�Ȩֵ: ");
     scanf("%d",&G.arcs[v1][w1].adj);
   }
   else // ͼ
     G.arcs[v1][w1].adj=1;
   printf("�Ƿ��иû���ߵ������Ϣ(0:�� 1:��): ");
   scanf("%d%*c",&i);
   if(i)
   {
     printf("������û���ߵ������Ϣ(<%d���ַ�)��",MAX_INFO);
     gets(s);
     l=strlen(s);
     if(l)
     {
       info=(char*)malloc((l+1)*sizeof(char));
       strcpy(info,s);
       G.arcs[v1][w1].info=info;
     }
   }
   if(G.kind>1) // ����
   {
     G.arcs[w1][v1].adj=G.arcs[v1][w1].adj;
     G.arcs[w1][v1].info=G.arcs[v1][w1].info; // ָ��ͬһ�������Ϣ
   }
   return OK;
 }

 Status DeleteArc(MGraph &G,VertexType v,VertexType w)
 { // ��ʼ����: ͼG����,v��w��G����������
   // �������: ��G��ɾ����<v,w>,��G�������,��ɾ���Գƻ�<w,v>
   int v1,w1;
   v1=LocateVex(G,v); // β
   w1=LocateVex(G,w); // ͷ
   if(v1<0||w1<0) // v1��w1��ֵ���Ϸ�
     return ERROR;
   if(G.kind%2==0) // ͼ
     G.arcs[v1][w1].adj=0;
   else // ��
     G.arcs[v1][w1].adj=INFINITY;
   if(G.arcs[v1][w1].info) // ��������Ϣ
   {
     free(G.arcs[v1][w1].info);
     G.arcs[v1][w1].info=NULL;
   }
   if(G.kind>=2) // ����,ɾ���Գƻ�<w,v>
   {
     G.arcs[w1][v1].adj=G.arcs[v1][w1].adj;
     G.arcs[w1][v1].info=NULL;
   }
   G.arcnum--;
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; // ���ʱ�־����(ȫ����)
 Status(*VisitFunc)(VertexType); // ��������
 void DFS(MGraph G,int v)
 { // �ӵ�v����������ݹ��������ȱ���ͼG���㷨7.5
   VertexType w1,v1;
   int w;
   visited[v]=TRUE; // ���÷��ʱ�־ΪTRUE(�ѷ���)
   VisitFunc(G.vexs[v]); // ���ʵ�v������
   strcpy(v1,GetVex(G,v));
   for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,GetVex(G,w))))
     if(!visited[w])
       DFS(G,w); // ��v����δ���ʵ����Ϊw���ڽӶ���ݹ����DFS
 }

 void DFSTraverse(MGraph G,Status(*Visit)(VertexType))
 { // ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.4
   // �������: �ӵ�1��������,������ȱ���ͼG,����ÿ��������ú���Visit
   //           һ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ��
   int v;
   VisitFunc=Visit; // ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ�����
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; // ���ʱ�־�����ʼ��(δ������)
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); // ����δ���ʵĶ������DFS
   printf("\n");
 }

 typedef VRType QElemType; // ��������
 #include"c3-2.h" // BFSTraverse()��
 #include"bo3-2.cpp" // BFSTraverse()��
 void BFSTraverse(MGraph G,Status(*Visit)(VertexType))
 { // ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.6
   // �������: �ӵ�1��������,��������ȷǵݹ����ͼG,����ÿ��������ú���
   //           Visitһ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ�ܡ�
   //           ʹ�ø�������Q�ͷ��ʱ�־����visited
   int v,u,w;
   VertexType w1,u1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; // �ó�ֵ
   InitQueue(Q); // �ÿյĸ�������Q
   for(v=0;v<G.vexnum;v++)
     if(!visited[v]) // v��δ����
     {
       visited[v]=TRUE; // ���÷��ʱ�־ΪTRUE(�ѷ���)
       Visit(G.vexs[v]);
       EnQueue(Q,v); // v�����
       while(!QueueEmpty(Q)) // ���в���
       {
         DeQueue(Q,u); // ��ͷԪ�س��Ӳ���Ϊu
         strcpy(u1,GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,GetVex(G,w))))
           if(!visited[w]) // wΪu����δ���ʵ��ڽӶ�������
           {
             visited[w]=TRUE;
             Visit(G.vexs[w]);
             EnQueue(Q,w);
           }
       }
     }
   printf("\n");
 }

 void Display(MGraph G)
 { // ����ڽӾ���G
   int i,j;
   char s[7],s1[3];
   switch(G.kind)
   {
     case DG: strcpy(s,"����ͼ\0");
              strcpy(s1,"��\0");
              break;
     case DN: strcpy(s,"������\0");
              strcpy(s1,"��\0");
              break;
     case AG: strcpy(s,"����ͼ\0");
              strcpy(s1,"��\0");
              break;
     case AN: strcpy(s,"������\0");
              strcpy(s1,"��\0");
   }
   printf("%d������%d��%s��%s\n",G.vexnum,G.arcnum,s1,s);
   for(i=0;i<G.vexnum;++i) // ���G.vexs
     printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
   printf("G.arcs.adj:\n"); // ���G.arcs.adj
   for(i=0;i<G.vexnum;i++)
   {
     for(j=0;j<G.vexnum;j++)
       printf("%11d",G.arcs[i][j].adj);
     printf("\n");
   }
   printf("G.arcs.info:\n"); // ���G.arcs.info
   printf("����1(��β) ����2(��ͷ) ��%s��Ϣ��\n",s1);
   if(G.kind<2) // ����
     for(i=0;i<G.vexnum;i++)
       for(j=0;j<G.vexnum;j++)
       {
         if(G.arcs[i][j].info)
           printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
       }
   else // ����
   {
     for(i=0;i<G.vexnum;i++)
       for(j=i+1;j<G.vexnum;j++)
         if(G.arcs[i][j].info)
           printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
   }
 }

