 // main7-1.cpp ����bo7-1.cpp��������
 #include"c1.h"
 #define MAX_NAME 5 // �����ַ�������󳤶�+1
 #define MAX_INFO 20 // �����Ϣ�ַ�������󳤶�+1
 typedef int VRType;
 typedef char InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h"
 #include"bo7-1.cpp"

 Status visit(VertexType i)
 {
   printf("%s ",i);
   return OK;
 }

 void main()
 {
   int i,j,k,n;
   VertexType v1,v2;
   MGraph g;
   CreateFAG(g);
   Display(g);
   printf("�޸Ķ����ֵ��������ԭֵ ��ֵ: ");
   scanf("%s%s",v1,v2);
   PutVex(g,v1,v2);
   printf("������������Ľ��:\n");
   DFSTraverse(g,visit);
   printf("������������Ľ��:\n");
   BFSTraverse(g,visit);
   printf("ɾ��һ���߻򻡣��������ɾ���߻򻡵Ļ�β ��ͷ��");
   scanf("%s%s",v1,v2);
   DeleteArc(g,v1,v2);
   Display(g);
   DestroyGraph(g);
   printf("��˳��ѡ������ͼ,������,����ͼ,������\n");
   for(i=0;i<4;i++) // ��֤4�����
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
