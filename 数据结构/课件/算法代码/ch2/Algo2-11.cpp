 // algo2-11.cpp ʵ���㷨2.20��2.21�ĳ���
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.cpp"

 Status ListInsert_L(LinkList &L,int i,ElemType e) // �㷨2.20
 { // �ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
   Link h,s;
   if(!LocatePos(L,i-1,h))
     return ERROR; // iֵ���Ϸ�
   if(!MakeNode(s,e))
     return ERROR; // ������ʧ��
   InsFirst(L,h,s); //���ڴӵ�i����㿪ʼ������,��i-1�����������ͷ���
   return OK;
 }

 Status MergeList_L(LinkList La,LinkList Lb,LinkList &Lc,int(*compare)(ElemType,ElemType))
 { // ��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С��鲢La��Lb�õ��µĵ���
   // ���Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ����С������ı�La��Lb���㷨2.21
   Link ha,hb,pa,pb,q;
   ElemType a,b;
   if(!InitList(Lc))
     return ERROR; // �洢�ռ����ʧ��
   ha=GetHead(La); // ha��hb�ֱ�ָ��La��Lb��ͷ���
   hb=GetHead(Lb);
   pa=NextPos(ha); // pa��pb�ֱ�ָ��La��Lb�ĵ�һ�����
   pb=NextPos(hb);
   while(!ListEmpty(La)&&!ListEmpty(Lb)) // La��Lb���ǿ�
   {
     a=GetCurElem(pa); // a��bΪ�����е�ǰ�Ƚ�Ԫ��
     b=GetCurElem(pb);
     if(compare(a,b)<=0)
     {
       DelFirst(La,ha,q);
       InsFirst(Lc,Lc.tail,q);
       pa=NextPos(ha);
     }
     else // a>b
     {
       DelFirst(Lb,hb,q);
       InsFirst(Lc,Lc.tail,q);
       pb=NextPos(hb);
     }
   }
   if(!ListEmpty(La))
     Append(Lc,pa);
   else
     Append(Lc,pb);
   FreeNode(ha);
   FreeNode(hb);
   return OK;
 }

 int comp(ElemType c1,ElemType c2)
 {
   return c1-c2;
 }

 void visit(ElemType c)
 {
   printf("%d ",c); // ����
 }

 void main()
 {
   LinkList La,Lb,Lc;
   int j;
   InitList(La);
   for(j=1;j<=5;j++)
     ListInsert_L(La,j,j); // ˳����� 1 2 3 4 5
   printf("La=");
   ListTraverse(La,visit);
   InitList(Lb);
   for(j=1;j<=5;j++)
     ListInsert_L(Lb,j,2*j); // ˳����� 2 4 6 8 10
   printf("Lb=");
   ListTraverse(Lb,visit);
   InitList(Lc);
   MergeList_L(La,Lb,Lc,comp); // �鲢La��Lb������Lc
   printf("Lc=");
   ListTraverse(Lc,visit);
   DestroyList(Lc);
 }