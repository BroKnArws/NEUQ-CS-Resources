 // bo5-6.cpp ��������չ��������洢(�洢�ṹ��c5-6.h����)�Ļ�������(13��)
 #include"c4-2.h" // ����HString����
 #include"bo4-2.cpp" // HString���͵Ļ�������
 // ��������д��ʽ��ΪHString����
 Status InitGList(GList &L)
 { // �����յĹ����L
   L=NULL;
   return OK;
 }

 Status sever(HString &str,HString &hstr) // ͬbo5-52.cpp
 { // ���ǿմ�str�ָ��������:hstrΪ��һ��','֮ǰ���Ӵ�,strΪ֮����Ӵ�
   int n,i=1,k=0; // k����δ��Ե������Ÿ���
   HString ch,c1,c2,c3;
   InitString(ch); // ��ʼ��HString���͵ı���
   InitString(c1);
   InitString(c2);
   InitString(c3);
   StrAssign(c1,",");
   StrAssign(c2,"(");
   StrAssign(c3,")");
   n=StrLength(str);
   do
   {
     SubString(ch,str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
     ++i;
   }while(i<=n&&StrCompare(ch,c1)||k!=0);
   if(i<=n)
   {
     StrCopy(ch,str);
     SubString(hstr,ch,1,i-2);
     SubString(str,ch,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,str);
     ClearString(str);
   }
   return OK;
 }

 Status CreateGList(GList &L,HString S)
 { // ��ʼ����: S�ǹ�������д��ʽ�����������: ��S���������L
   HString emp,sub,hsub;
   GList p;
   InitString(emp);
   InitString(sub);
   InitString(hsub);
   StrAssign(emp,"()"); // ��emp="()"
   if(!(L=(GList)malloc(sizeof(GLNode)))) // �����㲻�ɹ�
     exit(OVERFLOW);
   if(!StrCompare(S,emp)) // �����ձ�
   {
     L->tag=LIST;
     L->hp=NULL;
     L->tp=NULL;
   }
   else if(StrLength(S)==1) // ������ԭ�ӹ����
   {
     L->tag=ATOM;
     L->atom=S.ch[0];
     L->tp=NULL;
   }
   else // ����һ���
   {
     L->tag=LIST;
     L->tp=NULL;
     SubString(sub,S,2,StrLength(S)-2); // ���������
     sever(sub,hsub); // ��sub�з������ͷ��hsub
     CreateGList(L->hp,hsub);
     p=L->hp;
     while(!StrEmpty(sub)) // ��β����,���ظ���n���ӱ�
     {
       sever(sub,hsub); // ��sub�з������ͷ��hsub
       CreateGList(p->tp,hsub);
       p=p->tp;
     };
   }
   return OK;
 }

 void DestroyGList(GList &L)
 { // ��ʼ����: �����L���ڡ��������: ���ٹ����L
   GList ph,pt;
   if(L) // L��Ϊ�ձ�
   { // ��ph��pt����L������ָ��
     if(L->tag) // ���ӱ�
       ph=L->hp;
     else // ��ԭ��
       ph=NULL;
     pt=L->tp;
     free(L); // �ͷ�L��ָ���
     L=NULL; // ��LΪ��
     DestroyGList(ph); // �ݹ����ٱ�ph
     DestroyGList(pt); // �ݹ����ٱ�pt
   }
 }

 Status CopyGList(GList &T,GList L)
 { // ��ʼ����: �����L���ڡ��������: �ɹ����L���Ƶõ������T
   if(!L) // L��
   {
     T=NULL;
     return OK;
   }
   T=(GList)malloc(sizeof(GLNode));
   if(!T)
     exit(OVERFLOW);
   T->tag=L->tag; // ����ö�ٱ���
   if(L->tag==ATOM) // ���ƹ����岿��
     T->atom=L->atom; // ���Ƶ�ԭ��
   else
     CopyGList(T->hp,L->hp); // �����ӱ�
   if(L->tp==NULL) // ����β
     T->tp=L->tp;
   else
     CopyGList(T->tp,L->tp); // �����ӱ�
   return OK;
 }

 int GListLength(GList L)
 { // ��ʼ����: �����L���ڡ��������: ������L�ĳ���,��Ԫ�ظ���
   int len=0;
   GList p;
   if(L->tag==LIST&&!L->hp) // �ձ�
     return 0; // �ձ���0
   else if(L->tag==ATOM) // ��ԭ�ӱ�
     return 1;
   else // һ���
   {
     p=L->hp;
     do
     {
       len++;
       p=p->tp;
     }while(p);
     return len;
   }
 }

 int GListDepth(GList L)
 { // ��ʼ����: �����L���ڡ��������: ������L�����
   int max,dep;
   GList pp;
   if(L==NULL||L->tag==LIST&&!L->hp)
     return 1; // �ձ����Ϊ1
   else if(L->tag==ATOM)
     return 0; // ��ԭ�ӱ����Ϊ0
   else // ��һ�������
     for(max=0,pp=L->hp;pp;pp=pp->tp)
     {
       dep=GListDepth(pp); // ����ppΪͷָ����ӱ����
       if(dep>max)
         max=dep;
     }
   return max+1; // �ǿձ������Ǹ�Ԫ�ص���ȵ����ֵ��1
 }

 Status GListEmpty(GList L)
 { // ��ʼ����: �����L���ڡ��������: �ж������L�Ƿ�Ϊ��
   if(!L||L->tag==LIST&&!L->hp)
     return OK;
   else
     return ERROR;
 }

 GList GetHead(GList L)
 { // ��ʼ����: �����L���ڡ��������: ȡ�����L��ͷ
   GList h;
   InitGList(h);
   if(!L||L->tag==LIST&&!L->hp)
   {
     printf("\n�ձ��ޱ�ͷ!");
     exit(0);
   }
   h=(GList)malloc(sizeof(GLNode));
   if(!h)
     exit(OVERFLOW);
   h->tag=L->hp->tag;
   h->tp=NULL;
   if(h->tag==ATOM)
     h->atom=L->hp->atom;
   else
     CopyGList(h->hp,L->hp->hp);
   return h;
 }

 GList GetTail(GList L)
 { // ��ʼ����: �����L���ڡ��������: ȡ�����L��β
   GList T;
   if(!L)
   {
     printf("\n�ձ��ޱ�β!");
     exit(0);
   }
   T=(GList)malloc(sizeof(GLNode));
   if(!T)
     exit(OVERFLOW);
   T->tag=LIST;
   T->tp=NULL;
   CopyGList(T->hp,L->hp->tp);
   return T;
 }

 Status InsertFirst_GL(GList &L,GList e)
 { // ��ʼ����: ��������
   // �������: ����Ԫ��e��Ϊ�����L�ĵ�һԪ��(��ͷ,Ҳ�������ӱ�)
   GList p=L->hp;
   L->hp=e;
   e->tp=p;
   return OK;
 }

 Status DeleteFirst_GL(GList &L,GList &e)
 { // ��ʼ����:�����L���ڡ��������:ɾ�������L�ĵ�һԪ��,����e������ֵ
   if(L)
   {
     e=L->hp;
     L->hp=e->tp;
     e->tp=NULL;
   }
   else
     e=L;
   return OK;
 }

 void Traverse_GL(GList L,void(*v)(AtomType))
 { // ���õݹ��㷨���������L
   GList hp;
   if(L) // L����
   {
     if(L->tag==ATOM) // LΪ��ԭ��
     {
       v(L->atom);
       hp=NULL;
     }
     else // LΪ�ӱ�
       hp=L->hp;
     Traverse_GL(hp,v);
     Traverse_GL(L->tp,v);
   }
 }
