 // algo2-7.cpp �̿�����ͼ2.10��̬����ʾ��
 // ��һ������λ����[0].cur�У���Աcur��ֵΪ0��������β
 #include"c1.h"
 #define N 6 // �ַ�������
 typedef char ElemType[N];
 #include"c2-3.h"

 void main()
 {
   SLinkList s={{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0}};
   int i;
   i=s[0].cur;
   while(i) // ����̿�����ͼ2.10(a)��״̬
   {
     printf("%s ",s[i].data); // �������ĵ�ǰֵ
     i=s[i].cur; // �ҵ���һ��
   }
   printf("\n");
   s[4].cur=9; // ���̿�����ͼ2.10(b)�޸�
   s[6].cur=8;
   s[9].cur=5;
   strcpy(s[9].data,"SHI");
   i=s[0].cur;
   while(i) // ����̿�����ͼ2.10(b)��״̬
   {
     printf("%s ",s[i].data); // �������ĵ�ǰֵ
     i=s[i].cur; // �ҵ���һ��
   }
   printf("\n");
 }