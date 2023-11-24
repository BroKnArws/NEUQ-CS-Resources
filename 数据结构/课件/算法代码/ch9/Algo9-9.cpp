 // algo9-9.cpp ����bo9-7.cpp�ĳ���
 #include"c1.h"
 #define NULLKEY 0 // 0Ϊ�޼�¼��־
 #define N 10 // ����Ԫ�ظ���
 typedef int KeyType; // ��ؼ�����Ϊ����
 struct ElemType // ����Ԫ������
 {
   KeyType key;
   int ord;
 };

 #include"c9.h"
 #include"c9-6.h"
 #include"bo9-7.cpp"

 void print(int p,ElemType r)
 {
   printf("address=%d (%d,%d)\n",p,r.key,r.ord);
 }

 void main()
 {
   ElemType r[N]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
   HashTable h;
   int i,p;
   Status j;
   KeyType k;
   InitHashTable(h);
   for(i=0;i<N-1;i++)
   { // ����ǰN-1����¼
     j=InsertHash(h,r[i]);
     if(j==DUPLICATE)
       printf("�������йؼ���Ϊ%d�ļ�¼���޷��ٲ����¼(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
   }
   printf("����ϣ��ַ��˳�������ϣ��:\n");
   TraverseHash(h,print);
   printf("����������Ҽ�¼�Ĺؼ���: ");
   scanf("%d",&k);
   j=Find(h,k,p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("û�ҵ�\n");
   j=InsertHash(h,r[i]); // �����N����¼
   if(j==ERROR) // �ؽ���ϣ��
     j=InsertHash(h,r[i]); // �ؽ���ϣ������²���
   printf("����ϣ��ַ��˳������ؽ���Ĺ�ϣ��:\n");
   TraverseHash(h,print);
   printf("����������Ҽ�¼�Ĺؼ���: ");
   scanf("%d",&k);
   j=Find(h,k,p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("û�ҵ�\n");
   DestroyHashTable(h);
 }
