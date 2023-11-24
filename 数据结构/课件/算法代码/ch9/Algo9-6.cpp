 // algo9-6.cpp ����bo9-4.cpp�ĳ���
 #include"c1.h"
 #define m 3 // B���Ľף�����Ϊ3
 #define N 16 // ����Ԫ�ظ���
 #define MAX 5 // �ַ�����󳤶�+1
 typedef int KeyType; // ��ؼ�����Ϊ����
 struct Others // ��¼����������
 {
   char info[MAX];
 };

 #include"c9-3.h"
 #include"bo9-4.cpp"

 void print(BTNode c,int i) // TraverseDSTable()���õĺ���
 {
   printf("(%d,%s)",c.node[i].key,c.node[i].recptr->others.info);
 }

 void main()
 {
   Record r[N]={{24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},
		{50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
		{3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
		{7,"16"}}; // (�Խ̿�����ͼ9.16Ϊ��)
   BTree t;
   Result s;
   int i;
   InitDSTable(t);
   for(i=0;i<N;i++)
   {
     s=SearchBTree(t,r[i].key);
     if(!s.tag)
       InsertBTree(t,&r[i],s.pt,s.i);
   }
   printf("���ؼ��ֵ�˳�����B_��:\n");
   TraverseDSTable(t,print);
   printf("\n����������Ҽ�¼�Ĺؼ���: ");
   scanf("%d",&i);
   s=SearchBTree(t,i);
   if(s.tag)
     print(*(s.pt),s.i);
   else
     printf("û�ҵ�");
   printf("\n");
   DestroyDSTable(t);
 }
