 // algo2-9.cpp ��������bo2-32.cpp�еĻ�������ʵ���㷨2.17�Ĺ���
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.cpp"
 #include"bo2-32.cpp"

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 int difference(SLinkList space) // �Ľ��㷨2.17(�������û�������ʵ��)
 { // �������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ����(A-B)��(B-A)
   // �ľ�̬������������ͷָ�롣���豸�ÿռ��㹻��space[0].curΪ���ÿռ��ͷָ��
   int m,n,i,j,k,S;
   ElemType b,c;
   InitSpace(space); // ��ʼ�����ÿռ�
   S=InitList(space); // ��������S��ͷ���
   printf("�����뼯��A��B��Ԫ�ظ���m,n:");
   scanf("%d,%d%*c",&m,&n); // %*c�Ե��س���
   printf("�����뼯��A��Ԫ�أ���%d����:",m);
   for(j=1;j<=m;j++) // ��������A������
   {
     scanf("%c",&b); // ����A��Ԫ��ֵ
     ListInsert(space,S,j,b); // ���뵽��β
   }
   scanf("%*c"); // �Ե��س���
   printf("�����뼯��B��Ԫ�أ���%d����:",n);
   for(j=1;j<=n;j++)
   { // ��������B��Ԫ��,�����ڵ�ǰ����,�����,����ɾ��
     scanf("%c",&b);
     k=LocateElem(space,S,b); // kΪb��λ��
     if(k) // b�ڵ�ǰ����
     {
       PriorElem(space,S,b,c); // b��ǰ��Ϊc
       i=LocateElem(space,S,c); // iΪc��λ��
       space[i].cur=space[k].cur; // ��k��ָ�븳��i��ָ��
       Free(space,k); // ���±�Ϊk�Ŀ��н����յ���������
     }
     else
       ListInsert(space,S,ListLength(space,S)+1,b); // �ڱ�β����b
   }
   return S;
 }

 void main()
 {
   int k;
   SLinkList s;
   k=difference(s);
   ListTraverse(s,k,visit);
 }
