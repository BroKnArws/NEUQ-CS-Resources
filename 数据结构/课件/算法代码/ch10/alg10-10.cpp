 // alg10-10.cpp �鲢����
 #include<stdio.h>
 typedef int InfoType; // �������������������
 #include"c9.h"
 #include"c10-1.h"

 void Merge(RedType SR[],RedType TR[],int i,int m,int n)
 { // �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n] �㷨10.12
   int j,k,l;
   for(j=m+1,k=i;i<=m&&j<=n;++k) // ��SR�м�¼��С����ز���TR
     if LQ(SR[i].key,SR[j].key)
       TR[k]=SR[i++];
     else
       TR[k]=SR[j++];
   if(i<=m)
     for(l=0;l<=m-i;l++)
       TR[k+l]=SR[i+l]; // ��ʣ���SR[i..m]���Ƶ�TR
   if(j<=n)
     for(l=0;l<=n-j;l++)
       TR[k+l]=SR[j+l]; // ��ʣ���SR[j..n]���Ƶ�TR
 }

 void MSort(RedType SR[],RedType TR1[],int s, int t)
 { // ��SR[s..t]�鲢����ΪTR1[s..t]���㷨10.13
   int m;
   RedType TR2[MAXSIZE+1];
   if(s==t)
     TR1[s]=SR[s];
   else
   {
     m=(s+t)/2; // ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
     MSort(SR,TR2,s,m); // �ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
     MSort(SR,TR2,m+1,t); // �ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
     Merge(TR2,TR1,s,m,t); // ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]
   }
 }

 void MergeSort(SqList &L)
 { // ��˳���L���鲢�����㷨10.14
   MSort(L.r,L.r,1,L.length);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 #define N 7
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("����ǰ:\n");
   print(l);
   MergeSort(l);
   printf("�����:\n");
   print(l);
 }
