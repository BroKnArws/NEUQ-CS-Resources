 // algo8-2.cpp ���ϵͳ��ʵ���㷨8.2�ĳ���
 #include"c1.h"
 #include"c8-2.h"
 #define N 100 // ռ�ÿ���������ֵ
 Space r; // rΪ���ɿռ���׵�ַ,ȫ����

 Space AllocBuddy(FreeList &avail,int n)
 { // avail[0..m]Ϊ�����ÿռ��,nΪ���������,���в�С��n�Ŀ��п�,
   // �������Ӧ�Ĵ洢��,���������׵�ַ;���򷵻�NULL���㷨8.2
   int i,k;
   Space pa,pi,pre,suc;
   for(k=0;k<=m&&(avail[k].nodesize<n+1||!avail[k].first);++k); // �����������Ҫ����ӱ�
   if(k>m) // ����ʧ�ܣ�����NULL
     return NULL;
   else // ���з���
   {
     pa=avail[k].first; // ָ��ɷ����ӱ�ĵ�һ�����
     pre=pa->llink; // �ֱ�ָ��ǰ���ͺ��
     suc=pa->rlink;
     if(pa==suc)
       avail[k].first=NULL; // �������ӱ��ɿձ�
     else // ���ӱ�ɾȥ*pa���
     {
       pre->rlink=suc;
       suc->llink=pre;
       avail[k].first=suc;
     }
     for(i=1;avail[k-i].nodesize>=n+1;++i)
     {
       pi=pa+int(pow(2,k-i));
       pi->rlink=pi;
       pi->llink=pi;
       pi->tag=0;
       pi->kval=k-i;
       avail[k-i].first=pi;
     } // ��ʣ��������Ӧ�ӱ�
     pa->tag=1;
     pa->kval=k-(--i);
   }
   return pa;
 }

 Space buddy(Space p)
 { // ���������ʼ��ַΪp,���СΪpow(2,k)�Ŀ�Ļ���ַ
   if((p-r)%int(pow(2,p->kval+1))==0) // pΪǰ��
     return p+int(pow(2,p->kval));
   else // pΪ���
     return p-int(pow(2,p->kval));
 }

 void Reclaim(FreeList &pav,Space &p)
 { // ���ϵͳ�Ļ����㷨 ��p��ָ���ͷſ���յ������ÿռ��pav��
   Space s;
   s=buddy(p); // �������ʼ��ַ
   while(s>=r&&s<r+pav[m].nodesize&&s->tag==0) // �鲢����,������ʼ��ַ����Ч��Χ���һ������
   { // ��������ɾ���ý��
     if(s->llink==s&&s->rlink==s) // �����Ͻ���һ�����
       pav[s->kval].first=NULL; // �ô�����Ϊ��
     else // �����ϲ�ֹһ�����
     {
       s->llink->rlink=s->rlink; // ǰ���ĺ��Ϊ�ý��ĺ��
       s->rlink->llink=s->llink; // ��̵�ǰ��Ϊ�ý���ǰ��
       if(pav[s->kval].first==s) // s������ĵ�һ�����
         pav[s->kval].first=s->rlink; // ��ͷָ����һ�����
     } // �����޸Ľ��ͷ��
     if((p-r)%int(pow(2,p->kval+1))==0) // pΪǰ��
       p->kval++;
     else // pΪ���
     {
       s->kval=p->kval+1;
       p=s; // pָ���¿��׵�ַ
     }
     s=buddy(p); // ��һ���������ʼ��ַ
   }
   // ���½�p�嵽�����ÿռ����
   p->tag=0;
   if(pav[p->kval].first==NULL) // �������
     pav[p->kval].first=p->llink=p->rlink=p;
   else // ���ڱ�ͷ
   {
     p->rlink=pav[p->kval].first;
     p->llink=p->rlink->llink;
     p->rlink->llink=p;
     p->llink->rlink=p;
     pav[p->kval].first=p;
   }
   p=NULL;
 }

 void Print(FreeList p)
 { // ���p�����п����ÿռ��
   int i;
   Space h;
   for(i=0;i<=m;i++)
   {
     if(p[i].first) // ��i�������ÿռ����
     {
       h=p[i].first; // hָ������ĵ�һ������ͷ����(�׵�ַ)
       do
       {
         printf("��Ĵ�С=%d ����׵�ַ=%u ",int(pow(2,h->kval)),h); // ��������Ϣ
         printf("���־=%d(0:���� 1:ռ��)\n",h->tag);
         h=h->rlink; // ָ����һ������ͷ����(�׵�ַ)
       }while(h!=p[i].first); // û��ѭ������ı�β
     }
   }
 }

 void PrintUser(Space p[])
 { // ���p������ָ���ѷ���ռ�
   for(int i=0;i<N;i++)
     if(p[i]) // ָ�벻Ϊ0(ָ��һ��ռ�ÿ�)
     {
       printf("ռ�ÿ�%d���׵�ַ=%u ",i,p[i]); // ��������Ϣ
       printf("��Ĵ�С=%d",int(pow(2,p[i]->kval)));
       printf(" ���־=%d(0:���� 1:ռ��)\n",p[i]->tag);
     }
 }

 void main()
 {
   int i,n;
   FreeList a;
   Space q[N]={NULL}; // q����Ϊռ�ÿ���׵�ַ
   printf("sizeof(WORD)=%u m=%u int(pow(2,m))=%u\n",sizeof(WORD),m,int(pow(2,m)));
   for(i=0;i<=m;i++) // ��ʼ��a
   {
     a[i].nodesize=int(pow(2,i));
     a[i].first=NULL;
   }
   r=a[m].first=new WORD[a[m].nodesize]; // ���������������һ�����
   if(r) // ���ɽ��ɹ�
   {
     r->llink=r->rlink=r; // ��ʼ���ý��
     r->tag=0;
     r->kval=m;
     Print(a);
     PrintUser(q);
     n=100;
     q[0]=AllocBuddy(a,n); // ��a����100��WORD���ڴ�(ʵ�ʻ��128��WORD)
     printf("����%d���ֺ󣬿����ÿռ�Ϊ:\n",n);
     Print(a);
     PrintUser(q);
     n=200;
     q[1]=AllocBuddy(a,n); // ��a����200��WORD���ڴ�(ʵ�ʻ��256��WORD)
     printf("����%d������",n);
     n=220;
     q[2]=AllocBuddy(a,n); // ��a����220��WORD���ڴ�(ʵ�ʻ��256��WORD)
     printf("����%d���ֺ󣬿����ÿռ�Ϊ:\n",n);
     Print(a);
     PrintUser(q);
     Reclaim(a,q[1]); // ����q[1]����鲻����
     printf("����q[1]�󣬿����ÿռ�Ϊ:\n");
     Print(a);
     PrintUser(q);
     Reclaim(a,q[0]); // ����q[0]��������
     printf("����q[0]�󣬿����ÿռ�Ϊ:\n");
     Print(a);
     PrintUser(q);
     Reclaim(a,q[2]); // ����q[2]�������У�����һ������
     printf("����q[2]�󣬿����ÿռ�Ϊ:\n");
     Print(a);
     PrintUser(q);
   }
   else
     printf("ERROR\n");
 }
