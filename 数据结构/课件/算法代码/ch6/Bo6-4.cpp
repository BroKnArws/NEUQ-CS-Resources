 // bo6-4.cpp ����˫�ױ�洢(�洢�ṹ��c6-4.h����)�Ļ�������(14��)
 Status InitTree(PTree &T)
 { // �������: �������T
   T.n=0;
   return OK;
 }

 void DestroyTree()
 { // ����PTree�Ƕ�������,�޷�����
 }

 typedef struct
 {
   int num;
   TElemType name;
 }QElemType; // �������Ԫ������
 #include"c3-2.h" // ����LinkQueue����
 #include"bo3-2.cpp" // LinkQueue���͵Ļ�������
 Status CreateTree(PTree &T)
 { // �������: ������T
   LinkQueue q;
   QElemType p,qq;
   int i=1,j,l;
   char c[MAX_TREE_SIZE]; // ��ʱ��ź��ӽ������
   InitQueue(q); // ��ʼ������
   printf("����������(�ַ���,�ո�Ϊ��): ");
   scanf("%c%*c",&T.nodes[0].data); // ��������Ϊ0,%*c�Ե��س���
   if(T.nodes[0].data!=Nil) // �ǿ���
   {
     T.nodes[0].parent=-1; // �������˫��
     qq.name=T.nodes[0].data;
     qq.num=0;
     EnQueue(q,qq); // ��Ӵ˽��
     while(i<MAX_TREE_SIZE&&!QueueEmpty(q)) // ����δ���ҶӲ���
     {
       DeQueue(q,qq); // ����һ�����
       printf("�밴����˳��������%c�����к���: ",qq.name);
       gets(c);
       l=strlen(c);
       for(j=0;j<l;j++)
       {
         T.nodes[i].data=c[j];
         T.nodes[i].parent=qq.num;
         p.name=c[j];
         p.num=i;
         EnQueue(q,p); // ��Ӵ˽��
         i++;
       }
     }
     if(i>MAX_TREE_SIZE)
     {
       printf("�����������������\n");
       exit(OVERFLOW);
     }
     T.n=i;
   }
   else
     T.n=0;
   return OK;
 }

 #define ClearTree InitTree // ���߲�����ͬ

 Status TreeEmpty(PTree T)
 { // ��ʼ����: ��T���ڡ��������: ��TΪ����,�򷵻�TRUE,���򷵻�FALSE
   if(T.n)
     return FALSE;
   else
     return TRUE;
 }

 int TreeDepth(PTree T)
 { // ��ʼ����: ��T���ڡ��������: ����T�����
   int k,m,def,max=0;
   for(k=0;k<T.n;++k)
   {
     def=1; // ��ʼ�����ʵ�����
     m=T.nodes[k].parent;
     while(m!=-1)
     {
       m=T.nodes[m].parent;
       def++;
     }
     if(max<def)
       max=def;
   }
   return max; // ������
 }

 TElemType Root(PTree T)
 { // ��ʼ����: ��T���ڡ��������: ����T�ĸ�
   int i;
   for(i=0;i<T.n;i++)
     if(T.nodes[i].parent<0)
       return T.nodes[i].data;
   return Nil;
 }

 TElemType Value(PTree T,int i)
 { // ��ʼ����: ��T����,i����T�н�����š��������: ���ص�i������ֵ
   if(i<T.n)
     return T.nodes[i].data;
   else
     return Nil;
 }

 Status Assign(PTree &T,TElemType cur_e,TElemType value)
 { // ��ʼ����: ��T����,cur_e����T�н���ֵ���������: ��cur_eΪvalue
   int j;
   for(j=0;j<T.n;j++)
   {
     if(T.nodes[j].data==cur_e)
     {
       T.nodes[j].data=value;
       return OK;
     }
   }
   return ERROR;
 }

 TElemType Parent(PTree T,TElemType cur_e)
 { // ��ʼ����: ��T����,cur_e��T��ĳ�����
   // �������: ��cur_e��T�ķǸ����,�򷵻�����˫��,������ֵΪ���գ�
   int j;
   for(j=1;j<T.n;j++) // ��������Ϊ0
     if(T.nodes[j].data==cur_e)
       return T.nodes[T.nodes[j].parent].data;
   return Nil;
 }

 TElemType LeftChild(PTree T,TElemType cur_e)
 { // ��ʼ����: ��T����,cur_e��T��ĳ�����
   // �������: ��cur_e��T�ķ�Ҷ�ӽ��,�򷵻�����������,���򷵻أ��գ�
   int i,j;
   for(i=0;i<T.n;i++)
     if(T.nodes[i].data==cur_e) // �ҵ�cur_e,�����Ϊi
       break;
   for(j=i+1;j<T.n;j++) // �������Ĺ��캯��,���ӵ���ţ���˫�׵����
     if(T.nodes[j].parent==i) // �������Ĺ��캯��,������(����)����ţ��������ӵ����
       return T.nodes[j].data;
   return Nil;
 }

 TElemType RightSibling(PTree T,TElemType cur_e)
 { // ��ʼ����: ��T����,cur_e��T��ĳ�����
   // �������: ��cur_e����(��һ��)�ֵ�,�򷵻��������ֵ�,���򷵻أ��գ�
   int i;
   for(i=0;i<T.n;i++)
     if(T.nodes[i].data==cur_e) // �ҵ�cur_e,�����Ϊi
       break;
   if(T.nodes[i+1].parent==T.nodes[i].parent)
   // �������Ĺ��캯��,��cur_e�����ֵܵĻ������ֵܽ������
     return T.nodes[i+1].data;
   return Nil;
 }

 Status Print(PTree T)
 { // �����T����
   int i;
   printf("������=%d\n",T.n);
   printf(" ��� ˫��\n");
   for(i=0;i<T.n;i++)
   {
     printf("    %c",Value(T,i)); // ���
     if(T.nodes[i].parent>=0) // ��˫��
       printf("    %c",Value(T,T.nodes[i].parent)); // ˫��
     printf("\n");
   }
   return OK;
 }

 Status InsertChild(PTree &T,TElemType p,int i,PTree c)
 { // ��ʼ����: ��T����,p��T��ĳ�����,1��i��p��ָ���Ķ�+1,�ǿ���c��T���ཻ
   // �������: ����cΪT��p���ĵ�i������
   int j,k,l,f=1,n=0; // �轻����־f�ĳ�ֵΪ1,p�ĺ�����n�ĳ�ֵΪ0
   PTNode t;
   if(!TreeEmpty(T)) // T����
   {
     for(j=0;j<T.n;j++) // ��T����p�����
       if(T.nodes[j].data==p) // p�����Ϊj
         break;
     l=j+1; // ���c��p�ĵ�1������,�����j+1��
     if(i>1) // c����p�ĵ�1������
     {
       for(k=j+1;k<T.n;k++) // ��j+1��ʼ��p��ǰi-1������
         if(T.nodes[k].parent==j) // ��ǰ�����p�ĺ���
         {
           n++; // ��������1
           if(n==i-1) // �ҵ�p�ĵ�i-1������,�����Ϊk1
             break;
         }
       l=k+1; // c����k+1��
     } // p�����Ϊj,c����l��
     if(l<T.n) // �����l�������
       for(k=T.n-1;k>=l;k--) // ���ν����l�Ժ�Ľ�������c.n��λ��
       {
         T.nodes[k+c.n]=T.nodes[k];
         if(T.nodes[k].parent>=l)
           T.nodes[k+c.n].parent+=c.n;
       }
     for(k=0;k<c.n;k++)
     {
       T.nodes[l+k].data=c.nodes[k].data; // ���ν���c�����н����ڴ˴�
       T.nodes[l+k].parent=c.nodes[k].parent+l;
     }
     T.nodes[l].parent=j; // ��c�ĸ�����˫��Ϊp
     T.n+=c.n; // ��T�Ľ������c.n��
     while(f)
     { // �Ӳ����֮��,������԰���������
       f=0; // ������־��0
       for(j=l;j<T.n-1;j++)
         if(T.nodes[j].parent>T.nodes[j+1].parent)
         { // ������j��˫�����ڽ��j+1��˫��֮��(��û�а���������),���������
           t=T.nodes[j];
           T.nodes[j]=T.nodes[j+1];
           T.nodes[j+1]=t;
           f=1; // ������־��1
           for(k=j;k<T.n;k++) // �ı�˫�����
             if(T.nodes[k].parent==j)
               T.nodes[k].parent++; // ˫����Ÿ�Ϊj+1
             else if(T.nodes[k].parent==j+1)
               T.nodes[k].parent--; // ˫����Ÿ�Ϊj
         }
     }
     return OK;
   }
   else // ��T������
     return ERROR;
 }

 Status deleted[MAX_TREE_SIZE+1]; // ɾ����־����(ȫ����)
 void DeleteChild(PTree &T,TElemType p,int i)
 { // ��ʼ����: ��T����,p��T��ĳ�����,1��i��p��ָ���Ķ�
   // �������: ɾ��T�н��p�ĵ�i������
   int j,k,n=0;
   LinkQueue q;
   QElemType pq,qq;
   for(j=0;j<=T.n;j++)
     deleted[j]=0; // �ó�ֵΪ0(��ɾ�����)
   pq.name='a'; // �˳�Ա����
   InitQueue(q); // ��ʼ������
   for(j=0;j<T.n;j++)
     if(T.nodes[j].data==p)
       break; // jΪ���p�����
   for(k=j+1;k<T.n;k++)
   {
     if(T.nodes[k].parent==j)
       n++;
     if(n==i)
       break; // kΪp�ĵ�i�������������
   }
   if(k<T.n) // p�ĵ�i������������
   {
     n=0;
     pq.num=k;
     deleted[k]=1; // ��ɾ�����
     n++;
     EnQueue(q,pq);
     while(!QueueEmpty(q))
     {
       DeQueue(q,qq);
       for(j=qq.num+1;j<T.n;j++)
         if(T.nodes[j].parent==qq.num)
         {
           pq.num=j;
           deleted[j]=1; // ��ɾ�����
           n++;
           EnQueue(q,pq);
         }
     }
     for(j=0;j<T.n;j++)
       if(deleted[j]==1)
       {
         for(k=j+1;k<=T.n;k++)
         {
           deleted[k-1]=deleted[k];
           T.nodes[k-1]=T.nodes[k];
           if(T.nodes[k].parent>j)
             T.nodes[k-1].parent--;
         }
         j--;
       }
     T.n-=n; // nΪ��ɾ�������
   }
 }

 void TraverseTree(PTree T,void(*Visit)(TElemType))
 { // ��ʼ����:������T����,Visit�ǶԽ�������Ӧ�ú���
   // �������:���������T,��ÿ�������ú���Visitһ���ҽ�һ��
   int i;
   for(i=0;i<T.n;i++)
     Visit(T.nodes[i].data);
   printf("\n");
 }
