 // algo8-3.cpp ʵ���㷨8.3�ĳ���
 #include"c1.h"
 typedef char AtomType; // ����ԭ������Ϊ�ַ���
 #include"c8-3.h"
 #include"bo5-51.cpp"

 Status CreateMarkGList(GList &L,SString S) // ��bo5-51.cpp��
 { // ����ͷβ����洢�ṹ,�ɹ�������д��ʽ��S���������L����emp="()"
   SString sub,hsub,emp;
   GList p,q;
   StrAssign(emp,"()");
   if(!StrCompare(S,emp))
     L=NULL; // �����ձ�
   else
   {
     if(!(L=(GList)malloc(sizeof(GLNode)))) // ������
       exit(OVERFLOW);
     if(StrLength(S)==1) // SΪ��ԭ��
     {
       L->tag=ATOM;
       L->atom=S[1]; // ������ԭ�ӹ����
       L->mark=0; // ��
     }
     else
     {
       L->tag=LIST;
       L->mark=0; // ��
       p=L;
       SubString(sub,S,2,StrLength(S)-2); // ���������
       do
       { // �ظ���n���ӱ�
         sever(sub,hsub); // ��sub�з������ͷ��hsub
         CreateMarkGList(p->ptr.hp,hsub); // ��
         q=p;
         if(!StrEmpty(sub)) // ��β����
         {
           if(!(p=(GLNode *)malloc(sizeof(GLNode))))
             exit(OVERFLOW);
           p->tag=LIST;
           p->mark=0; // ��
	   q->ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->ptr.tp=NULL;
     }
   }
   return OK;
 }

 void MarkList(GList GL) // �㷨8.3
 { // �����ǿչ����GL(GL!=NULL��GL->mark==0),�Ա�������δ�ӱ�־�Ľ��ӱ�־��
   GList t,p,q;
   Status finished;
   if(GL!=NULL&&GL->mark==0)
   {
     t=NULL; // tָʾp��ĸ��
     p=GL;
     finished=FALSE;
     while(!finished)
     {
       while(p->mark==0)
       {
	 p->mark=1; // MarkHead(p)��ϸ��
         q=p->ptr.hp; // qָ��*p�ı�ͷ
         if(q&&q->mark==0)
           if(q->tag==0)
             q->mark=1; // ATOM,��ͷΪԭ�ӽ��
           else
           { // ���������ӱ�
             p->ptr.hp=t;
             p->tag=ATOM;
             t=p;
             p=q;
           }
       } // ��ɶԱ�ͷ�ı�־
       q=p->ptr.tp; // qָ��*p�ı�β
       if(q&&q->mark==0)
       { // ����������β
         p->ptr.tp=t;
         t=p;
         p=q;
       }
       else // BackTrack(finished)��ϸ��
       {
         while(t&&t->tag==1) // LIST,����,�ӱ�β����
         {
           q=t;
           t=q->ptr.tp;
           q->ptr.tp=p;
           p=q;
         }
         if(!t)
           finished=TRUE; // ����
         else
         { // �ӱ�ͷ����
           q=t;
           t=q->ptr.hp;
           q->ptr.hp=p;
           p=q;
           p->tag=LIST;
         } // ����������β
       }
     }
   }
 }

 void Traverse_GL(GList L,void(*v)(GList))
 { // ���õݹ��㷨���������L,��bo5-5.cpp��
   if(L) // L����
     if(L->tag==ATOM) // LΪ��ԭ��
       v(L);
     else // LΪ�����
     {
       v(L);
       Traverse_GL(L->ptr.hp,v);
       Traverse_GL(L->ptr.tp,v);
     }
 }

 void visit(GList p)
 {
   if(p->tag==ATOM)
     printf("mark=%d %c\n",p->mark,p->atom);
   else
     printf("mark=%d list\n",p->mark);
 }

 void main()
 {
   char p[80];
   SString t;
   GList l;
   printf("����������l(��д��ʽ���ձ�:(),��ԭ��:a,����:(a,(b),b)):\n");
   gets(p);
   StrAssign(t,p);
   CreateMarkGList(l,t);
   Traverse_GL(l,visit);
   MarkList(l);
   printf("�ӱ�־��:\n");
   Traverse_GL(l,visit);
 }
