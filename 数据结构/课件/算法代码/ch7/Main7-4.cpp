 // main7-4.cpp ����bo7-4.cpp��������
 #include"c1.h"
 #define MAX_NAME 3 // �����ַ�������󳤶�+1
 #define MAX_INFO 80 // �����Ϣ�ַ�������󳤶�+1
 typedef char InfoType;
 typedef char VertexType[MAX_NAME]; // �ַ�������
 #include"c7-4.h"
 #include"bo7-4.cpp"
 Status visit(VertexType v)
 {
   printf("%s ",v);
   return OK;
 }

 void main()
 {
   int k,n;
   AMLGraph g;
   VertexType v1,v2;
   CreateGraph(g);
   Display(g);
   printf("�޸Ķ����ֵ��������ԭֵ ��ֵ: ");
   scanf("%s%s",v1,v2);
   PutVex(g,v1,v2);
   printf("�����¶��㣬�����붥���ֵ: ");
   scanf("%s",v1);
   InsertVex(g,v1);
   printf("�������¶����йصıߣ����������: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("��������һ�����ֵ: ");
     scanf("%s",v2);
     InsertArc(g,v1,v2);
   }
   Display(g);
   printf("������������Ľ��:\n");
   DFSTraverse(g,visit);
   printf("������������Ľ��:\n");
   BFSTraverse(g,visit);
   DestroyGraph(g);
 }