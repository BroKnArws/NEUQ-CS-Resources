 // bo4-1.cpp �����ö���˳��洢�ṹ(��c4-1.h����)�Ļ�������(14��)
 // SString�����飬�ʲ����������͡��˻������������㷨4.2,4.3,4.5
 Status StrAssign(SString T,char *chars)
 { // ����һ����ֵ����chars�Ĵ�T
   int i;
   if(strlen(chars)>MAXSTRLEN)
     return ERROR;
   else
   {
     T[0]=strlen(chars);
     for(i=1;i<=T[0];i++)
       T[i]=*(chars+i-1);
     return OK;
   }
 }

 Status StrCopy(SString T,SString S)
 { // �ɴ�S���Ƶô�T
   int i;
   for(i=0;i<=S[0];i++)
     T[i]=S[i];
   return OK;
 }

 Status StrEmpty(SString S)
 { // ��SΪ�մ�,�򷵻�TRUE,���򷵻�FALSE
   if(S[0]==0)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(SString S,SString T)
 { // ��ʼ����: ��S��T����
   // �������: ��S>T,�򷵻�ֵ>0;��S=T,�򷵻�ֵ=0;��S<T,�򷵻�ֵ<0
   int i;
   for(i=1;i<=S[0]&&i<=T[0];++i)
     if(S[i]!=T[i])
       return S[i]-T[i];
   return S[0]-T[0];
 }

 int StrLength(SString S)
 { // ���ش���Ԫ�ظ���
   return S[0];
 }

 Status ClearString(SString S)
 { // ��ʼ����:��S���ڡ��������:��S��Ϊ�մ�
   S[0]=0;// ���Ϊ��
   return OK;
 }

 Status Concat(SString T,SString S1,SString S2) // �㷨4.2��
 { // ��T����S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�TRUE������FALSE
   int i;
   if(S1[0]+S2[0]<=MAXSTRLEN)
   { // δ�ض�
     for(i=1;i<=S1[0];i++)
       T[i]=S1[i];
     for(i=1;i<=S2[0];i++)
       T[S1[0]+i]=S2[i];
     T[0]=S1[0]+S2[0];
     return TRUE;
   }
   else
   { // �ض�S2
     for(i=1;i<=S1[0];i++)
       T[i]=S1[i];
     for(i=1;i<=MAXSTRLEN-S1[0];i++)
       T[S1[0]+i]=S2[i];
     T[0]=MAXSTRLEN;
     return FALSE;
   }
 }

 Status SubString(SString Sub,SString S,int pos,int len)
 { // ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ����㷨4.3
   int i;
   if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
     return ERROR;
   for(i=1;i<=len;i++)
     Sub[i]=S[pos+i-1];
   Sub[0]=len;
   return OK;
 }

 int Index(SString S,SString T,int pos)
 { // �����Ӵ�T������S�е�pos���ַ�֮���λ�á���������,����ֵΪ0��
   // ����,T�ǿ�,1��pos��StrLength(S)���㷨4.5
   int i,j;
   if(1<=pos&&pos<=S[0])
   {
     i=pos;
     j=1;
     while(i<=S[0]&&j<=T[0])
       if(S[i]==T[j]) // �����ȽϺ���ַ�
       {
         ++i;
         ++j;
       }
       else // ָ��������¿�ʼƥ��
       {
	 i=i-j+2;
         j=1;
       }
     if(j>T[0])
       return i-T[0];
     else
       return 0;
   }
   else
     return 0;
 }

 Status StrInsert(SString S,int pos,SString T)
 { // ��ʼ����: ��S��T����,1��pos��StrLength(S)+1
   // �������: �ڴ�S�ĵ�pos���ַ�֮ǰ���봮T����ȫ���뷵��TRUE,���ֲ��뷵��FALSE
   int i;
   if(pos<1||pos>S[0]+1)
     return ERROR;
   if(S[0]+T[0]<=MAXSTRLEN)
   { // ��ȫ����
     for(i=S[0];i>=pos;i--)
       S[i+T[0]]=S[i];
     for(i=pos;i<pos+T[0];i++)
       S[i]=T[i-pos+1];
     S[0]=S[0]+T[0];
     return TRUE;
   }
   else
   { // ���ֲ���
     for(i=MAXSTRLEN;i<=pos;i--)
       S[i]=S[i-T[0]];
     for(i=pos;i<pos+T[0];i++)
       S[i]=T[i-pos+1];
     S[0]=MAXSTRLEN;
     return FALSE;
   }
 }

 Status StrDelete(SString S,int pos,int len)
 { // ��ʼ����: ��S����,1��pos��StrLength(S)-len+1
   // �������: �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
   int i;
   if(pos<1||pos>S[0]-len+1||len<0)
     return ERROR;
   for(i=pos+len;i<=S[0];i++)
     S[i-len]=S[i];
   S[0]-=len;
   return OK;
 }

 Status Replace(SString S,SString T,SString V)
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
 { // ����SString�Ƕ�������,�޷�����
 }

 void StrPrint(SString T)
 { // ����ַ���T�����
   int i;
   for(i=1;i<=T[0];i++)
     printf("%c",T[i]);
   printf("\n");
 }
