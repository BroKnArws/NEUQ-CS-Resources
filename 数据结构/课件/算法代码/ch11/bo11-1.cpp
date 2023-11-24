 // bo11-1.cpp k·ƽ��鲢�ĺ���
 FILE *fp[k+1]; // k+1���ļ�ָ��(fp[k]Ϊ���ļ�ָ��)��ȫ�ֱ���
 typedef int LoserTree[k]; // ����������ȫ�������Ҳ���Ҷ�ӣ��ɲ���˳��洢�ṹ
 typedef RedType ExNode,External[k+1]; // ����,�иı�
 External b; // ȫ�ֱ���
 #define MINKEY INT_MIN
 #define MAXKEY INT_MAX

 void input(int i,KeyType &a)
 { // �ӵ�i���ļ�(��i���鲢��)����öε�ǰ��1����¼�Ĺؼ��ֵ�����
   fread(&a,sizeof(KeyType),1,fp[i]);
 }

 void output(int i)
 { // ����i���ļ�(��i���鲢��)�е�ǰ�ļ�¼д������鲢��
   ExNode a;
   a.key=b[i].key; // ��ǰ��¼�Ĺؼ����Ѷ���b[i].key��
   fread(&a.otherinfo,sizeof(InfoType),1,fp[i]);
   fwrite(&a,sizeof(ExNode),1,fp[k]);
 }

 void Adjust(LoserTree ls,int s)
 { // �ش�Ҷ�ӽ��b[s]�������ls[0]��·���������������㷨11.2
   int i,t;
   t=(s+k)/2; // ls[t]��b[s]��˫�׽��
   while(t>0)
   {
     if(b[s].key>b[ls[t]].key)
     {
       i=s;
       s=ls[t]; // sָʾ�µ�ʤ��
       ls[t]=i;
     }
     t=t/2;
   }
   ls[0]=s;
 }

 void CreateLoserTree(LoserTree ls)
 { // ��֪b[0]��b[k-1]Ϊ��ȫ������ls��Ҷ�ӽ�㣬����k���ؼ��֣��ش�Ҷ��
   // ������k��·����ls������Ϊ���������㷨11.3
   int i;
   b[k].key=MINKEY;
   for(i=0;i<k;++i)
     ls[i]=k; // ����ls�С����ߡ��ĳ�ֵ
   for(i=k-1;i>=0;--i) // ���δ�b[k-1]��b[k-2]������b[0]������������
     Adjust(ls,i);
 }

 void K_Merge(LoserTree ls,External b)
 { // ���ð�����ls����Ŵ�0��k-1��k������鲢���еļ�¼�鲢������鲢�Ρ�
   // b[0]��b[k-1]Ϊ�������ϵ�k��Ҷ�ӽ�㣬�ֱ���k������鲢���е�ǰ
   // ��¼�Ĺؼ��֡��㷨11.1
   int i,q;
   for(i=0;i<k;++i) // �ֱ��k������鲢�ζ��˸öε�ǰ��һ����¼�Ĺؼ��ֵ�����
     input(i,b[i].key);
   CreateLoserTree(ls); // ��������ls��ѡ����С�ؼ���Ϊb[ls[0]].key
   while(b[ls[0]].key!=MAXKEY)
   {
     q=ls[0]; // qָʾ��ǰ��С�ؼ������ڹ鲢��
     output(q); // �����Ϊq�Ĺ鲢���е�ǰ���ؼ���Ϊb[q].key���ļ�¼д������鲢��
     input(q,b[q].key); // �ӱ��Ϊq������鲢���ж�����һ����¼�Ĺؼ���
     Adjust(ls,q); // ������������ѡ���µ���С�ؼ���
   }
   output(ls[0]); // �������ؼ���MAXKEY�ļ�¼д������鲢��
 }
