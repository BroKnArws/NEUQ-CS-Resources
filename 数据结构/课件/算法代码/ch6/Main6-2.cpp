 // main6-2.cpp ����bo6-2.cpp��������,������������ѡ����������(��һ�ַ���)
 #define CHAR // �ַ���
 // #define INT // ���ͣ�����ѡһ��
 #include"c1.h"
 #ifdef CHAR
   typedef char TElemType;
   TElemType Nil=' '; // �ַ����Կո��Ϊ��
 #endif
 #ifdef INT
   typedef int TElemType;
   TElemType Nil=0; // ������0Ϊ��
 #endif
 #include"c6-2.h"
 #include"bo6-2.cpp"

 Status visitT(TElemType e)
 {
 #ifdef CHAR
   printf("%c ",e);
 #endif
 #ifdef INT
   printf("%d ",e);
 #endif
   return OK;
 }

 void main()
 {
   int i;
   BiTree T,p,c;
   TElemType e1,e2;
   InitBiTree(T);
   printf("����ն�������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("�������ĸ�Ϊ: %c\n",e1);
 #endif
 #ifdef INT
     printf("�������ĸ�Ϊ: %d\n",e1);
 #endif
   else
     printf("���գ��޸�\n");
 #ifdef CHAR
   printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #endif
 #ifdef INT
   printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   CreateBiTree(T);
   printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("�������ĸ�Ϊ: %c\n",e1);
 #endif
 #ifdef INT
     printf("�������ĸ�Ϊ: %d\n",e1);
 #endif
   else
     printf("���գ��޸�\n");
   printf("����ݹ����������:\n");
   InOrderTraverse(T,visitT);
   printf("\n����ǵݹ����������:\n");
   InOrderTraverse1(T,visitT);
   printf("����ǵݹ����������(��һ�ַ���):\n");
   InOrderTraverse2(T,visitT);
   printf("����ݹ����������:\n");
   PostOrderTraverse(T,visitT);
   printf("\n�������������:\n");
   LevelOrderTraverse(T,visitT);
   printf("������һ������ֵ: ");
 #ifdef CHAR
   scanf("%*c%c",&e1);
 #endif
 #ifdef INT
   scanf("%d",&e1);
 #endif
   p=Point(T,e1); // pΪe1��ָ��
 #ifdef CHAR
   printf("����ֵΪ%c\n",Value(p));
 #endif
 #ifdef INT
   printf("����ֵΪ%d\n",Value(p));
 #endif
   printf("���ı�˽���ֵ����������ֵ: ");
 #ifdef CHAR
   scanf("%*c%c%*c",&e2);
 #endif
 #ifdef INT
   scanf("%d",&e2);
 #endif
   Assign(p,e2);
   printf("�������������:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c��˫����%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d��˫����%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû��˫��\n",e2);
 #endif
 #ifdef INT
     printf("%dû��˫��\n",e2);
 #endif
   e1=LeftChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c��������%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d��������%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû������\n",e2);
 #endif
 #ifdef INT
     printf("%dû������\n",e2);
 #endif
   e1=RightChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c���Һ�����%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d���Һ�����%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû���Һ���\n",e2);
 #endif
 #ifdef INT
     printf("%dû���Һ���\n",e2);
 #endif
   e1=LeftSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c�����ֵ���%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d�����ֵ���%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû�����ֵ�\n",e2);
 #endif
 #ifdef INT
     printf("%dû�����ֵ�\n",e2);
 #endif
   e1=RightSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c�����ֵ���%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d�����ֵ���%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%cû�����ֵ�\n",e2);
 #endif
 #ifdef INT
     printf("%dû�����ֵ�\n",e2);
 #endif
   InitBiTree(c);
   printf("����һ��������Ϊ�յĶ�����c:\n");
 #ifdef CHAR
   printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #endif
 #ifdef INT
   printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   CreateBiTree(c);
   printf("����ݹ����������c:\n");
   PreOrderTraverse(c,visitT);
   printf("\n��c�嵽��T��,��������T����c��˫�׽�� cΪ��(0)����(1)����: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1); // p��T����c��˫�׽��ָ��
   InsertChild(p,i,c);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\nɾ������,�������ɾ��������˫�׽��  ��(0)����(1)����: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1);
   DeleteChild(p,i);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");
   DestroyBiTree(T);
 }