 // bo6-5.cpp ���Ķ�������(���ӣ��ֵ�)�洢(�洢�ṹ��c6-5.h����)�Ļ�������(17��)
 Status InitTree(CSTree &T)
 { // �������: �������T
   T=NULL;
   return OK;
 }

 void DestroyTree(CSTree &T)
 { // ��ʼ����: ��T���ڡ��������: ������T
   if(T)
   {
     if(T->firstchild) // T�г���
       DestroyTree(T->firstchild); // ����T�ĳ���Ϊ����������
     if(T->nextsibling) // T����һ���ֵ�
       DestroyTree(T->nextsibling); // ����T����һ���ֵ�Ϊ����������
     free(T); // �ͷŸ����
     T=NULL;
   }
 }

 typedef CSTree QElemType; // �������Ԫ������
 #include"c3-2.h" // ����LinkQueue����
 #include"bo3-2.cpp" // LinkQueue���͵Ļ�������
 Status CreateTree(CSTree &T)
 { // ������T
   char c[20]; // ��ʱ��ź��ӽ��(�費����20��)��ֵ
   CSTree p,p1;
   LinkQueue q;
   int i,l;
   InitQueue(q);
   printf("����������(�ַ���,�ո�Ϊ��): ");
   scanf("%c%*c",&c[0]);
   if(c[0]!=Nil) // �ǿ���
   {
     T=(CSTree)malloc(sizeof(CSNode)); // ���������
     T->data=c[0];
     T->nextsibling=NULL;
     EnQueue(q,T); // ��Ӹ�����ָ��
     while(!QueueEmpty(q)) // �Ӳ���
     {
       DeQueue(q,p); // ����һ������ָ��
       printf("�밴����˳��������%c�����к���: ",p->data);
       gets(c);
       l=strlen(c);
       if(l>0) // �к���
       {
         p1=p->firstchild=(CSTree)malloc(sizeof(CSNode)); // �������ӽ��
         p1->data=c[0];
         for(i=1;i<l;i++)
         {
           p1->nextsibling=(CSTree)malloc(sizeof(CSNode)); // ������һ���ֵܽ��
           EnQueue(q,p1); // �����һ�����
           p1=p1->nextsibling;
           p1->data=c[i];
         }
         p1->nextsibling=NULL;
         EnQueue(q,p1); // ������һ�����
       }
       else
         p->firstchild=NULL;
     }
   }
   else
     T=NULL;
   return OK;
 }

 #define ClearTree DestroyTree // ���߲�����ͬ

 Status TreeEmpty(CSTree T)
 { // ��ʼ����: ��T���ڡ��������: ��TΪ����,�򷵻�TURE,���򷵻�FALSE
   if(T) // T����
     return FALSE;
   else
     return TRUE;
 }

 int TreeDepth(CSTree T)
 { // ��ʼ����: ��T���ڡ��������: ����T�����
   CSTree p;
   int depth,max=0;
   if(!T) // ����
     return 0;
   if(!T->firstchild) // ���޳���
     return 1;
   for(p=T->firstchild;p;p=p->nextsibling)
   {
     depth=TreeDepth(p);
     if(depth>max)
       max=depth;
   }
   return max+1;
 }

 TElemType Value(CSTree p)
 { // ����p��ָ����ֵ
   return p->data;
 }

 TElemType Root(CSTree T)
 { // ��ʼ����: ��T���ڡ��������: ����T�ĸ�
   if(T)
     return Value(T);
   else
     return Nil;
 }

 CSTree Point(CSTree T,TElemType s)
 { // ���ض�������(���ӣ��ֵ�)��T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣���
   LinkQueue q;
   QElemType a;
   if(T) // �ǿ���
   {
     InitQueue(q); // ��ʼ������
     EnQueue(q,T); // ��������
     while(!QueueEmpty(q)) // �Ӳ���
     {
       DeQueue(q,a); // ����,����Ԫ�ظ���a
       if(a->data==s)
	 return a;
       if(a->firstchild) // �г���
         EnQueue(q,a->firstchild); // ��ӳ���
       if(a->nextsibling) // ����һ���ֵ�
         EnQueue(q,a->nextsibling); // �����һ���ֵ�
     }
   }
   return NULL;
 }

 Status Assign(CSTree &T,TElemType cur_e,TElemType value)
 { // ��ʼ����: ��T����,cur_e����T�н���ֵ���������: ��cur_eΪvalue
   CSTree p;
   if(T) // �ǿ���
   {
     p=Point(T,cur_e); // pΪcur_e��ָ��
     if(p) // �ҵ�cur_e
     {
       p->data=value; // ����ֵ
       return OK;
     }
   }
   return Nil; // ���ջ�û�ҵ�
 }

 TElemType Parent(CSTree T,TElemType cur_e)
 { // ��ʼ����: ��T����,cur_e��T��ĳ�����
   // �������: ��cur_e��T�ķǸ����,�򷵻�����˫��,������ֵΪ���գ�
   CSTree p,t;
   LinkQueue q;
   InitQueue(q);
   if(T) // ���ǿ�
   {
     if(Value(T)==cur_e) // �����ֵΪcur_e
       return Nil;
     EnQueue(q,T); // ��������
     while(!QueueEmpty(q))
     {
       DeQueue(q,p);
       if(p->firstchild) // p�г���
       {
         if(p->firstchild->data==cur_e) // ����Ϊcur_e
           return Value(p); // ����˫��
         t=p; // ˫��ָ�븳��t
         p=p->firstchild; // pָ����
         EnQueue(q,p); // ��ӳ���
         while(p->nextsibling) // ����һ���ֵ�
         {
           p=p->nextsibling; // pָ����һ���ֵ�
	   if(Value(p)==cur_e) // ��һ���ֵ�Ϊcur_e
             return Value(t); // ����˫��
           EnQueue(q,p); // �����һ���ֵ�
         }
       }
     }
   }
   return Nil; // ���ջ�û�ҵ�cur_e
 }

 TElemType LeftChild(CSTree T,TElemType cur_e)
 { // ��ʼ����: ��T����,cur_e��T��ĳ�����
   // �������: ��cur_e��T�ķ�Ҷ�ӽ��,�򷵻�����������,���򷵻أ��գ�
   CSTree f;
   f=Point(T,cur_e); // fָ����cur_e
   if(f&&f->firstchild) // �ҵ����cur_e�ҽ��cur_e�г���
     return f->firstchild->data;
   else
     return Nil;
 }

 TElemType RightSibling(CSTree T,TElemType cur_e)
 { // ��ʼ����: ��T����,cur_e��T��ĳ�����
   // �������: ��cur_e�����ֵ�,�򷵻��������ֵ�,���򷵻أ��գ�
   CSTree f;
   f=Point(T,cur_e); // fָ����cur_e
   if(f&&f->nextsibling) // �ҵ����cur_e�ҽ��cur_e�����ֵ�
     return f->nextsibling->data;
   else
     return Nil; // ����
 }

 Status InsertChild(CSTree &T,CSTree p,int i,CSTree c)
 { // ��ʼ����: ��T����,pָ��T��ĳ�����,1��i��p��ָ���Ķ�+1,�ǿ���c��T���ཻ
   // �������: ����cΪT��p���ĵ�i������
   // ��Ϊp��ָ���ĵ�ַ����ı䣬��p��������������
   int j;
   if(T) // T����
   {
     if(i==1) // ����cΪp�ĳ���
     {
       c->nextsibling=p->firstchild; // p��ԭ��������c����һ���ֵ�(c�����ֵ�)
       p->firstchild=c;
     }
     else // �Ҳ����
     {
       p=p->firstchild; // ָ��p�ĳ���
       j=2;
       while(p&&j<i)
       {
         p=p->nextsibling;
         j++;
       }
       if(j==i) // �ҵ�����λ��
       {
         c->nextsibling=p->nextsibling;
         p->nextsibling=c;
       }
       else // pԭ�к�����С��i-1
         return ERROR;
     }
     return OK;
   }
   else // T��
     return ERROR;
 }

 Status DeleteChild(CSTree &T,CSTree p,int i)
 { // ��ʼ����: ��T����,pָ��T��ĳ�����,1��i��p��ָ���Ķ�
   // �������: ɾ��T��p��ָ���ĵ�i������
   // ��Ϊp��ָ���ĵ�ַ����ı䣬��p��������������
   CSTree b;
   int j;
   if(T) // T����
   {
     if(i==1) // ɾ������
     {
       b=p->firstchild;
       p->firstchild=b->nextsibling; // p��ԭ�������ǳ���
       b->nextsibling=NULL;
       DestroyTree(b);
     }
     else // ɾ���ǳ���
     {
       p=p->firstchild; // pָ����
       j=2;
       while(p&&j<i)
       {
         p=p->nextsibling;
         j++;
       }
       if(j==i) // �ҵ���i������
       {
         b=p->nextsibling;
         p->nextsibling=b->nextsibling;
         b->nextsibling=NULL;
         DestroyTree(b);
       }
       else // pԭ�к�����С��i
         return ERROR;
     }
     return OK;
   }
   else
     return ERROR;
 }

 void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { // �ȸ��������ӣ��ֵܶ�������ṹ����T
   if(T)
   {
     Visit(Value(T)); // �ȷ��ʸ����
     PreOrderTraverse(T->firstchild,Visit); // ���ȸ�������������
     PreOrderTraverse(T->nextsibling,Visit); // ����ȸ�������һ���ֵ�����
   }
 }

 void PostOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { // ����������ӣ��ֵܶ�������ṹ����T
   CSTree p;
   if(T)
   {
     if(T->firstchild) // �г���
     {
       PostOrderTraverse(T->firstchild,Visit); // ���������������
       p=T->firstchild->nextsibling; // pָ���ӵ���һ���ֵ�
       while(p)
       {
         PostOrderTraverse(p,Visit); // ���������һ���ֵ�����
         p=p->nextsibling; // pָ������һ���ֵ�
       }
     }
     Visit(Value(T)); // �����ʸ����
   }
 }

 void LevelOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { // ����������ӣ��ֵܶ�������ṹ����T
   CSTree p;
   LinkQueue q;
   InitQueue(q);
   if(T)
   {
     Visit(Value(T)); // �ȷ��ʸ����
     EnQueue(q,T); // ��Ӹ�����ָ��
     while(!QueueEmpty(q)) // �Ӳ���
     {
       DeQueue(q,p); // ����һ������ָ��
       if(p->firstchild) // �г���
       {
         p=p->firstchild;
         Visit(Value(p)); // ���ʳ��ӽ��
         EnQueue(q,p); // ��ӳ��ӽ���ָ��
         while(p->nextsibling) // ����һ���ֵ�
         {
           p=p->nextsibling;
           Visit(Value(p)); // ������һ���ֵ�
           EnQueue(q,p); // ����ֵܽ���ָ��
         }
       }
     }
   }
 }
