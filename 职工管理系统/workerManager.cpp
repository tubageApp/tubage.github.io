#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile.txt"

//���캯��
WorkerManager::WorkerManager()
{
	//��ʼ������
	int num = 0;
	num = this->get_EmpNum();
	if (num > 0)
	{
		this->m_EmpNum = num;
		this->m_FileIsEmpty = false;
		this->m_EmpArray = new Worker * [this->m_EmpNum];
		this->init_Emp();

		//�����Ƿ�ɹ�����
		//this->m_EmpArray[0]->showInfo();
	}
	else
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;

		//�����Ƿ�ɹ�����
		//cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
	}
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "**********************************" << endl;
	cout << "*********1������ְ����Ϣ**********" << endl;
	cout << "*********2����ʾְ����Ϣ**********" << endl;
	cout << "*********3��ɾ����ְְ��**********" << endl;
	cout << "*********4���޸�ְ����Ϣ**********" << endl;
	cout << "*********5������ְ����Ϣ**********" << endl;
	cout << "*********6�����ձ������**********" << endl;
	cout << "*********7����������ĵ�**********" << endl;
	cout << "*********8���˳��������**********" << endl;
	cout << "**********************************" << endl;
	cout << endl;
}

//8���˳��������
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//1�����ְ����Ϣ
void WorkerManager::add_Emp()
{
	cout << "���������ְ��������";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//�����¿ռ��С
		int newsize = m_EmpNum + addNum;

		//�����µĶ����ռ�
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
			cout << "�������" << i + 1 << "��ְ������Ϣ" << endl;
			cout << "ְ���ţ�";
			cin >> id;
			if (m_EmpArray != NULL)
			{
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (m_EmpArray[i]->m_Id == id)
					{
						cout << "��ְ�����Ѵ��ڣ����������룺";
						cin >> id;
					}
				}
			}
			cout << "������";
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ   1����ְͨ��    2������    3���ϰ�    ��";
			cin >> dId;

			Worker* worker = NULL;
			switch (dId)
			{
			case 1://��ͨԱ��
				worker = new Employee(id, name, dId);
				break;
			case 2://����
				worker = new Manager(id, name, dId);
				break;
			case 3://�ϰ�
				worker = new Boss(id, name, dId);
				break;
			default:
				break;
			}
			newSpase[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ������
		delete[] this->m_EmpArray;
		//�������鳤��
		this->m_EmpNum = newsize;
		//��������ռ�ָ��
		this->m_EmpArray = newSpase;
		//���浽�ļ�
		this->save();
		//��ʶ���鲻Ϊ��
		this->m_FileIsEmpty = false;
		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "��ְ��" << endl;
	}
	else
	{
		cout << "�������" << endl;
	}
	system("pause");
	system("cls");
}

//���浽�ļ���
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

//�ж��ļ��Ƿ�Ϊ��//����ļ������ݸ���
int WorkerManager::get_EmpNum()
{
	int id;
	string name;
	int dId;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//��¼����������
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	ifs.close();
	return num;
}

//��ʼ��Ա��
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
		case 1://��ͨԱ��
			worker = new Employee(id, name, dId);
			break;
		case 2://����
			worker = new Manager(id, name, dId);
			break;
		case 3://�ϰ�
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

//2����ʾְ����Ϣ
void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
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

//���ز��ҵ���λ�ã�ɾ�����޸��Լ����ҿ����õ���
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

//3��ɾ����ְְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
	}
	else
	{
		cout << "��������Ҫɾ��ְ����ְ���ţ�";
		int id;
		cin >> id;
		int ret;
		ret = this->IsExist(id);
		if (ret == -1)
		{
			cout << "���޴��ˣ�" << endl;
		}
		else
		{
			cout << "����ɾ����" << endl;
			this->m_EmpArray[ret]->showInfo();
			for (int j = ret; j < this->m_EmpNum; j++)
			{
				this->m_EmpArray[j] = this->m_EmpArray[j + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ���" << endl;
			if (this->m_EmpNum == 0)
			{
				this->m_FileIsEmpty = true;
			}
		}
	}
	system("pause");
	system("cls");
}

//4���޸�ְ����Ϣ
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸�ְ����ְ���ţ�";
		int id;
		cin >> id;
		int ret;
		ret = this->IsExist(id);
		if (ret == -1)
		{
			cout << "���޴��ˣ�" << endl;
		}
		else
		{
			this->m_EmpArray[ret]->showInfo();
			delete this->m_EmpArray[ret];
			int id;
			string name;
			int dId;
			cout << "�������µ�ְ����:";
			cin >> id;
			cout << "�������µ�ְ��������";
			cin >> name;
			cout << "�������µ�ְ����λ��1����ְͨ��    2������    3���ϰ�     ��";
			cin >> dId;

			Worker* worker = NULL;
			switch (dId)
			{
			case 1://��ͨԱ��
				worker = new Employee(id, name, dId);
				break;
			case 2://����
				worker = new Manager(id, name, dId);
				break;
			case 3://�ϰ�
				worker = new Boss(id, name, dId);
				break;
			default:
				break;
			}
			m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ���" << endl;
			this->save();
		}
	}
	system("pause");
	system("cls");
}

//5������ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
	}
	else
	{
		cout << "��ѡ���ѯ�ķ�ʽ��1��ְ����   2��ְ������   ��";
		int temp;
		while (true)
		{
			cin >> temp;
			if (temp == 1)
			{
				cout << "��������Ҫ��ѯ��ְ���ţ�";
				int id;
				cin >> id;
				int ret;
				ret = this->IsExist(id);
				if (ret == -1)
				{
					cout << "���޴��ˣ�" << endl;
				}
				else
				{
					this->m_EmpArray[ret]->showInfo();
				}
				break;
			}
			else if (temp == 2)
			{
				cout << "��������Ҫ��ѯ��ְ��������";
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
					cout << "���޴��ˣ�" << endl;
				}
				break;
			}
			else
			{
				cout << "���ҷ�ʽ����������������룺";
				continue;
			}
		}
	}
	system("pause");
	system("cls");
}

//6������ְ��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��ѡ��ְ��������ʽ��1������    2������    ��";
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
			cout << "��������ɹ���" << endl;
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
			cout << "��������ɹ���" << endl;
			this->save();
			break;
		}
		else
		{
			cout << "����ʽ����������������룺";
			continue;
		}
	}
	system("pause");
	system("cls");
}

//7������ļ�
void WorkerManager::Clean_File()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "ȷ��Ҫɾ���ļ��� 1��ȷ��    2������   ��";
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
			cout << "����������������룺";
			continue;
		}
	}
	system("pause");
	system("cls");
}

//��������
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