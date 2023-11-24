 // main7-2.cpp ����bo7-2.cpp��������
 #include"c1.h"
 #define MAX_NAME 3 // �����ַ�������󳤶�+1
 typedef int InfoType; // �������Ȩֵ
 typedef char VertexType[MAX_NAME]; // �ַ�������
 #include"c7-2.h"
 #include"bo7-2.cpp"

 void print(char *i)
 {
   printf("%s ",i);
 }

 void main()
 {
   int i,j,k,n;
   ALGraph g;
   VertexType v1,v2;
   printf("��ѡ������ͼ\n");
   CreateGraph(g);
   Display(g);
   printf("ɾ��һ���߻򻡣��������ɾ���߻򻡵Ļ�β ��ͷ��");
   scanf("%s%s",v1,v2);
   DeleteArc(g,v1,v2);
   printf("�޸Ķ����ֵ��������ԭֵ ��ֵ: ");
   scanf("%s%s",v1,v2);
   PutVex(g,v1,v2);
   printf("�����¶��㣬�����붥���ֵ: ");
   scanf("%s",v1);
   InsertVex(g,v1);
   printf("�������¶����йصĻ���ߣ������뻡�����: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("��������һ�����ֵ: ");
     scanf("%s",v2);
     printf("��������ͼ����������һ����ķ���(0:��ͷ 1:��β): ");
     scanf("%d",&j);
     if(j)
       InsertArc(g,v2,v1);
     else
       InsertArc(g,v1,v2);
   }
   Display(g);
   printf("ɾ�����㼰��صĻ���ߣ������붥���ֵ: ");
   scanf("%s",v1);
   DeleteVex(g,v1);
   Display(g);
   printf("������������Ľ��:\n");
   DFSTraverse(g,print);
   printf("������������Ľ��:\n");
   BFSTraverse(g,print);
   DestroyGraph(g);
   printf("��˳��ѡ��������,����ͼ,������\n");
   for(i=0;i<3;i++) // ��֤����3�����
   {
     CreateGraph(g);
     Display(g);
     printf("�����¶��㣬�����붥���ֵ: ");
     scanf("%s",v1);
     InsertVex(g,v1);
     printf("�������¶����йصĻ���ߣ������뻡�����: ");
     scanf("%d",&n);
     for(k=0;k<n;k++)
     {
       printf("��������һ�����ֵ: ");
       scanf("%s",v2);
       if(g.kind<=1) // ����
       {
         printf("��������ͼ��������������һ����ķ���(0:��ͷ 1:��β): ");
         scanf("%d",&j);
         if(j)
           InsertArc(g,v2,v1);
         else
           InsertArc(g,v1,v2);
       }
       else // ����
         InsertArc(g,v1,v2);
     }
     Display(g);
     printf("ɾ�����㼰��صĻ���ߣ������붥���ֵ: ");
     scanf("%s",v1);
     DeleteVex(g,v1);
     Display(g);
     DestroyGraph(g);
   }
 }
