 // c9-3.h B���Ľ������
 struct Record // ��¼����
 {
   KeyType key; // �ؼ���
   Others others; // ��������(�����̶���)
 };

 typedef struct BTNode
 {
   int keynum; // ����йؼ��ָ����������Ĵ�С
   BTNode *parent; // ָ��˫�׽��
   struct Node // �����������
   {
     KeyType key; // �ؼ�������
     BTNode *ptr; // ����ָ������
     Record *recptr; // ��¼ָ������
   }node[m+1]; // key,recptr��0�ŵ�Ԫδ��
 }BTNode,*BTree; // B������B��������

 struct Result // B���Ĳ��ҽ������
 {
   BTNode *pt; // ָ���ҵ��Ľ��
   int i; // 1..m���ڽ���еĹؼ������
   int tag; // 1:���ҳɹ���O:����ʧ��
 };
