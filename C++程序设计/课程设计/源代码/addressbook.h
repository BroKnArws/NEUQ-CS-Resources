#include"pch.h"


class address_book                                   //����ͨѶ¼�� 
{
protected:
	int number;                                      //��� 
	char name[20];                                   //���� 
	char sex[20];                                    //�Ա� 
	char mailing_address[50];                        //ͨѶ��ַ 
	char email_address[50];                          //�����ַ 
	char phone_number[50];                           //�绰���� 
public:
	void book_add(int &book_num);                    //��ӹ��� 
	static void data_display(int book_num);          //ȫ��չʾ����
	static void book_inquire(int book_num);          //��ѯ����
	static void book_delete(int &book_num);          //ɾ������
	static void data_edit(int &book_num);            //�༭����
	static void book_save(int book_num);             //���湦��
	static void book_read(int &book_num);            //��ȡ����
	bool book_check(address_book *book);             //��ʽ���
}book[100];