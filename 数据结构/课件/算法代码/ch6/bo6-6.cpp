 // bo6-6.cpp ����������������洢(�洢�ṹ��c6-7.h����)�Ļ�������(21��)
 Status InitBiTree(BiPTree &T)
 { // �������: ����ն�����T
   T=NULL;
   return OK;
 }

 void DestroyBiTree(BiPTree &T)
 { // ��ʼ����: ������T���ڡ��������: ���ٶ�����T
   if(T) // �ǿ���
   {
     if(T->lchild) // ������
       DestroyBiTree(T->lchild); // ������������
     if(T->rchild) // ���Һ���
       DestroyBiTree(T->rchild); // �����Һ�������
     free(T); // �ͷŸ����
     T=NULL; // ��ָ�븳0
   }
 }

 void Create(BiPTree &T) // CreateBiTree()����
 { // �������������������н���ֵ����Ϊ�ַ��ͻ����ͣ��������ж��壩��
   // �����ȱ˫��ָ������������ʾ�Ķ�����T������Nil��ʾ�գ��ӣ���
   TElemType ch;
 #ifdef CHAR
   scanf("%c",&ch);
 #endif
 #ifdef INT
   scanf("%d",&ch);
 #endif
   if(ch==Nil) // ��
     T=NULL;
   else
   {
     T=(BiPTree)malloc(sizeof(BiTPNode));
     if(!T)
       exit(OVERFLOW);
     T->data=ch; // ���ɸ����
     Create(T->lchild); // ����������
     Create(T->rchild); // ����������
   }
 }

 typedef BiPTree QElemType; // �����Ԫ��Ϊ��������ָ������
 #include"c3-2.h"
 #include"bo3-2.cpp"
 Status CreateBiTree(BiPTree &T)
 { // �������������������н���ֵ����Ϊ�ַ��ͻ����ͣ��������ж��壩��
   // �������������ʾ�Ķ�����T
   LinkQueue q;
   QElemType a;
   Create(T); // ���������(ȱ˫��ָ��)
   if(T) // �ǿ���
   {
     T->parent=NULL; // ������˫��Ϊ���գ�
     InitQueue(q); // ��ʼ������
     EnQueue(q,T); // ��ָ�����
     while(!QueueEmpty(q)) // �Ӳ���
     {
       DeQueue(q,a); // ����,����Ԫ�ظ���a
       if(a->lchild) // ������
       {
         a->lchild->parent=a; // �����ӵ�˫��ָ�븳ֵ
         EnQueue(q,a->lchild); // �������
       }
       if(a->rchild) // ���Һ���
       {
         a->rchild->parent=a; // ���Һ��ӵ�˫��ָ�븳ֵ
	 EnQueue(q,a->rchild); // �Һ������
       }
     }
   }
   return OK;
 }

 #define ClearBiTree DestroyBiTree

 Status BiTreeEmpty(BiPTree T)
 { // ��ʼ����: ������T���ڡ��������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE
   if(T)
     return FALSE;
   else
     return TRUE;
 }

 int BiTreeDepth(BiPTree T)
 { // ��ʼ����: ������T���ڡ��������: ����T�����
   int i,j;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);
   else
     i=0;
   if(T->rchild)
     j=BiTreeDepth(T->rchild);
   else
     j=0;
   return i>j?i+1:j+1;
 }

 TElemType Root(BiPTree T)
 { // ��ʼ����: ������T���ڡ��������: ����T�ĸ�
   if(T)
     return T->data;
   else
     return Nil;
 }

 TElemType Value(BiPTree p)
 { // ��ʼ����: ������T���ڣ�pָ��T��ĳ�����
   // �������: ����p��ָ����ֵ
   return p->data;
 }

 void Assign(BiPTree p,TElemType value)
 { // ��p��ָ��㸳ֵΪvalue
   p->data=value;
 }

 BiPTree Point(BiPTree T,TElemType e)
 { // ���ض�����T��ָ��Ԫ��ֵΪe�Ľ���ָ�롣��
   LinkQueue q;
   QElemType a;
   if(T) // �ǿ���
   {
     InitQueue(q); // ��ʼ������
     EnQueue(q,T); // ��������
     while(!QueueEmpty(q)) // �Ӳ���
     {
       DeQueue(q,a); // ����,����Ԫ�ظ���a
       if(a->data==e)
         return a;
       if(a->lchild) // ������
         EnQueue(q,a->lchild); // �������
       if(a->rchild) // ���Һ���
         EnQueue(q,a->rchild); // ����Һ���
     }
   }
   return NULL;
 }

 TElemType Parent(BiPTree T,TElemType e)
 { // ��ʼ����: ������T����,e��T��ĳ�����
   // �������: ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ�
   BiPTree a;
   if(T) // �ǿ���
   {
     a=Point(T,e); // a�ǽ��e��ָ��
     if(a&&a!=T) // T�д��ڽ��e��e�ǷǸ����
       return a->parent->data; // ����e��˫�׵�ֵ
   }
   return Nil; // ����������ؿ�
 }

 TElemType LeftChild(BiPTree T,TElemType e)
 { // ��ʼ����: ������T����,e��T��ĳ�����
   // �������: ����e�����ӡ���e������,�򷵻أ��գ�
   BiPTree a;
   if(T) // �ǿ���
   {
     a=Point(T,e); // a�ǽ��e��ָ��
     if(a&&a->lchild) // T�д��ڽ��e��e��������
       return a->lchild->data; // ����e�����ӵ�ֵ
   }
   return Nil; // ����������ؿ�
 }

 TElemType RightChild(BiPTree T,TElemType e)
 { // ��ʼ����: ������T����,e��T��ĳ�����
   // �������: ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ�
   BiPTree a;
   if(T) // �ǿ���
   {
     a=Point(T,e); // a�ǽ��e��ָ��
     if(a&&a->rchild) // T�д��ڽ��e��e�����Һ���
       return a->rchild->data; // ����e���Һ��ӵ�ֵ
   }
   return Nil; // ����������ؿ�
 }

 TElemType LeftSibling(BiPTree T,TElemType e)
 { // ��ʼ����: ������T����,e��T��ĳ�����
   // �������: ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ�
   BiPTree a;
   if(T) // �ǿ���
   {
     a=Point(T,e); // a�ǽ��e��ָ��
     if(a&&a!=T&&a->parent->lchild&&a->parent->lchild!=a) // T�д��ڽ��e��e�������ֵ�
       return a->parent->lchild->data; // ����e�����ֵܵ�ֵ
   }
   return Nil; // ����������ؿ�
 }

 TElemType RightSibling(BiPTree T,TElemType e)
 { // ��ʼ����: ������T����,e��T��ĳ�����
   // �������: ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ�
   BiPTree a;
   if(T) // �ǿ���
   {
     a=Point(T,e); // a�ǽ��e��ָ��
     if(a&&a!=T&&a->parent->rchild&&a->parent->rchild!=a) // T�д��ڽ��e��e�������ֵ�
       return a->parent->rchild->data; // ����e�����ֵܵ�ֵ
   }
   return Nil; // ����������ؿ�
 }

 Status InsertChild(BiPTree p,int LR,BiPTree c) // �β�T����
 { // ��ʼ����: ������T����,pָ��T��ĳ�����,LRΪ0��1,�ǿն�����c��T
   //           ���ཻ��������Ϊ��
   // �������: ����LRΪ0��1,����cΪT��p��ָ���������������p��ָ���
   //           ��ԭ��������������Ϊc��������
   if(p) // p����
   {
     if(LR==0)
     {
       c->rchild=p->lchild;
       if(c->rchild) // c���Һ���(pԭ������)
         c->rchild->parent=c;
       p->lchild=c;
       c->parent=p;
     }
     else // LR==1
     {
       c->rchild=p->rchild;
       if(c->rchild) // c���Һ���(pԭ���Һ���)
         c->rchild->parent=c;
       p->rchild=c;
       c->parent=p;
     }
     return OK;
   }
   return ERROR; // p��
 }

 Status DeleteChild(BiPTree p,int LR) // �β�T����
 { // ��ʼ����: ������T����,pָ��T��ĳ�����,LRΪ0��1
   // �������: ����LRΪ0��1,ɾ��T��p��ָ�������������
   if(p) // p����
   {
     if(LR==0) // ɾ��������
       ClearBiTree(p->lchild);
     else // ɾ��������
       ClearBiTree(p->rchild);
     return OK;
   }
   return ERROR; // p��
 }

 void PreOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { // ����ݹ����������T
   if(T)
   {
     Visit(T); // �ȷ��ʸ����
     PreOrderTraverse(T->lchild,Visit); // ���������������
     PreOrderTraverse(T->rchild,Visit); // ����������������
   }
 }

 void InOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { // ����ݹ����������T
   if(T)
   {
     InOrderTraverse(T->lchild,Visit); // �������������
     Visit(T); // �ٷ��ʸ����
     InOrderTraverse(T->rchild,Visit); // ����������������
   }
 }

 void PostOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { // ����ݹ����������T
   if(T)
   {
     PostOrderTraverse(T->lchild,Visit); // �������������
     PostOrderTraverse(T->rchild,Visit); // �������������
     Visit(T); // �����ʸ����
   }
 }

 void LevelOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { // �������������T(���ö���)
   LinkQueue q;
   QElemType a;
   if(T)
   {
     InitQueue(q);
     EnQueue(q,T);
     while(!QueueEmpty(q))
     {
       DeQueue(q,a);
       Visit(a);
       if(a->lchild!=NULL)
         EnQueue(q,a->lchild);
       if(a->rchild!=NULL)
         EnQueue(q,a->rchild);
     }
   }
 }
