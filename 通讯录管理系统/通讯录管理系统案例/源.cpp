#include<iostream>
#include<cstdlib>
using namespace std;
#include<string>
#define max 1000

//展示对通讯录的操作
void showMenu()
{
	cout << "\t1、添加联系人" << endl;
	cout << "\t2、显示联系人" << endl;
	cout << "\t3、删除联系人" << endl;
	cout << "\t4、查找联系人" << endl;
	cout << "\t5、修改联系人" << endl;
	cout << "\t6、清空联系人" << endl;
	cout << "\t0、退出通讯录" << endl;
}

//定义联系人结构体
struct Person
{
	//姓名
	string m_Name;
	//性别
	string m_Sex;
	//年龄
	int m_Age;
	//手机号码
	string m_Phone;
	//家庭住址
	string m_Addr;
};

//定义通讯录结构体
struct addressBook
{
	//创建一个联系人数组最多记录1000人
	Person perArray[max];
	//记录联系人数量
	int num = 0;
};

void Phone()
{
	while (true)
	{
		int size = 0;
		string phone;
		cin >> phone;
		for (int i = 0; i < phone.length(); i++)
		{
			if (phone[i] >= '0' && phone[i] <= '9')
			{
				size++;
				continue;
			}
			else
			{
				cout << "您输入的手机号不合法！请重新输入" << endl;
				break;
			}
		}
		if (size == 11 && phone.length() == 11)
		{
			break;
		}
		else
		{
			cout << "请输入11位手机号！" << endl;
		}
	}
}

//1、添加联系人
void addPerson(addressBook *ads)
{
	//判断通讯录是否已满，满了就不再添加
	if (ads->num == max)
	{
		cout << "通讯录已满！";
	}
	else
	{
		cout << "姓名：";
		cin >> ads->perArray[ads->num].m_Name;

		cout << "性别（男或女）：";
		string sex;
		while (true)
		{
			cin >> sex;
			ads->perArray[ads->num].m_Sex = sex;
			//性别只能输入为男和女
			if (sex == "男" || sex == "女")
			{
				break;
			}
			else
			{
				cout << "您输入的性别不合法，请重新输入" << endl;
			}
		}

		cout << "年龄：";
		cin >> ads->perArray[ads->num].m_Age;

		cout << "联系电话：";
		Phone();

		cout << "家庭住址：";
		cin >> ads->perArray[ads->num].m_Addr;

		ads->num++;
		cout << "添加成功！" << endl;
	}
	system("pause");
	system("cls");
}

//2、显示联系人
void showPerson(addressBook *ads)
{
	//先判断（通讯录）联系人数组是否为空
	if (ads->num == 0)
	{
		cout << "通讯录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < ads->num; i++)
		{
			cout << "姓名：" << ads->perArray[i].m_Name << "\t";
			cout << "性别：" << ads->perArray[i].m_Sex << "\t";
			cout << "年龄：" << ads->perArray[i].m_Age << "\t";
			cout << "联系电话：" << ads->perArray[i].m_Phone << "\t";
			cout << "家庭住址：" << ads->perArray[i].m_Addr << "\t" << endl;
		}
	}
	system("pause");
	system("cls");
}

//判断删除，查找，修改的联系人是否存在
int Exist(addressBook* ads,string name)
{
	for (int i = 0; i < ads->num; i++)
	{
		if (ads->perArray[i].m_Name == name)
		{
			//存在返回对应位置
			return i;
		}
		else
		{   //不存在返回-1
			return -1;
		}
	}
	//通讯录为空
	return -1;
}

//3、删除联系人
void delectPerson(addressBook* ads)
{
	cout << "请输入需要删除的联系人的姓名：";
	string name;
	cin >> name;
	int temp = Exist(ads, name);
	if (temp < 0)
	{    //通讯录为空和查不到此人时
		cout << "查无此人！" << endl;
	}
	else
	{
		for (int i = temp; i < ads->num - 1; i++)
		{
			ads->perArray[i] = ads->perArray[i + 1];
		}
		ads->num--;
		cout << "删除成功！" << endl;
	}
	system("pause");
	system("cls");
}

//查找联系人
void findPerson(addressBook* ads)
{
	cout << "请输入需要查找的联系人的姓名：";
	string name;
	cin >> name;
	int temp = Exist(ads, name);
	if (temp < 0)
	{
		cout << "查无此人！" << endl;
	}
	else
	{
		cout << "姓名：" << ads->perArray[temp].m_Name << "\t";
		cout << "性别：" << ads->perArray[temp].m_Sex << "\t";
		cout << "年龄：" << ads->perArray[temp].m_Age << "\t";
		cout << "联系电话：" << ads->perArray[temp].m_Phone << "\t";
		cout << "家庭住址：" << ads->perArray[temp].m_Addr << "\t";
	}
	system("pause");
	system("cls");
}

//5、修改联系人
void changePerson(addressBook* ads)
{
	cout << "请输入需要修改的联系人的姓名：";
	string name;
	cin >> name;
	int temp = Exist(ads, name);
	if (temp < 0)
	{
		cout << "查无此人！" << endl;
	}
	else
	{
		cout << "请输入想要修改的选项：";
		cout << "1、姓名\t";
		cout << "2、性别\t";
		cout << "3、年龄\t";
		cout << "4、联系电话\t";
		cout << "5、家庭住址\t";
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
		{
			cout << "姓名：";
			string name;
			cin >> name;
			ads->perArray[temp].m_Name = name;
			break;
		}
		case 2:
		{
			cout << "性别（男或女）：";
			string sex;
			while (true)
			{
				cin >> sex;
				ads->perArray[temp].m_Sex = sex;
				if (sex == "男" || sex == "女")
				{
					break;
				}
				else
				{
					cout << "您输入的性别不合法，请重新输入" << endl;
				}
			}
			break;
		}
		case 3:
		{
			cout << "年龄：";
			int age;
			cin >> age;
			ads->perArray[temp].m_Age = age;
			break;
		}
		case 4:
		{
			cout << "联系电话：";
			Phone();
			/*cout << "联系电话：";
			string phone;
			cin >> phone;
			ads->perArray[temp].m_Phone = phone;*/
			break;
		}
		case 5:
		{
			cout << "家庭住址：";
			string addr;
			cin >> addr;
			ads->perArray[temp].m_Addr = addr;
			break;
		}
		default:
			break;
		}
	}
	system("pause");
	system("cls");
}

//6、清空联系人
void emptyPerson(addressBook* ads)
{
	ads->num = 0;
}


int main()
{
	addressBook ads;
	while (true)
	{
		//显示菜单
		showMenu();
		int select;
		cout << "请输入要执行的操作：";
		cin >> select;
		switch (select)
		{
			//1、添加联系人
		case 1:addPerson(&ads);
			break;

			//2、显示联系人
		case 2:showPerson(&ads);
			break;

			//3、删除联系人
		case 3: delectPerson(&ads);
			break;

			//4、查找联系人
		case 4:findPerson(&ads);
			break;

			//5、修改联系人
		case 5:changePerson(&ads);
			break;

			//6、清空联系人
		case 6:emptyPerson(&ads);
			break;

			//7、退出通讯录
		case 0:
			cout << "欢迎下次使用！";
			system("pause");
			return 0;
			break;

		default:
			break;
		}
	}
}