 // algo2-10.cpp ���������βָ���ѭ������ĺϲ����̿���ͼ2.13��
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
 #include"bo2-4.cpp"

 void MergeList_CL(LinkList &La,LinkList Lb)
 {
   LinkList p=Lb->next;
   Lb->next=La->next;
   La->next=p->next;
   free(p);
   La=Lb;
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int n=5,i;
   LinkList La,Lb;
   InitList_CL(La);
   for(i=1;i<=n;i++)
     ListInsert_CL(La,i,i);
   printf("La="); // �������La������
   ListTraverse_CL(La,visit);
   InitList_CL(Lb);
   for(i=1;i<=n;i++)
     ListInsert_CL(Lb,1,i*2);
   printf("Lb="); // �������Lb������
   ListTraverse_CL(Lb,visit);
   MergeList_CL(La,Lb);
   printf("La+Lb="); // ����ϲ�������������
   ListTraverse_CL(La,visit);
 }
