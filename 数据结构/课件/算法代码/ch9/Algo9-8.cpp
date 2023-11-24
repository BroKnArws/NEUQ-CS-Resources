 // algo9-8.cpp ����bo9-6.cpp�ĳ���
 #include"c1.h"
 #define N 16 // ����Ԫ�ظ���
 #define LENGTH 27 // ��������+1(��дӢ����ĸ)
 struct Others // ��¼����������
 {
   int ord;
 };
 #define Nil ' ' // ���������Ϊ�ո�(��̿��鲻ͬ)
 #include"c9-5.h"
 #include"bo9-6.cpp"

 Status pr(Record *r)
 {
   printf("(%s,%d)",r->key.ch,r->others.ord);
   return OK;
 }

 void main()
 {
   TrieTree t;
   int i;
   char s[MAXKEYLEN+1];
   KeysType k;
   Record *p;
   Record r[N]={{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
                {{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
                {{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
                {{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}};
   // ����Ԫ��(�Խ̿���ʽ9-24Ϊ��)
   InitDSTable(t);
   for(i=0;i<N;i++)
   {
     r[i].key.num=strlen(r[i].key.ch)+1;
     r[i].key.ch[r[i].key.num]=Nil; // �ڹؼ��ַ������ӽ�����
     p=SearchTrie(t,r[i].key);
     if(!p)
       InsertTrie(t,&r[i]);
   }
   printf("���ؼ��ַ�����˳�����Trie��(����):\n");
   TraverseDSTable(t,pr);
   printf("\n����������Ҽ�¼�Ĺؼ��ַ���: ");
   scanf("%s",s);
   k.num=strlen(s)+1;
   strcpy(k.ch,s);
   k.ch[k.num]=Nil; // �ڹؼ��ַ������ӽ�����
   p=SearchTrie(t,k);
   if(p)
     pr(p);
   else
     printf("û�ҵ�");
   printf("\n");
   DestroyDSTable(t);
 }
