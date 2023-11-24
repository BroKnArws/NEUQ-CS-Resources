 // algo8-1.cpp �߽��ʶ����ʵ���㷨8.1�ĳ���
 #include"c1.h"
 #include"c8-1.h"
 #define MAX 1000 // �����ÿռ�Ĵ�С(��WORD���ֽ���Ϊ��λ)
 #define e 10 // �����С�ߴ�-1(��WORD���ֽ���Ϊ��λ)

 Space AllocBoundTag(Space &pav,int n) // �㷨8.1(�״���Ϸ�)
 { // ���в�С��n�Ŀ��п�,�������Ӧ�Ĵ洢��,���������׵�ַ;���򷵻�NULL
   // �����������ÿռ���գ���pavָ����иշ�����Ľ��ĺ�̽��
   Space p,f;
   for(p=pav;p&&p->size<n&&p->rlink!=pav;p=p->rlink); // ���Ҳ�С��n�Ŀ��п�
   if(!p||p->size<n) // �Ҳ��������ؿ�ָ��
     return NULL;
   else // pָ���ҵ��Ŀ��п�
   {
     f=FootLoc(p); // ָ��ײ�
     pav=p->rlink; // pavָ��*p���ĺ�̽��
     if(p->size-n<=e) // ������䣬������<=e��ʣ����
     {
       if(pav==p) // �����ÿռ���Ϊ�ձ�
         pav=NULL;
       else // �ڱ���ɾ������Ľ��
       {
         pav->llink=p->llink;
         p->llink->rlink=pav;
       }
       p->tag=f->tag=1; // �޸ķ������ͷ���͵ײ���־
     }
     else // ����ÿ�ĺ�n����(�ߵ�ַ����)
     {
       f->tag=1; // �޸ķ����ĵײ���־
       p->size-=n; // ��ʣ����С
       f=FootLoc(p); // ָ��ʣ���ײ�
       f->tag=0; // ����ʣ���ײ�
       f->uplink=p;
       p=f+1; // ָ������ͷ��
       p->tag=1; // ���÷����ͷ��
       p->size=n;
     }
     return p; // ���ط�����׵�ַ
   }
 }

 void Reclaim(Space &pav,Space &p)
 { // �߽��ʶ���Ļ����㷨
   Space s=(p-1)->uplink,t=p+p->size; // s��t�ֱ�ָ���ͷſ�������ڿ�(����ʱ)���׵�ַ
   int l=(p-1)->tag,r=(p+p->size)->tag; // l��r�ֱ�ָʾ�ͷſ�������ڿ��Ƿ����
   if(!pav) // �����ÿռ���
   { // ���ͷſ���뵽pav��ָ�Ŀ����ÿռ����
     pav=p->llink=p->rlink=p; // ͷ���������ָ�뼰pav��ָ���ͷſ�
     p->tag=0; // �޸�ͷ������־Ϊ����
     (FootLoc(p))->uplink=p; // �޸�β����
     (FootLoc(p))->tag=0;
   }
   else // �����ÿռ����
   {
     if(l==1&&r==1) // ����������Ϊռ�ÿ�
     {
       p->tag=0; // �޸�ͷ������־Ϊ����
       (FootLoc(p))->uplink=p; // �޸�β����
       (FootLoc(p))->tag=0;
       pav->llink->rlink=p; // ��p��ָ���(���ͷŵĽ��)����pav��ָ���֮ǰ
       p->llink=pav->llink;
       p->rlink=pav;
       pav->llink=p;
       pav=p; // �޸�pav,����ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ�Ľ��
     }
     else if(l==0&&r==1) // ������Ϊ���п�,������Ϊռ�ÿ�
     { // �ϲ����ڿ���ͷſ�
       s=(p-1)->uplink; // ���ڿ��п��ͷ����ַ
       s->size+=p->size; // �����µĿ��п��С
       t=FootLoc(p); // �����µĿ��п�ײ�
       t->uplink=s;
       t->tag=0;
     }
     else if(l==1&&r==0) // ������Ϊ���п�,������Ϊռ�ÿ�
     { // �ϲ����ڿ���ͷſ�
       p->tag=0; // PΪ�ϲ���Ľ��ͷ����ַ
       p->llink=t->llink; // p��ǰ��Ϊԭt��ǰ��
       p->llink->rlink=p; // p��ǰ���ĺ��Ϊp
       p->rlink=t->rlink; // p�ĺ��Ϊԭt�ĺ��
       p->rlink->llink=p; // p�ĺ�̵�ǰ��Ϊp
       p->size+=t->size; // �µĿ��п�Ĵ�С
       (FootLoc(t))->uplink=p; // �ײ�(ԭt�ĵײ�)ָ��ָ���½���ͷ��
       if(pav==t) // �����ÿռ���ͷָ��ָ��t(t�Ѳ��ǿ��н���׵�ַ��)
         pav=p; // �޸�pav,����ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ�Ľ��
     }
     else // ����������Ϊ���п�
     {
       s->size+=p->size+t->size; // �����½��Ĵ�С
       t->llink->rlink=t->rlink; // ɾȥ���ڿ��п���
       t->rlink->llink=t->llink;
       (FootLoc(t))->uplink=s; // �½��ײ�(ԭt�ĵײ�)ָ��ָ����ͷ��
       if(pav==t) // �����ÿռ���ͷָ��ָ��t(t�Ѳ��ǿ��н���׵�ַ��)
         pav=s; // �޸�pav,����ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ�Ľ��
     }
   }
   p=NULL; // ����ͷŵĽ���ָ��Ϊ��
 }

 void Print(Space p)
 { // ���p��ָ�Ŀ����ÿռ��
   Space h,f;
   if(p) // �����ÿռ����
   {
     h=p; // hָ���һ������ͷ����(�׵�ַ)
     f=FootLoc(h); // fָ���һ�����ĵײ���
     do
     {
       printf("��Ĵ�С=%d ����׵�ַ=%u ",h->size,f->uplink); // ��������Ϣ
       printf("���־=%d(0:���� 1:ռ��) �ڿ��׵�ַ=%u\n",h->tag,f+1);
       h=h->rlink; // ָ����һ������ͷ����(�׵�ַ)
       f=FootLoc(h); // fָ����һ�����ĵײ���
     }while(h!=p); // û��ѭ������ı�β
   }
 }

 void PrintUser(Space p[])
 { // ���p������ָ���ѷ���ռ�
   for(int i=0;i<MAX/e;i++)
     if(p[i]) // ָ�벻Ϊ0(ָ��һ��ռ�ÿ�)
     {
       printf("��%d���׵�ַ=%u ",i,p[i]); // ��������Ϣ
       printf("��Ĵ�С=%d ��ͷ��־=%d(0:���� 1:ռ��)",p[i]->size,p[i]->tag);
       printf(" ��β��־=%d\n",(FootLoc(p[i]))->tag);
     }
 }

 void main()
 {
   Space pav,p; // ���п�ָ��
   Space v[MAX/e]={NULL}; // ռ�ÿ�ָ������(��ʼ��Ϊ��)
   int n;
   printf("�ṹ��WORDΪ%d���ֽ�\n",sizeof(WORD));
   p=new WORD[MAX+2]; // �����СΪMAX*sizeof(WORD)���ֽڵĿռ�
   p->tag=1; // ���õ�ַ�߽�,�Է����������ڿ�ʱ����
   pav=p+1; // �����ÿռ��ı�ͷ
   pav->rlink=pav->llink=pav; // ��ʼ�������ÿռ�(һ������)
   pav->tag=0;
   pav->size=MAX;
   p=FootLoc(pav); // pָ��ײ���
   p->uplink=pav;
   p->tag=0;
   (p+1)->tag=1; // ���ø�ַ�߽�,�Է����������ڿ�ʱ����
   printf("��ʼ���󣬿����ÿռ��Ϊ:\n");
   Print(pav);
   n=300;
   v[0]=AllocBoundTag(pav,n);
   printf("����%u���洢�ռ�󣬿����ÿռ��Ϊ:\n",n);
   Print(pav);
   PrintUser(v);
   n=450;
   v[1]=AllocBoundTag(pav,n);
   printf("����%u���洢�ռ��pavΪ:\n",n);
   Print(pav);
   PrintUser(v);
   n=300; // ���䲻�ɹ�
   v[2]=AllocBoundTag(pav,n);
   printf("����%u���洢�ռ��(���ɹ�)��pavΪ:\n",n);
   Print(pav);
   PrintUser(v);
   n=242; // ����������(250)
   v[2]=AllocBoundTag(pav,n);
   printf("����%u���洢�ռ��(�������)��pavΪ:\n",n);
   Print(pav);
   PrintUser(v);
   printf("����v[0](%d)��(��pav��ʱ����)��pavΪ:\n",v[0]->size);
   Reclaim(pav,v[0]); // pavΪ��
   Print(pav);
   PrintUser(v);
   printf("1���س�������");
   getchar();
   printf("����v[2](%d)��(����������Ϊռ�ÿ�),pavΪ:\n",v[2]->size);
   Reclaim(pav,v[2]); // ����������Ϊռ�ÿ�
   Print(pav);
   PrintUser(v);
   n=270; // ���ҿռ��㹻��Ŀ�
   v[0]=AllocBoundTag(pav,n);
   printf("����%u���洢�ռ��(���ҿռ��㹻��Ŀ�)��pavΪ:\n",n);
   Print(pav);
   PrintUser(v);
   n=30; // �ڵ�ǰ���Ϸ���
   v[2]=AllocBoundTag(pav,n);
   printf("����%u���洢�ռ��(�ڵ�ǰ���Ϸ���)��pavΪ:\n",n);
   Print(pav);
   PrintUser(v);
   printf("����v[1](%d)��(������Ϊ���п�,������Ϊռ�ÿ�)��pavΪ:\n",v[1]->size);
   Reclaim(pav,v[1]); // ������Ϊ���п�,������Ϊռ�ÿ�
   Print(pav);
   PrintUser(v);
   printf("2���س�������");
   getchar();
   printf("����v[0](%d)��(������Ϊ���п�,������Ϊռ�ÿ�)��pavΪ:\n",v[0]->size);
   Reclaim(pav,v[0]); // ������Ϊ���п�,������Ϊռ�ÿ�
   Print(pav);
   PrintUser(v);
   printf("����v[2](%d)��(����������Ϊ���п�),pavΪ:\n",v[2]->size);
   Reclaim(pav,v[2]); // ����������Ϊ���п�
   Print(pav);
   PrintUser(v);
 }
