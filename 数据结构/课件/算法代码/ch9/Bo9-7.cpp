 // bo9-7.cpp ��ϣ�����Ļ�������
 Status InitHashTable(HashTable &H)
 { // �������: ����һ���յĹ�ϣ��
   int i;
   H.count=0; // ��ǰԪ�ظ���Ϊ0
   H.sizeindex=0; // ��ʼ�洢����Ϊhashsize[0]
   m=hashsize[0];
   H.elem=(ElemType*)malloc(m*sizeof(ElemType));
   if(!H.elem)
     exit(OVERFLOW); // �洢����ʧ��
   for(i=0;i<m;i++)
     H.elem[i].key=NULLKEY; // δ���¼�ı�־
   return OK;
 }

 void DestroyHashTable(HashTable &H)
 { // ��ʼ����: ��ϣ��H���ڡ��������: ���ٹ�ϣ��H
   free(H.elem);
   H.elem=NULL;
   H.count=0;
   H.sizeindex=0;
 }

 unsigned Hash(KeyType K)
 { // һ���򵥵Ĺ�ϣ����(mΪ����ȫ�ֱ���)
   return K%m;
 }

 void collision(int &p,int d) // ����̽����ɢ��
 { // ���Ŷ�ַ�������ͻ
   p=(p+d)%m;
 }

 Status SearchHash(HashTable H,KeyType K,int &p,int &c)
 { // �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ��������
   // Ԫ���ڱ���λ��,������SUCCESS;����,��pָʾ����λ��,������UNSUCCESS
   // c���ԼƳ�ͻ���������ֵ���㣬���������ʱ�ο����㷨9.17
   p=Hash(K); // ��ù�ϣ��ַ
   while(H.elem[p].key!=NULLKEY&&!EQ(K,H.elem[p].key))
   { // ��λ�������м�¼�����ҹؼ��ֲ����
     c++;
     if(c<m)
       collision(p,c); // �����һ̽���ַp
     else
       break;
   }
   if EQ(K,H.elem[p].key)
     return SUCCESS; // ���ҳɹ���p���ش�������Ԫ��λ��
   else
     return UNSUCCESS; // ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)��p���ص��ǲ���λ��
 }

 Status InsertHash(HashTable &,ElemType); // �Ժ���������
 void RecreateHashTable(HashTable &H) // �ؽ���ϣ��
 { // �ؽ���ϣ��
   int i,count=H.count;
   ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
   p=elem;
   printf("�ؽ���ϣ��\n");
   for(i=0;i<m;i++) // ����ԭ�е����ݵ�elem��
     if((H.elem+i)->key!=NULLKEY) // �õ�Ԫ������
       *p++=*(H.elem+i);
   H.count=0;
   H.sizeindex++; // ����洢����
   m=hashsize[H.sizeindex];
   p=(ElemType*)realloc(H.elem,m*sizeof(ElemType));
   if(!p)
     exit(OVERFLOW); // �洢����ʧ��
   H.elem=p;
   for(i=0;i<m;i++)
     H.elem[i].key=NULLKEY; // δ���¼�ı�־(��ʼ��)
   for(p=elem;p<elem+count;p++) // ��ԭ�е����ݰ����µı����뵽�ؽ��Ĺ�ϣ����
     InsertHash(H,*p);
 }

 Status InsertHash(HashTable &H,ElemType e)
 { // ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������OK��
   // ����ͻ�����������ؽ���ϣ���㷨9.18
   int c,p;
   c=0;
   if(SearchHash(H,e.key,p,c)) // ����������e����ͬ�ؼ��ֵ�Ԫ��
     return DUPLICATE;
   else if(c<hashsize[H.sizeindex]/2) // ��ͻ����cδ�ﵽ����,(c�ķ�ֵ�ɵ�)
   { // ����e
     H.elem[p]=e;
     ++H.count;
     return OK;
   }
   else
     RecreateHashTable(H); // �ؽ���ϣ��
   return ERROR;
 }

 void TraverseHash(HashTable H,void(*Vi)(int,ElemType))
 { // ����ϣ��ַ��˳�������ϣ��
   printf("��ϣ��ַ0��%d\n",m-1);
   for(int i=0;i<m;i++)
     if(H.elem[i].key!=NULLKEY) // ������
       Vi(i,H.elem[i]);
 }

 Status Find(HashTable H,KeyType K,int &p)
 { // �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ��������
   // Ԫ���ڱ���λ��,������SUCCESS;����,����UNSUCCESS
   int c=0;
   p=Hash(K); // ��ù�ϣ��ַ
   while(H.elem[p].key!=NULLKEY&&!EQ(K,H.elem[p].key))
   { // ��λ�������м�¼�����ҹؼ��ֲ����
     c++;
     if(c<m)
       collision(p,c); // �����һ̽���ַp
     else
     return UNSUCCESS; // ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)
   }
   if EQ(K,H.elem[p].key)
     return SUCCESS; // ���ҳɹ���p���ش�������Ԫ��λ��
   else
     return UNSUCCESS; // ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)
 }
