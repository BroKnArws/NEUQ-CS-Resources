#include"pch.h"
#include <iostream> 
#include <string> 
#include<iomanip>
#include<fstream>
#include<windows.h>
#include"addressbook.h"
using namespace std;


void menu_show()                                                             //菜单展示
{

	cout << "+---------------------------+    ┌-──────────────────┐\n";
	cout << "|                           |    │ 1. 添加通讯录     │\n";
	cout << "|         欢迎使用          |    │ 2. 查询通讯录信息 │\n";
	cout << "|                           |    │ 3. 查询全部通讯录 │\n";
	cout << "|                           |    │ 4. 删除指定记录   │\n";
	cout << "|                           |    │ 5. 编辑指定记录   │\n";
	cout << "|      通讯录 管理系统      |    │ 6. 保存通讯录     │\n";
	cout << "|                           |    │ 7. 读取通讯录     │\n";
	cout << "|                           |    │ 8. 退出系统       │\n";
	cout << "+---------------------------+    └-──────────────────┘\n";
	cout << "请您输入选项" << endl;
}

bool address_book::book_check(address_book *book)   //格式检查
{
	bool name, sex, email_address, flag = true;
	name = sex = true;
	email_address = false;
	char *p = &book->name[0];
	while (*p != '\0')
	{
		if (*p >= '0'&&*p <= '9')
		{
			name = false;
			break;
		}
		p++;
	}
	string p2 = book->sex;                           //由于1个汉字占2个字节，因此需要转换为string类才能识别。
	if (p2 != "男" && p2 != "女")
	{
		sex = false;
	}
	p = &book->email_address[0];
	while (*p != '\0')
	{
		if (*p == '@')
		{
			email_address = true;
			break;
		}
		p++;
	}
	if (!name)                                        //统计错误的个数，一起输出。
	{
		cout << "您输入的 姓名 可能不符合格式（应为汉字或英文组合）；" << endl;
		flag = false;
	}
	if (!sex)
	{
		cout << "您输入的 性别 可能不符合格式（应为男或女）；" << endl;
		flag = false;
	}
	if (!email_address)
	{
		cout << "您输入的 电子邮箱 可能不符合格式（应为xxx@xxx.com）；" << endl;
		flag = false;
	}
	if (!flag)
	{
		cout << "请按 任意键 重新输入:" << endl;
		return false;
	}
	else
	{
		return true;
	}

}
void Pseudo_save(string sl)                          //进度条动画
{
	int a, b;
	cout << "正在" << sl << "中……";
	cout << endl;
	for (b = 1; b <= 53; b++)
	{
		cout << "=";
	}
	for (a = 1; a <= 50; a++)
	{
		cout << "\r";                                //转至本行首位
		for (b = 1; b <= a; b++)
		{
			cout << ">";
		}
		cout.width(3);                              //设置输出宽度3
		cout << 2 * a << "%";                       //百分比号
		Sleep(35);                                  //设置时间
	}
	cout << endl;
	cout << sl << "成功！" << endl;
}

void address_book::book_save(int book_num)                      //储存功能
{
	if (book_num == 1)
	{
		cout << "通讯录为空，无法保存。" << endl;
	}
	else
	{
		ofstream outfile("addressbook.txt");                    //保存到addressbook.txt
		if (!outfile)
		{
			cout << "文件路径错误或文件不存在。" << endl;
		}
		else
		{
			for (int n = 1; n <= book_num - 1; n++)
			{
				outfile.write((char *)&book[n], sizeof(book[n]));   //保存一次指针后移sizeof(book[n])个字节。
			}
			Pseudo_save("保存");
			outfile.close();
		}
	}
	system("pause");
	system("cls");
}

void address_book::book_read(int &book_num)
{
	int n = 1;
	ifstream infile("addressbook.txt");                         //保存到addressbook.txt
	if (!infile)
	{
		cout << "文件路径错误或文件不存在。" << endl;
	}
	else
	{
		while (!(infile.eof()))
		{
			infile.read((char *)&book[n], sizeof(book[n]));
			n++;
		}
		book_num = n - 1;                          //重新确定book_num的个数，并使下标移至最后一个元素以后
		Pseudo_save("读取");
		infile.close();

	}
	system("pause");
	system("cls");
}


void address_book::book_add(int &book_num)                              //添加功能
{
	bool judge = 1;
	do                                                                 //如果用户不停止输入重复编号，则一直要求输入，直到编号不再重复为止。                    
	{
		cout << "请输入编号： " << endl;
		while (!(cin >> number))                                       //如果输入的不符合数据类型要求，就会返回0. 本句即输入错误时执行以下语句。
		{
			cout << "输入格式有误(应为数字），请重新输入： " << endl;
			cin.clear();                                               //与下句同用方可去掉缓冲区。
			cin.sync();                                                //清除缓冲区，避免无限循环。
			while (cin.get() != '\n')                                  //即输入内容，一直到遇到回车时停止，再将该语句送回前面判断。
			{
				continue;                                              //如果不设这句，会导致不断读取缓冲区数据，无限循环。
			}
		}
		for (int n = 0; n <= book_num - 1; n++)                        //book[0].number可忽略不计
		{
			if (book[n].number == number)
			{
				cout << "编号重复！请重新输入： " << endl;
				break;
			}
			if (n == book_num - 1)                                     //如果一直到book_num-1判断完毕后都没有出现重复数字，跳出循环。
			{
				judge = 0;
				break;
			}
		}
	} while (judge);
	while (1)
	{
		cout << "请输入姓名： " << endl;
		cin >> name;
		cout << "请输入性别： " << endl;
		cin >> sex;
		cout << "请输入通讯地址： " << endl;
		cin >> mailing_address;
		cout << "请输入邮箱地址： " << endl;
		cin >> email_address;
		cout << "请输入电话号码： " << endl;
		cin >> phone_number;
		if (!book_check(this))                                           //检查函数           
		{
			system("pause");
			system("cls");
			menu_show();
			continue;
		}
		break;
	}
	Pseudo_save("保存");
	book_num++;
	system("pause");
	system("cls");
}

void address_book::book_inquire(int book_num)
{
	int book_information_int, num; char book_information_str[50];
	bool judge = 0; int n;
	cout << "---------------------------+\n";
	cout << "输入 1 ：按 编号     查找  |" << endl
		<< "输入 2 ：按 姓名     查找  |" << endl
		<< "输入 3 ：按 电话号码 查找  |" << endl
		<< "输入 4： 按 通讯地址 查找  |" << endl
		<< "输入 5： 按 邮箱地址 查找  |" << endl;
	cout << "---------------------------+\n";
	cout << "请输入你想查询的方式：      " << endl;
	cin >> num;
	switch (num)
	{
	case 1:
		cout << "---------------------------+\n";
		cout << "请输入编号：" << endl;
		while (!(cin >> book_information_int))
		{
			cout << "输入格式有误(应为数字），请重新输入： " << endl;
			cin.clear();
			cin.sync();
			while (cin.get() != '\n')
			{
				continue;
			}
		}
		for (n = 1; n <= book_num; n++)
		{
			if (book[n].number == book_information_int)
			{
				judge = 1;
				break;
			}
		}
		break;
	case 2:
		cout << "---------------------------+\n";
		cout << "请输入姓名:" << endl;
		cin >> book_information_str;
		for (n = 1; n <= book_num; n++)
		{
			if (!strcmp(book[n].name,book_information_str))
			{
				judge = 1;
				break;
			}
		}
		break;
	case 3:
		cout << "---------------------------+\n";
		cout << "请输入电话号码:" << endl;
		cin >> book_information_str;
		for (n = 1; n <= book_num; n++)
		{
			if (!strcmp(book[n].phone_number,book_information_str))
			{
				judge = 1;
				break;
			}
		}
		break;
	case 4:
		cout << "---------------------------+\n";
		cout << "请输入通讯地址:" << endl;
		cin >> book_information_str;
		for (n = 1; n <= book_num; n++)
		{
			if (!strcmp(book[n].mailing_address,book_information_str))
			{
				judge = 1;
				break;
			}
		}
		break;
	case 5:
		cout << "---------------------------+\n";
		cout << "请输入邮箱地址:" << endl;
		cin >> book_information_str;
		for (n = 1; n <= book_num; n++)
		{
			if (!strcmp(book[n].email_address,book_information_str))
			{
				judge = 1;
				break;
			}
		}
		break;
	}
	if (judge)
	{
		cout << "查找成功！" << endl;
		cout << "---------------------------+\n";
		cout << "编号：" << book[n].number << endl
			<< "姓名： " << book[n].name << endl
			<< "性别： " << book[n].sex << endl
			<< "通讯地址： " << book[n].mailing_address << endl
			<< "邮箱地址：" << book[n].email_address << endl
			<< "电话号码： " << book[n].phone_number << endl;
		cout << "---------------------------+\n";
	}
	else
	{
		cout << "查无此人。" << endl;
	}
	system("pause");
	system("cls");
}


void address_book::data_display(int book_num)
{
	if (book_num == 1)              //没有添加过任何通讯录信息的book_num为1.
	{
		cout << "通讯录为空" << endl;

	}
	else
	{
		cout << std::left << " 编号 " << std::right << setw(7) << "姓名" << std::right << setw(8) << "性别" << std::right << setw(17)
			<< "通讯地址" << std::right << setw(21) << "邮箱地址" << std::right << setw(19) << "电话号码" << endl;
		cout << "----------------------------------------------------------------------------------------------" << endl;
		for (int n = 1; n <= book_num - 1; n++)
		{
			cout << std::left
				<< book[n].number << std::right << setw(8)
				<< book[n].name << std::right << setw(6)
				<< book[n].sex << std::right << setw(24)
				<< book[n].mailing_address << std::right << setw(20)
				<< book[n].email_address << std::right << setw(16)
				<< book[n].phone_number << endl;
		}
		cout << "----------------------------------------------------------------------------------------------" << endl;
	}
	system("pause");
	system("cls");
}

void address_book::book_delete(int &book_num)
{
	int book_information_int;
	bool judge = 0; int n;
	cout << "---------------------------+\n";
	cout << "请输入要删除记录的编号:" << endl;
	while (!(cin >> book_information_int))
	{
		cout << "输入格式有误(应为数字），请重新输入： " << endl;
		cin.clear();
		cin.sync();
		while (cin.get() != '\n')
		{
			continue;
		}
	}
	for (n = 1; n <= book_num; n++)
	{
		if (book[n].number == book_information_int)
		{
			judge = 1;
			break;
		}
	}
	if (judge)
	{
		if (n != book_num)
		{
			while (n != book_num)
			{
				book[n] = book[n + 1];
				n++;
			}
			book_num--;
		}
		else
		{
			book_num--;                                                                                          //其实并没有真正删除最后一个元素，只是下标减一，下次添加新元素时会替代原来应该被删除的元素。
		}
		cout << "---------------------------+\n";
		cout << "删除成功！" << endl;
	}
	else
	{
		cout << "---------------------------+\n";
		cout << "查无此人，无法删除。" << endl;
	}
	system("pause");
	system("cls");
}


void address_book::data_edit(int &book_num)
{
	char book_information_str[50]; int book_information_int;
	bool judge = 0; int n, num;
	cout << "---------------------------+\n";
	cout << "请输入要修改的记录的编号:" << endl;
	while (!(cin >> book_information_int))
	{
		cout << "输入格式有误(应为数字），请重新输入： " << endl;
		cin.clear();
		cin.sync();
		while (cin.get() != '\n')
		{
			continue;
		}
	}
	for (n = 1; n <= book_num; n++)
	{
		if (book[n].number == book_information_int)
		{
			judge = 1;
			break;
		}
	}
	if (judge)
	{
		cout << "---------------------------+\n";
		cout << "请输入你想修改的内容： " << endl;
		cout << "输入 1 ：对 姓名 进行修改" << endl
			<< "输入 2 ：对 性别 进行修改" << endl
			<< "输入 3 ：对 通讯地址 进行修改" << endl
			<< "输入 4： 对 邮箱地址 进行修改" << endl
			<< "输入 5： 对 电话号码 进行修改" << endl;
		cout << "---------------------------+\n";
		cin >> num;
		switch (num)
		{
		case 1:
			cout << "---------------------------+\n";
			cout << "请输入修改后的姓名：" << endl;
			cin >> book_information_str;
			strcpy_s(book[n].name, book_information_str);
			judge = 1;
			break;
		case 2:
			cout << "---------------------------+\n";
			cout << "请输入修改后的性别:" << endl;
			cin >> book_information_str;
			strcpy_s(book[n].sex, book_information_str);
			judge = 1;
			break;
		case 3:
			cout << "---------------------------+\n";
			cout << "请输入修改后的通讯地址:" << endl;
			cin >> book_information_str;
			strcpy_s(book[n].mailing_address, book_information_str);
			judge = 1;
			break;
		case 4:
			cout << "---------------------------+\n";
			cout << "请输入修改后的邮箱地址:" << endl;
			cin >> book_information_str;
			strcpy_s(book[n].email_address, book_information_str);
			judge = 1;
			break;
		case 5:
			cout << "---------------------------+\n";
			cout << "请输入修改后的电话号码:" << endl;
			cin >> book_information_str;
			strcpy_s(book[n].phone_number, book_information_str);
			judge = 1;
			break;

		}
		cout << "---------------------------+\n";
		cout << "内容修改成功！" << endl;
		cout << "以下为修改后的内容：" << endl;
		if (judge)
		{
			cout << "---------------------------+\n";
			cout << "编号：" << book[n].number << endl
				<< "姓名： " << book[n].name << endl
				<< "性别： " << book[n].sex << endl
				<< "通讯地址： " << book[n].mailing_address << endl
				<< "邮箱地址：" << book[n].email_address << endl
				<< "电话号码： " << book[n].phone_number << endl;
			cout << "---------------------------+\n";
		}
	}
	else
	{
		cout << "---------------------------+\n";
		cout << "查无此人，无法编辑。" << endl;
	}
	system("pause");
	system("cls");
}
void confirm_exit()
{
	char judge;
	cout << "---------------------------+\n";
	cout << "确认退出？( Y 确认退出 / N 返回管理系统）" << endl;
	cin >> judge;
	if (judge == 'Y' || judge == 'y')
	{
		exit(0);
	}
	else
	{
		system("cls");
	}

}

int main()
{
	int book_num = 1;                          //通讯录 数组,从1开始.
	int number;                                //输入的号码 
	while (1)                                  //反复循环，来重复输入。
	{
		menu_show();
		while (!(cin >> number))                    //输入错误号码   
		{
			cout << "请输入1到8内的数字" << endl;
			cin.clear();
			cin.sync();
			while (cin.get() != '\n')
			{
				continue;
			}
		}                                      //已经输入正确号码
		switch (number)                        //按照序号来执行不同模块下的功能（模块化） 
		{
		case 1:
			book[book_num].book_add(book_num);
			break;
		case 2:
			address_book::book_inquire(book_num);
			break;
		case 3:
			address_book::data_display(book_num);
			break;
		case 4:
			address_book::book_delete(book_num);
			break;
		case 5:
			address_book::data_edit(book_num);
			break;
		case 6:
			address_book::book_save(book_num);
			break;
		case 7:
			address_book::book_read(book_num);
			break;
		case 8:
			confirm_exit();
			break;
		default:
			cout << "请输入1到8内的数字\n";
			system("pause");
			system("cls");
			break;
		}
	}
}