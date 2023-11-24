 // main6-1.cpp ����bo6-1.cpp��������������������ѡ����������Ϊchar��int
 //#define CHAR 1 // �ַ���
 #define CHAR 0 // ����(����ѡһ)
 #include"c1.h"
 #if CHAR
   typedef char TElemType;
   TElemType Nil=' '; // ���ַ����Կո��Ϊ��
 #else
   typedef int TElemType;
   TElemType Nil=0; // ��������0Ϊ��
 #endif
 #include"c6-1.h"
 #include"bo6-1.cpp"

 Status visit(TElemType e)
 {
   cout<<e<<' ';
   return OK;
 }

 void main()
 {
   Status i;
   int j;
   position p;
   TElemType e;
   SqBiTree T,s;
   InitBiTree(T);
   CreateBiTree(T);
   cout<<"������������,���շ�"<<BiTreeEmpty(T)<<"(1:�� 0:��) �������="<<BiTreeDepth(T)<<endl;
   i=Root(T,e);
   if(i)
     cout<<"�������ĸ�Ϊ��"<<e<<endl;
   else
     cout<<"���գ��޸�"<<endl;
   cout<<"�������������:"<<endl;
   LevelOrderTraverse(T,visit);
   cout<<"�������������:"<<endl;
   InOrderTraverse(T,visit);
   cout<<"�������������:"<<endl;
   PostOrderTraverse(T,visit);
   cout<<"��������޸Ľ��Ĳ�� �������: ";
   cin>>p.level>>p.order;
   e=Value(T,p);
   cout<<"���޸Ľ���ԭֵΪ"<<e<<"��������ֵ: ";
   cin>>e;
   Assign(T,p,e);
   cout<<"�������������:"<<endl;
   PreOrderTraverse(T,visit);
   cout<<"���"<<e<<"��˫��Ϊ"<<Parent(T,e)<<",���Һ��ӷֱ�Ϊ";
   cout<<LeftChild(T,e)<<","<<RightChild(T,e)<<",�����ֱֵܷ�Ϊ";
   cout<<LeftSibling(T,e)<<","<<RightSibling(T,e)<<endl;
   InitBiTree(s);
   cout<<"����������Ϊ�յ���s:"<<endl;
   CreateBiTree(s);
   cout<<"��s�嵽��T��,��������T����s��˫�׽�� sΪ��(0)����(1)����: ";
   cin>>e>>j;
   InsertChild(T,e,j,s);
   Print(T);
   cout<<"ɾ������,�������ɾ�����������Ĳ�� ������� ��(0)����(1)����: ";
   cin>>p.level>>p.order>>j;
   DeleteChild(T,p,j);
   Print(T);
   ClearBiTree(T);
   cout<<"�����������,���շ�"<<BiTreeEmpty(T)<<"(1:�� 0:��) �������="<<BiTreeDepth(T)<<endl;
   i=Root(T,e);
   if(i)
     cout<<"�������ĸ�Ϊ��"<<e<<endl;
   else
     cout<<"���գ��޸�"<<endl;
 }