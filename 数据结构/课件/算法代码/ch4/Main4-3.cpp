 // main4-3.cpp ����bo4-3.cpp��������
 char blank='#'; // ȫ�ֱ���,���������
 #include"c1.h"
 #include"c4-3.h"
 #include"bo4-3.cpp"
 void main()
 {
   char *s1="ABCDEFGHI",*s2="12345",*s3="",*s4="asd#tr",*s5="ABCD";
   Status k;
   int pos,len;
   LString t1,t2,t3,t4;
   InitString(t1);
   InitString(t2);
   printf("��ʼ����t1�󣬴�t1�շ�%d(1:�� 0:��) ����=%d\n",StrEmpty(t1),StrLength(t1));
   k=StrAssign(t1,s3);
   if(k==OK)
   {
     printf("��t1Ϊ: ");
     StrPrint(t1);
   }
   else
     printf("����\n"); // �������ɿմ�
   k=StrAssign(t1,s4);
   if(k==OK)
   {
     printf("��t1Ϊ: ");
     StrPrint(t1);
   }
   else
     printf("����\n"); // �������ɺ��б���blank��������ַ��Ĵ�
   k=StrAssign(t1,s1);
   if(k==OK)
   {
     printf("��t1Ϊ: ");
     StrPrint(t1);
   }
   else
     printf("����\n");
   printf("��t1�շ�%d(1:�� 0:��) ����=%d\n",StrEmpty(t1),StrLength(t1));
   StrAssign(t2,s2);
   printf("��t2Ϊ: ");
   StrPrint(t2);
   StrCopy(t3,t1);
   printf("�ɴ�t1�����õ���t3,��t3Ϊ: ");
   StrPrint(t3);
   InitString(t4);
   StrAssign(t4,s5);
   printf("��t4Ϊ: ");
   StrPrint(t4);
   Replace(t3,t4,t2);
   printf("��t2ȡ����t3�е�t4���󣬴�t3Ϊ: ");
   StrPrint(t3);
   ClearString(t1);
   printf("��մ�t1�󣬴�t1�շ�%d(1:�� 0:��) ����=%d\n",StrEmpty(t1),StrLength(t1));
   Concat(t1,t2,t3);
   printf("��t1(=t2+t3)Ϊ: ");
   StrPrint(t1);
   Zip(t1);
   printf("ȥ������Ҫ��ռλ���󣬴�t1Ϊ: ");
   StrPrint(t1);
   pos=Index(t1,t3,1);
   printf("pos=%d\n",pos);
   printf("�ڴ�t1�ĵ�pos���ַ�֮ǰ���봮t2��������pos: ");
   scanf("%d",&pos);
   k=StrInsert(t1,pos,t2);
   if(k)
   {
     printf("���봮t2�󣬴�t1Ϊ: ");
     StrPrint(t1);
   }
   else
     printf("����ʧ�ܣ�\n");
   printf("���t1�ĵ�pos���ַ���,����Ϊlen���Ӵ�t2,������pos,len: ");
   scanf("%d,%d",&pos,&len);
   SubString(t2,t1,pos,len);
   printf("��t2Ϊ: ");
   StrPrint(t2);
   printf("StrCompare(t1,t2)=%d\n",StrCompare(t1,t2));
   printf("ɾ����t1�е����ַ������ӵ�pos���ַ���ɾ��len���ַ���������pos,len��");
   scanf("%d,%d",&pos,&len);
   k=StrDelete(t1,pos,len);
   if(k)
   {
     printf("�ӵ�%dλ����ɾ��%d��Ԫ�غ�t1Ϊ:",pos,len);
     StrPrint(t1);
   }
 }