 // algo2-12.cpp �õ�����ʵ���㷨2.1,����4����algo2-1.cpp��ͬ
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" // �˾���algo2-1.cpp��ͬ(��Ϊ���ò�ͬ�Ľṹ)
 #include"bo2-2.cpp" // �˾���algo2-1.cpp��ͬ(��Ϊ���ò�ͬ�Ľṹ)

 Status equal(ElemType c1,ElemType c2)
 { // �ж��Ƿ���ȵĺ�����Union()�õ�
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void Union(LinkList La,LinkList Lb) // �㷨2.1,�˾���algo2-1.cpp��ͬ
 { // �����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La��
   ElemType e;
   int La_len,Lb_len;
   int i;
   La_len=ListLength(La); // �����Ա�ĳ���
   Lb_len=ListLength(Lb);
   for(i=1;i<=Lb_len;i++)
   {
     GetElem(Lb,i,e); // ȡLb�е�i������Ԫ�ظ���e
     if(!LocateElem(La,e,equal)) // La�в����ں�e��ͬ��Ԫ��,�����֮
       ListInsert(La,++La_len,e);
   }
 }

 void print(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList La,Lb; // �˾���algo2-1.cpp��ͬ(��Ϊ���ò�ͬ�Ľṹ)
   Status i;
   int j;
   i=InitList(La);
   if(i==1) // �����ձ�La�ɹ�
     for(j=1;j<=5;j++) // �ڱ�La�в���5��Ԫ��
       i=ListInsert(La,j,j);
   printf("La= "); // �����La������
   ListTraverse(La,print);
   InitList(Lb); // Ҳ�ɲ��ж��Ƿ񴴽��ɹ�
   for(j=1;j<=5;j++) // �ڱ�Lb�в���5��Ԫ��
     i=ListInsert(Lb,j,2*j);
   printf("Lb= "); // �����Lb������
   ListTraverse(Lb,print);
   Union(La,Lb);
   printf("new La= "); // ����±�La������
   ListTraverse(La,print);
 }