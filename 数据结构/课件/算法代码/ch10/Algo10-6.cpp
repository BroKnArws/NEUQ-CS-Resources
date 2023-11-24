 // algo10-6.cpp �����㷨10.6(b)�ĳ���(�㷨10.6(a)�ĸĽ�)
 #include<stdio.h>
 typedef int InfoType; // �������������������
 #include"c10-1.h"
 int Partition(SqList &L,int low,int high)
 { // ����˳���L���ӱ�r[low..high]�ļ�¼�������¼��λ����������
   // ����λ�ã���ʱ����֮ǰ���󣩵ļ�¼������С���������㷨10.6(b)
   KeyType pivotkey;
   L.r[0]=L.r[low]; // ���ӱ�ĵ�һ����¼�������¼
   pivotkey=L.r[low].key; // �����¼�ؼ���
   while(low< high)
   { // �ӱ�����˽�������м�ɨ��
     while(low<high&&L.r[high].key>=pivotkey)
       --high;
     L.r[low]=L.r[high]; // ���������¼С�ļ�¼�Ƶ��Ͷ�
     while(low<high&&L.r[low].key<=pivotkey)
       ++low;
     L.r[high]=L.r[low]; // ���������¼��ļ�¼�Ƶ��߶�
   }
   L.r[low]=L.r[0]; // �����¼��λ
   return low; // ��������λ��
 }

 #include"bo10-2.cpp"
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
   QuickSort(l);
   printf("�����:\n");
   print(l);
 }
