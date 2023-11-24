 // bo9-1.cpp ��̬���ұ�(˳���������)�Ļ�������(7��)
 Status Creat_Seq(SSTable &ST,int n)
 { // �������: ����һ����n������Ԫ�صľ�̬˳����ұ�ST(��������ȫ������r)
   int i;
   ST.elem=(ElemType*)calloc(n+1,sizeof(ElemType)); // ��̬����n������Ԫ�ؿռ�(0�ŵ�Ԫ����)
   if(!ST.elem)
     return ERROR;
   for(i=1;i<=n;i++)
     *(ST.elem+i)=r[i-1]; // ��ȫ������r��ֵ���θ���ST
   ST.length=n;
   return OK;
 }

 void Ascend(SSTable &ST)
 { // �ؽ���̬���ұ�Ϊ���ؼ��ַǽ�������
   int i,j,k;
   for(i=1;i<ST.length;i++)
   {
     k=i;
     ST.elem[0]=ST.elem[i]; // ���Ƚ�ֵ��[0]��Ԫ
     for(j=i+1;j<=ST.length;j++)
       if LT(ST.elem[j].key,ST.elem[0].key)
       {
         k=j;
         ST.elem[0]=ST.elem[j];
       }
     if(k!=i) // �и�С��ֵ�򽻻�
     {
       ST.elem[k]=ST.elem[i];
       ST.elem[i]=ST.elem[0];
     }
   }
 }

 Status Creat_Ord(SSTable &ST,int n)
 { // �������: ����һ����n������Ԫ�صľ�̬���ؼ��ַǽ�����ұ�ST
   // ��������ȫ������r
   Status f;
   f=Creat_Seq(ST,n);
   if(f)
     Ascend(ST);
   return f;
 }

 Status Destroy(SSTable &ST)
 { // ��ʼ����: ��̬���ұ�ST���ڡ��������: ���ٱ�ST
   free(ST.elem);
   ST.elem=NULL;
   ST.length=0;
   return OK;
 }

 int Search_Seq(SSTable ST,KeyType key)
 { // ��˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ
   // ��Ԫ���ڱ��е�λ�ã�����Ϊ0���㷨9.1
   int i;
   ST.elem[0].key=key; // �ڱ�
   for(i=ST.length;!EQ(ST.elem[i].key,key);--i); // �Ӻ���ǰ��
   return i; // �Ҳ���ʱ��iΪ0
 }

 int Search_Bin(SSTable ST,KeyType key)
 { // �������ST���۰������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ
   // ��Ԫ���ڱ��е�λ�ã�����Ϊ0���㷨9.2
   int low,high,mid;
   low=1; // �������ֵ
   high=ST.length;
   while(low<=high)
   {
     mid=(low+high)/2;
     if EQ(key,ST.elem[mid].key)  // �ҵ�����Ԫ��
       return mid;
     else if LT(key,ST.elem[mid].key)
       high=mid-1; // ������ǰ��������в���
     else
       low=mid+1; // �����ں��������в���
   }
   return 0; // ˳����в����ڴ���Ԫ��
 }

 Status Traverse(SSTable ST,void(*Visit)(ElemType))
 { // ��ʼ����: ��̬���ұ�ST���ڣ�Visit()�Ƕ�Ԫ�ز�����Ӧ�ú���
   // �������: ��˳���ST��ÿ��Ԫ�ص��ú���Visit()һ���ҽ�һ�Ρ�
   // һ��Visit()ʧ�ܣ������ʧ��
   ElemType *p;
   int i;
   p=++ST.elem; // pָ���һ��Ԫ��
   for(i=1;i<=ST.length;i++)
     Visit(*p++);
   return OK;
 }
