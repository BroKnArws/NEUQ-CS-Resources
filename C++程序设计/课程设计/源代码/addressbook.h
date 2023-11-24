#include"pch.h"


class address_book                                   //定义通讯录类 
{
protected:
	int number;                                      //编号 
	char name[20];                                   //姓名 
	char sex[20];                                    //性别 
	char mailing_address[50];                        //通讯地址 
	char email_address[50];                          //邮箱地址 
	char phone_number[50];                           //电话号码 
public:
	void book_add(int &book_num);                    //添加功能 
	static void data_display(int book_num);          //全部展示功能
	static void book_inquire(int book_num);          //查询功能
	static void book_delete(int &book_num);          //删除功能
	static void data_edit(int &book_num);            //编辑功能
	static void book_save(int book_num);             //保存功能
	static void book_read(int &book_num);            //读取功能
	bool book_check(address_book *book);             //格式检查
}book[100];