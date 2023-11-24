 // algo10-7.cpp ��ѡ������
 #include<stdio.h>
 typedef int InfoType; // �������������������
 #include"c10-1.h"
 int SelectMinKey(SqList L,int i)
 { // ������L.r[i..L.length]��key��С�ļ�¼�����
   KeyType min;
   int j,k;
   k=i; // ���i��Ϊ��С
   min=L.r[i].key;
   for(j=i+1;j<=L.length;j++)
     if(L.r[j].key<min) // �ҵ���С��
     {
       k=j;
       min=L.r[j].key;
     }
   return k;
 }

 void SelectSort(SqList &L)
 { // ��˳���L����ѡ�������㷨10.9
   int i,j;
   RedType t;
   for(i=1;i<L.length;++i)
   { //  ѡ���iС�ļ�¼����������λ
     j=SelectMinKey(L,i); // ��L.r[i..L.length]��ѡ��key��С�ļ�¼
     if(i!=j)
     { // ���i����¼����
       t=L.r[i];
       L.r[i]=L.r[j];
       L.r[j]=t;
     }
   }
 }

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
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("����ǰ:\n");
   print(l);
   SelectSort(l);
   printf("�����:\n");
   print(l);
 }