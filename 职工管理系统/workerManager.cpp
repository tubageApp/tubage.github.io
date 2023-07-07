#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile.txt"

//构造函数
WorkerManager::WorkerManager()
{
	//初始化属性
	int num = 0;
	num = this->get_EmpNum();
	if (num > 0)
	{
		this->m_EmpNum = num;
		this->m_FileIsEmpty = false;
		this->m_EmpArray = new Worker * [this->m_EmpNum];
		this->init_Emp();

		//测试是否成功代码
		//this->m_EmpArray[0]->showInfo();
	}
	else
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;

		//测试是否成功代码
		//cout << "文件为空或文件不存在" << endl;
	}
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "**********************************" << endl;
	cout << "*********1、增加职工信息**********" << endl;
	cout << "*********2、显示职工信息**********" << endl;
	cout << "*********3、删除离职职工**********" << endl;
	cout << "*********4、修改职工信息**********" << endl;
	cout << "*********5、查找职工信息**********" << endl;
	cout << "*********6、按照编号排序**********" << endl;
	cout << "*********7、清空所有文档**********" << endl;
	cout << "*********8、退出管理程序**********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}

//8、退出管理程序
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//1、添加职工信息
void WorkerManager::add_Emp()
{
	cout << "请输入添加职工数量：";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//计算新空间大小
		int newsize = m_EmpNum + addNum;

		//开辟新的堆区空间
		Worker** newSpase = new Worker * [newsize*sizeof(Worker)];

		if (m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpase[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum;i++)
		{
			int id;
			string name;
			int dId;
			cout << "请输入第" << i + 1 << "个职工的信息" << endl;
			cout << "职工号：";
			cin >> id;
			if (m_EmpArray != NULL)
			{
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (m_EmpArray[i]->m_Id == id)
					{
						cout << "该职工号已存在，请重新输入：";
						cin >> id;
					}
				}
			}
			cout << "姓名：";
			cin >> name;
			cout << "请选择该职工的岗位   1、普通职工    2、经理    3、老板    ：";
			cin >> dId;

			Worker* worker = NULL;
			switch (dId)
			{
			case 1://普通员工
				worker = new Employee(id, name, dId);
				break;
			case 2://经理
				worker = new Manager(id, name, dId);
				break;
			case 3://老板
				worker = new Boss(id, name, dId);
				break;
			default:
				break;
			}
			newSpase[this->m_EmpNum + i] = worker;
		}
		//释放原来数组
		delete[] this->m_EmpArray;
		//更新数组长度
		this->m_EmpNum = newsize;
		//更新数组空间指向
		this->m_EmpArray = newSpase;
		//保存到文件
		this->save();
		//标识数组不为空
		this->m_FileIsEmpty = false;
		//提示信息
		cout << "成功添加" << addNum << "个职工" << endl;
	}
	else
	{
		cout << "输入错误！" << endl;
	}
	system("pause");
	system("cls");
}

//保存到文件中
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	
	ofs.close();
}

//判断文件是否为空//获得文件内数据个数
int WorkerManager::get_EmpNum()
{
	int id;
	string name;
	int dId;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//记录读出数据数
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	ifs.close();
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	int id;
	string name;
	int dId;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker=NULL;
		switch (dId)
		{
		case 1://普通员工
			worker = new Employee(id, name, dId);
			break;
		case 2://经理
			worker = new Manager(id, name, dId);
			break;
		case 3://老板
			worker = new Boss(id, name, dId);
			break;
		default:
			break;
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//2、显示职工信息
void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//返回查找到的位置（删除和修改以及查找可以用到）
int WorkerManager::IsExist(int id)
{
	int temp = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			temp = i;
			break;
		}
	}
	return temp;
}

//3、删除离职职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
	}
	else
	{
		cout << "请输入想要删除职工的职工号：";
		int id;
		cin >> id;
		int ret;
		ret = this->IsExist(id);
		if (ret == -1)
		{
			cout << "查无此人！" << endl;
		}
		else
		{
			cout << "正在删除：" << endl;
			this->m_EmpArray[ret]->showInfo();
			for (int j = ret; j < this->m_EmpNum; j++)
			{
				this->m_EmpArray[j] = this->m_EmpArray[j + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功！" << endl;
			if (this->m_EmpNum == 0)
			{
				this->m_FileIsEmpty = true;
			}
		}
	}
	system("pause");
	system("cls");
}

//4、修改职工信息
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
	}
	else
	{
		cout << "请输入需要修改职工的职工号：";
		int id;
		cin >> id;
		int ret;
		ret = this->IsExist(id);
		if (ret == -1)
		{
			cout << "查无此人！" << endl;
		}
		else
		{
			this->m_EmpArray[ret]->showInfo();
			delete this->m_EmpArray[ret];
			int id;
			string name;
			int dId;
			cout << "请输入新的职工号:";
			cin >> id;
			cout << "请输入新的职工姓名：";
			cin >> name;
			cout << "请输入新的职工岗位：1、普通职工    2、经理    3、老板     ：";
			cin >> dId;

			Worker* worker = NULL;
			switch (dId)
			{
			case 1://普通员工
				worker = new Employee(id, name, dId);
				break;
			case 2://经理
				worker = new Manager(id, name, dId);
				break;
			case 3://老板
				worker = new Boss(id, name, dId);
				break;
			default:
				break;
			}
			m_EmpArray[ret] = worker;
			cout << "修改成功！" << endl;
			this->save();
		}
	}
	system("pause");
	system("cls");
}

//5、查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
	}
	else
	{
		cout << "请选择查询的方式：1、职工号   2、职工姓名   ：";
		int temp;
		while (true)
		{
			cin >> temp;
			if (temp == 1)
			{
				cout << "请输入想要查询的职工号：";
				int id;
				cin >> id;
				int ret;
				ret = this->IsExist(id);
				if (ret == -1)
				{
					cout << "查无此人！" << endl;
				}
				else
				{
					this->m_EmpArray[ret]->showInfo();
				}
				break;
			}
			else if (temp == 2)
			{
				cout << "请输入想要查询的职工姓名：";
				string name;
				cin >> name;
				int NameNum = 0;
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->m_Name == name)
					{
						this->m_EmpArray[i]->showInfo();
						NameNum++;
					}
				}
				if (NameNum == 0)
				{
					cout << "查无此人！" << endl;
				}
				break;
			}
			else
			{
				cout << "查找方式输入错误，请重新输入：";
				continue;
			}
		}
	}
	system("pause");
	system("cls");
}

//6、排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请选择职工号排序方式：1、升序    2、降序    ：";
	int temp;
	while (true)
	{
		cin >> temp;
		if (temp == 1)
		{
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				for (int j = 0; j < this->m_EmpNum - i - 1; j++)
				{
					Worker* worker;
					if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[j + 1]->m_Id)
					{
						worker = this->m_EmpArray[j];
						this->m_EmpArray[j] = this->m_EmpArray[j + 1];
						this->m_EmpArray[j + 1] = worker;
					}
				}
			}
			cout << "升序排序成功！" << endl;
			this->save();
			break;
		}
		else if (temp == 2)
		{
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				for (int j = 0; j < this->m_EmpNum - i - 1; j++)
				{
					Worker* worker;
					if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[j + 1]->m_Id)
					{
						worker = this->m_EmpArray[j];
						this->m_EmpArray[j] = this->m_EmpArray[j + 1];
						this->m_EmpArray[j + 1] = worker;
					}
				}
			}
			cout << "降序排序成功！" << endl;
			this->save();
			break;
		}
		else
		{
			cout << "排序方式输入错误，请重新输入：";
			continue;
		}
	}
	system("pause");
	system("cls");
}

//7、清除文件
void WorkerManager::Clean_File()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "确认要删除文件吗？ 1、确认    2、返回   ：";
	int temp;
	while (true)
	{
		cin >> temp;
		if (temp == 1)
		{
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc);
			ofs.close();
			if (this->m_EmpArray != NULL)
			{
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					delete this->m_EmpArray[i];
				}
				this->m_EmpNum = 0;
				delete this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_FileIsEmpty = true;
			}
			break;
		}
		else if (temp == 2)
		{
			system("cls");
			return;
		}
		else
		{
			cout << "输入错误，请重新输入：";
			continue;
		}
	}
	system("pause");
	system("cls");
}

//析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
		}
		this->m_EmpNum = 0;
		delete this->m_EmpArray;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
	}
}