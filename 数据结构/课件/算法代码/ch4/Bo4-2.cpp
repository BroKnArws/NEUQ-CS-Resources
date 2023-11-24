 // bo4-2.cpp �����öѷ���洢�ṹ(��c4-2.h����)�Ļ�������(15��)
 // �����㷨4.1��4.4
 Status StrAssign(HString &T,char *chars)
 { // ����һ����ֵ���ڴ�����chars�Ĵ�T
   int i,j;
   if(T.ch)
     free(T.ch); // �ͷ�Tԭ�пռ�
   i=strlen(chars); // ��chars�ĳ���i
   if(!i)
   { // chars�ĳ���Ϊ0
     T.ch=NULL;
     T.length=0;
   }
   else
   { // chars�ĳ��Ȳ�Ϊ0
     T.ch=(char*)malloc(i*sizeof(char)); // ���䴮�ռ�
     if(!T.ch) // ���䴮�ռ�ʧ��
       exit(OVERFLOW);
     for(j=0;j<i;j++) // ������
       T.ch[j]=chars[j];
     T.length=i;
   }
   return OK;
 }

 Status StrCopy(HString &T,HString S)
 { // ��ʼ����: ��S���ڡ��������: �ɴ�S���Ƶô�T
   int i;
   if(T.ch)
     free(T.ch); // �ͷ�Tԭ�пռ�
   T.ch=(char*)malloc(S.length*sizeof(char)); // ���䴮�ռ�
   if(!T.ch) // ���䴮�ռ�ʧ��
     exit(OVERFLOW);
   for(i=0;i<S.length;i++) // ������
     T.ch[i]=S.ch[i];
   T.length=S.length;
   return OK;
 }

 Status StrEmpty(HString S)
 { // ��ʼ����: ��S���ڡ��������: ��SΪ�մ�,�򷵻�TRUE,���򷵻�FALSE
   if(S.length==0&&S.ch==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(HString S,HString T)
 { // ��S>T,�򷵻�ֵ>0;��S=T,�򷵻�ֵ=0;��S<T,�򷵻�ֵ<0
   int i;
   for(i=0;i<S.length&&i<T.length;++i)
     if(S.ch[i]!=T.ch[i])
       return S.ch[i]-T.ch[i];
   return S.length-T.length;
 }

 int StrLength(HString S)
 { // ����S��Ԫ�ظ���,��Ϊ���ĳ���
   return S.length;
 }

 Status ClearString(HString &S)
 { // ��S��Ϊ�մ�
   if(S.ch)
   {
     free(S.ch);
     S.ch=NULL;
   }
   S.length=0;
   return OK;
 }

 Status Concat(HString &T,HString S1,HString S2)
 { // ��T������S1��S2���Ӷ��ɵ��´�
   int i;
   if(T.ch)
     free(T.ch); // �ͷžɿռ�
   T.length=S1.length+S2.length;
   T.ch=(char *)malloc(T.length*sizeof(char));
   if(!T.ch)
     exit(OVERFLOW);
   for(i=0;i<S1.length;i++)
     T.ch[i]=S1.ch[i];
   for(i=0;i<S2.length;i++)
     T.ch[S1.length+i]=S2.ch[i];
   return OK;
 }

 Status SubString(HString &Sub, HString S,int pos,int len)
 { // ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���
   // ����,1��pos��StrLength(S)��0��len��StrLength(S)-pos+1
   int i;
   if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
     return ERROR;
   if(Sub.ch)
     free(Sub.ch); // �ͷžɿռ�
   if(!len) // ���Ӵ�
   {
     Sub.ch=NULL;
     Sub.length=0;
   }
   else
   { // �����Ӵ�
     Sub.ch=(char*)malloc(len*sizeof(char));
     if(!Sub.ch)
       exit(OVERFLOW);
     for(i=0;i<=len-1;i++)
       Sub.ch[i]=S.ch[pos-1+i];
     Sub.length=len;
   }
   return OK;
 }

 void InitString(HString &T)
 { // ��ʼ��(�����մ�)�ַ���T�����
   T.length=0;
   T.ch=NULL;
 }

 int Index(HString S,HString T,int pos) // �㷨4.1
 { // TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ�,
   // �򷵻ص�һ���������Ӵ���S�е�λ��,���򷵻�0
   int n,m,i;
   HString sub;
   InitString(sub);
   if(pos>0)
   {
     n=StrLength(S);
     m=StrLength(T);
     i=pos;
     while(i<=n-m+1)
     {
       SubString(sub,S,i,m);
       if(StrCompare(sub,T)!=0)
	 ++i;
       else
         return i;
     }
   }
   return 0;
  }

 Status StrInsert(HString &S,int pos,HString T) // �㷨4.4
 { // 1��pos��StrLength(S)+1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
   int i;
   if(pos<1||pos>S.length+1) // pos���Ϸ�
     return ERROR;
   if(T.length) // T�ǿ�,�����·���ռ�,����T
   {
     S.ch=(char*)realloc(S.ch,(S.length+T.length)*sizeof(char));
     if(!S.ch)
       exit(OVERFLOW);
     for(i=S.length-1;i>=pos-1;--i) // Ϊ����T���ڳ�λ��
       S.ch[i+T.length]=S.ch[i];
     for(i=0;i<T.length;i++)
       S.ch[pos-1+i]=T.ch[i]; // ����T
     S.length+=T.length;
   }
   return OK;
 }

 Status StrDelete(HString &S,int pos,int len)
 { // �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
   int i;
   if(S.length<pos+len-1)
     exit(ERROR);
   for(i=pos-1;i<=S.length-len;i++)
     S.ch[i]=S.ch[i+len];
   S.length-=len;
   S.ch=(char*)realloc(S.ch,S.length*sizeof(char));
   return OK;
 }

 Status Replace(HString &S,HString T,HString V)
 { // ��ʼ����: ��S,T��V����,T�Ƿǿմ����˺����봮�Ĵ洢�ṹ�޹أ�
   // �������: ��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
   int i=1; // �Ӵ�S�ĵ�һ���ַ�����Ҵ�T
   if(StrEmpty(T)) // T�ǿմ�
     return ERROR;
   do
   {
     i=Index(S,T,i); // ���iΪ����һ��i֮���ҵ����Ӵ�T��λ��
     if(i) // ��S�д��ڴ�T
     {
       StrDelete(S,i,StrLength(T)); // ɾ���ô�T
       StrInsert(S,i,V); // ��ԭ��T��λ�ò��봮V
       i+=StrLength(V); // �ڲ���Ĵ�V����������Ҵ�T
     }
   }while(i);
   return OK;
 }

 void DestroyString()
 { // �ѷ������͵��ַ����޷�����
 }

 void StrPrint(HString T)
 { // ���T�ַ��������
   int i;
   for(i=0;i<T.length;i++)
     printf("%c",T.ch[i]);
   printf("\n");
 }
