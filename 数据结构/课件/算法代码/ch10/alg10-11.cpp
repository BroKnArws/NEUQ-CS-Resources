 // alg10-11.cpp ��ʽ��������
 typedef int InfoType; // �������������������
 typedef int KeyType; // ����RedType���͵Ĺؼ���Ϊ����
 struct RedType // ��¼����(ͬc10-1.h)
 {
   KeyType key; // �ؼ�����
   InfoType otherinfo; // ����������
 };
 typedef char KeysType; // ����ؼ�������Ϊ�ַ���
 #include"c1.h"
 #include"c10-3.h"
 void InitList(SLList &L,RedType D[],int n)
 { // ��ʼ����̬����L��������D�е����ݴ���L�У�
   char c[MAX_NUM_OF_KEY],c1[MAX_NUM_OF_KEY];
   int i,j,max=D[0].key; // maxΪ�ؼ��ֵ����ֵ
   for(i=1;i<n;i++)
     if(max<D[i].key)
       max=D[i].key;
   L.keynum=int(ceil(log10(max)));
   L.recnum=n;
   for(i=1;i<=n;i++)
   {
     L.r[i].otheritems=D[i-1].otherinfo;
     itoa(D[i-1].key,c,10); // ��10��������ת��Ϊ�ַ���,����c
     for(j=strlen(c);j<L.keynum;j++) // ��c�ĳ���<max��λ��,��cǰ��'0'
     {
       strcpy(c1,"0");
       strcat(c1,c);
       strcpy(c,c1);
     }
     for(j=0;j<L.keynum;j++)
       L.r[i].keys[j]=c[L.keynum-1-j];
   }
 }

 int ord(char c)
 { // ����k��ӳ��(��λ����)
   return c-'0';
 }

 void Distribute(SLCell r[],int i,ArrType f,ArrType e) // �㷨10.15
 { // ��̬����L��r���м�¼�Ѱ�(keys[0],��,keys[i-1])���򡣱��㷨��
   // ��i���ؼ���keys[i]����RADIX���ӱ�,ʹͬһ�ӱ��м�¼��keys[i]��ͬ��
   // f[0..RADIX-1]��e[0..RADIX-1]�ֱ�ָ����ӱ��е�һ�������һ����¼
   int j,p;
   for(j=0;j<RADIX;++j)
     f[j]=0; // ���ӱ��ʼ��Ϊ�ձ�
   for(p=r[0].next;p;p=r[p].next)
   {
     j=ord(r[p].keys[i]); // ord����¼�е�i���ؼ���ӳ�䵽[0..RADIX-1]
     if(!f[j])
       f[j]=p;
     else
       r[e[j]].next=p;
     e[j]=p; // ��p��ָ�Ľ������j���ӱ���
   }
 }

 int succ(int i)
 { // ���̺���
   return ++i;
 }

 void Collect(SLCell r[],ArrType f,ArrType e)
 { // ���㷨��keys[i]��С����ؽ�f[0..RADIX-1]��ָ���ӱ��������ӳ�
   // һ������e[0..RADIX-1]Ϊ���ӱ��βָ�롣�㷨10.16
   int j,t;
   for(j=0;!f[j];j=succ(j)); // �ҵ�һ���ǿ��ӱ�succΪ���̺���
   r[0].next=f[j];
   t=e[j]; // r[0].nextָ���һ���ǿ��ӱ��е�һ�����
   while(j<RADIX-1)
   {
     for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j)); // ����һ���ǿ��ӱ�
     if(f[j])
     { // ���������ǿ��ӱ�
       r[t].next=f[j];
       t=e[j];
     }
   }
   r[t].next=0; // tָ�����һ���ǿ��ӱ��е����һ�����
 }

 void printl(SLList L)
 { // �����������̬����
   int i=L.r[0].next,j;
   while(i)
   {
     for(j=L.keynum-1;j>=0;j--)
       printf("%c",L.r[i].keys[j]);
     printf(" ");
     i=L.r[i].next;
   }
 }

 void RadixSort(SLList &L)
 { // L�ǲ��þ�̬�����ʾ��˳�����L����������ʹ��L��Ϊ���ؼ���
   // ��С���������̬����L.r[0]Ϊͷ��㡣�㷨10.17
   int i;
   ArrType f,e;
   for(i=0;i<L.recnum;++i)
     L.r[i].next=i+1;
   L.r[L.recnum].next=0; // ��L����Ϊ��̬����
   for(i=0;i<L.keynum;++i)
   { // �����λ�������ζԸ��ؼ��ֽ��з�����ռ�
     Distribute(L.r,i,f,e); // ��i�˷���
     Collect(L.r,f,e); // ��i���ռ�
     printf("��%d���ռ���:\n",i+1);
     printl(L);
     printf("\n");
   }
 }

 void print(SLList L)
 { // ��������������̬����
   int i,j;
   printf("keynum=%d recnum=%d\n",L.keynum,L.recnum);
   for(i=1;i<=L.recnum;i++)
   {
     printf("keys=");
     for(j=L.keynum-1;j>=0;j--)
       printf("%c",L.r[i].keys[j]);
     printf(" otheritems=%d next=%d\n",L.r[i].otheritems,L.r[i].next);
   }
 }

 void Sort(SLList L,int adr[]) // �Ĵ˾�(����)
 { // ���adr[1..L.length]��adr[i]Ϊ��̬����L�ĵ�i����С��¼�����
   int i=1,p=L.r[0].next;
   while(p)
   {
     adr[i++]=p;
     p=L.r[p].next;
   }
 }

 void Rearrange(SLList &L,int adr[]) // �Ĵ˾�(����)
 { // adr������̬����L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼��
   // ���㷨��adr����L.r��ʹ�������㷨10.18(L�������б�)
   int i,j,k;
   for(i=1;i<L.recnum;++i) // �Ĵ˾�(����)
     if(adr[i]!=i)
     {
       j=i;
       L.r[0]=L.r[i]; // �ݴ��¼L.r[i]
       while(adr[j]!=i)
       { // ����L.r[adr[j]]�ļ�¼��λֱ��adr[j]=iΪֹ
	 k=adr[j];
	 L.r[j]=L.r[k];
         adr[j]=j;
         j=k; // ��¼����λ
       }
       L.r[j]=L.r[0];
       adr[j]=j;
     }
 }

 #define N 10
 void main()
 {
   RedType d[N]={{278,1},{109,2},{63,3},{930,4},{589,5},{184,6},{505,7},{269,8},{8,9},{83,10}};
   SLList l;
   int *adr;
   InitList(l,d,N);
   printf("����ǰ(next��û��ֵ):\n");
   print(l);
   RadixSort(l);
   printf("�����(��̬����):\n");
   print(l);
   adr=(int*)malloc((l.recnum)*sizeof(int));
   Sort(l,adr);
   Rearrange(l,adr);
   printf("�����(���ż�¼):\n");
   print(l);
 }
