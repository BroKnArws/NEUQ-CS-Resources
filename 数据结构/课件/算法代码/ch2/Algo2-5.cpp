 // algo2-5.cpp ʵ���㷨2.11��2.12�ĳ���
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
 #include"bo2-2.cpp"

 void CreateList(LinkList &L,int n) // �㷨2.11
 { // ��λ��(���ڱ�ͷ)����n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�L
   int i;
   LinkList p;
   L=(LinkList)malloc(sizeof(LNode));
   L->next=NULL; // �Ƚ���һ����ͷ���ĵ�����
   printf("������%d������\n",n);
   for(i=n;i>0;--i)
   {
     p=(LinkList)malloc(sizeof(LNode)); // �����½��
     scanf("%d",&p->data); // ����Ԫ��ֵ
     p->next=L->next; // ���뵽��ͷ
     L->next=p;
   }
 }

 void CreateList2(LinkList &L,int n)
 { // ��λ��(���ڱ�β)����n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�
   int i;
   LinkList p,q;
   L=(LinkList)malloc(sizeof(LNode)); // ����ͷ���
   L->next=NULL;
   q=L;
   printf("������%d������\n",n);
   for(i=1;i<=n;i++)
   {
     p=(LinkList)malloc(sizeof(LNode));
     scanf("%d",&p->data);
     q->next=p;
     q=q->next;
   }
   p->next=NULL;
 }

 void MergeList(LinkList La,LinkList &Lb,LinkList &Lc)// �㷨2.12
 { // ��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����С�
   // �鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
   LinkList pa=La->next,pb=Lb->next,pc;
   Lc=pc=La; // ��La��ͷ�����ΪLc��ͷ���
   while(pa&&pb)
     if(pa->data<=pb->data)
     {
       pc->next=pa;
       pc=pa;
       pa=pa->next;
     }
     else
     {
       pc->next=pb;
       pc=pb;
       pb=pb->next;
     }
   pc->next=pa?pa:pb; // ����ʣ���
   free(Lb); // �ͷ�Lb��ͷ���
   Lb=NULL;
 }

 void visit(ElemType c) // ListTraverse()���õĺ���(����Ҫһ��)
 {
   printf("%d ",c);
 }

 void main()
 {
   int n=5;
   LinkList La,Lb,Lc;
   printf("���ǵݼ�˳��, ");
   CreateList2(La,n); // ��λ������n��Ԫ�ص�ֵ
   printf("La="); // �������La������
   ListTraverse(La,visit);
   printf("���ǵ���˳��, ");
   CreateList(Lb,n); // ��λ������n��Ԫ�ص�ֵ
   printf("Lb="); // �������Lb������
   ListTraverse(Lb,visit);
   MergeList(La,Lb,Lc); // ���ǵݼ�˳��鲢La��Lb,�õ��±�Lc
   printf("Lc="); // �������Lc������
   ListTraverse(Lc,visit);
 }
