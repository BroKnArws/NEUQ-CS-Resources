 // algo2-8.cpp ʵ���㷨2.17�ĳ���
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.cpp"
 #include"bo2-32.cpp"

 void difference(SLinkList space,int &S) // �㷨2.17
 { // �������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ����(A-B)��(B-A)
   // �ľ�̬����SΪ��ͷָ�롣���豸�ÿռ��㹻��space[0].curΪ���ÿռ��ͷָ��
   int r,p,m,n,i,j,k;
   ElemType b;
   InitSpace(space); // ��ʼ�����ÿռ�
   S=Malloc(space); // ����S��ͷ���
   r=S; // rָ��S�ĵ�ǰ�����
   printf("�����뼯��A��B��Ԫ�ظ���m,n:");
   scanf("%d,%d%*c",&m,&n); // %*c�Ե��س���
   printf("�����뼯��A��Ԫ�أ���%d����:",m);
   for(j=1;j<=m;j++) // ��������A������
   {
     i=Malloc(space); // ������
     scanf("%c",&space[i].data); // ����A��Ԫ��ֵ
     space[r].cur=i; // ���뵽��β
     r=i;
   }
   scanf("%*c"); // %*c�Ե��س���
   space[r].cur=0; // β����ָ��Ϊ��
   printf("�����뼯��B��Ԫ�أ���%d����:",n);
   for(j=1;j<=n;j++)
   { // ��������B��Ԫ��,�����ڵ�ǰ����,�����,����ɾ��
     scanf("%c",&b);
     p=S;
     k=space[S].cur; // kָ�򼯺�A�еĵ�һ�����
     while(k!=space[r].cur&&space[k].data!=b)
     { // �ڵ�ǰ���в���
       p=k;
       k=space[k].cur;
     }
     if(k==space[r].cur)
     { // ��ǰ���в����ڸ�Ԫ�أ�������r��ָ���֮����r��λ�ò���
       i=Malloc(space);
       space[i].data=b;
       space[i].cur=space[r].cur;
       space[r].cur=i;
     }
     else // ��Ԫ�����ڱ��У�ɾ��֮
     {
       space[p].cur=space[k].cur;
       Free(space,k);
       if(r==k)
         r=p; // ��ɾ������βԪ�أ������޸�βָ��
     }
   }
 }

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 void main()
 {
   int k;
   SLinkList s;
   difference(s,k);
   ListTraverse(s,k,visit);
 }
