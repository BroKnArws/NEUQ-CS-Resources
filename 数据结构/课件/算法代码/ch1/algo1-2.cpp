 // algo1-2.cpp ����1-1/x+1/x*x���ĸ���ݵ��㷨
 #include<stdio.h>
 #include<sys/timeb.h>
 void main()
 {
   timeb t1,t2;
   long t;
   double x,sum1=1,sum=1;
   int i,n;
   printf("������x n: ");
   scanf("%lf%d",&x,&n);
   ftime(&t1); // ��õ�ǰʱ��
   for(i=1;i<=n;i++)
   {
     sum1*=-1.0/x;
     sum+=sum1;
   }
   ftime(&t2); // ��õ�ǰʱ��
   t=(t2.time-t1.time)*1000+(t2.millitm-t1.millitm); // ����ʱ���
   printf("sum=%lf ��ʱ%ld����\n",sum,t);
 }
