 // algo10-3.cpp ϣ������
 #include<stdio.h>
 typedef int InfoType; // �������������������
 #include"c9.h"
 #include"c10-1.h"
 void ShellInsert(SqList &L,int dk)
 { // ��˳���L��һ��ϣ���������򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ�
   // ���������޸ģ�
   // 1.ǰ���¼λ�õ�������dk,������1;
   // 2.r[0]ֻ���ݴ浥Ԫ,�����ڱ�����j<=0ʱ,����λ�����ҵ����㷨10.4
   int i,j;
   for(i=dk+1;i<=L.length;++i)
     if LT(L.r[i].key,L.r[i-dk].key)
     { // �轫L.r[i]�������������ӱ�
       L.r[0]=L.r[i]; // �ݴ���L.r[0]
       for(j=i-dk;j>0&&LT(L.r[0].key,L.r[j].key);j-=dk)
         L.r[j+dk]=L.r[j]; // ��¼���ƣ����Ҳ���λ��
       L.r[j+dk]=L.r[0]; // ����
     }
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("%d ",L.r[i].key);
   printf("\n");
 }

 void print1(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 void ShellSort(SqList &L,int dlta[],int t)
 { // ����������dlta[0..t-1]��˳���L��ϣ�������㷨10.5
   int k;
   for(k=0;k<t;++k)
   {
     ShellInsert(L,dlta[k]); // һ������Ϊdlta[k]�Ĳ�������
     printf("��%d��������: ",k+1);
     print(L);
   }
 }

 #define N 10
 #define T 3
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8},{55,9},{4,10}};
   SqList l;
   int dt[T]={5,3,1}; // ������������
   for(int i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("����ǰ: ");
   print(l);
   ShellSort(l,dt,T);
   printf("�����: ");
   print1(l);
 }
