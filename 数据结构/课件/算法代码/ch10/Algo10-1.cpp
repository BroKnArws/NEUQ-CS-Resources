 // algo10-1.cpp ����bo10-1.cpp�ĳ���
 #include"c1.h"
 typedef int InfoType; // �������������������
 #include"c9.h"
 #include"c10-1.h"
 #include"bo10-1.cpp"
 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l1,l2,l3;
   int i;
   for(i=0;i<N;i++) // ��l1.r��ֵ
     l1.r[i+1]=d[i];
   l1.length=N;
   l2=l3=l1; // ����˳���l2��l3��l1��ͬ
   printf("����ǰ:\n");
   print(l1);
   InsertSort(l1);
   printf("ֱ�Ӳ��������:\n");
   print(l1);
   BInsertSort(l2);
   printf("�۰���������:\n");
   print(l2);
   P2_InsertSort(l3);
   printf("2_·���������:\n");
   print(l3);
 }
