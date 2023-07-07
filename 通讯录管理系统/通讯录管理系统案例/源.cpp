#include<iostream>
#include<cstdlib>
using namespace std;
#include<string>
#define max 1000

//չʾ��ͨѶ¼�Ĳ���
void showMenu()
{
	cout << "\t1�������ϵ��" << endl;
	cout << "\t2����ʾ��ϵ��" << endl;
	cout << "\t3��ɾ����ϵ��" << endl;
	cout << "\t4��������ϵ��" << endl;
	cout << "\t5���޸���ϵ��" << endl;
	cout << "\t6�������ϵ��" << endl;
	cout << "\t0���˳�ͨѶ¼" << endl;
}

//������ϵ�˽ṹ��
struct Person
{
	//����
	string m_Name;
	//�Ա�
	string m_Sex;
	//����
	int m_Age;
	//�ֻ�����
	string m_Phone;
	//��ͥסַ
	string m_Addr;
};

//����ͨѶ¼�ṹ��
struct addressBook
{
	//����һ����ϵ����������¼1000��
	Person perArray[max];
	//��¼��ϵ������
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
				cout << "��������ֻ��Ų��Ϸ�������������" << endl;
				break;
			}
		}
		if (size == 11 && phone.length() == 11)
		{
			break;
		}
		else
		{
			cout << "������11λ�ֻ��ţ�" << endl;
		}
	}
}

//1�������ϵ��
void addPerson(addressBook *ads)
{
	//�ж�ͨѶ¼�Ƿ����������˾Ͳ������
	if (ads->num == max)
	{
		cout << "ͨѶ¼������";
	}
	else
	{
		cout << "������";
		cin >> ads->perArray[ads->num].m_Name;

		cout << "�Ա��л�Ů����";
		string sex;
		while (true)
		{
			cin >> sex;
			ads->perArray[ads->num].m_Sex = sex;
			//�Ա�ֻ������Ϊ�к�Ů
			if (sex == "��" || sex == "Ů")
			{
				break;
			}
			else
			{
				cout << "��������Ա𲻺Ϸ�������������" << endl;
			}
		}

		cout << "���䣺";
		cin >> ads->perArray[ads->num].m_Age;

		cout << "��ϵ�绰��";
		Phone();

		cout << "��ͥסַ��";
		cin >> ads->perArray[ads->num].m_Addr;

		ads->num++;
		cout << "��ӳɹ���" << endl;
	}
	system("pause");
	system("cls");
}

//2����ʾ��ϵ��
void showPerson(addressBook *ads)
{
	//���жϣ�ͨѶ¼����ϵ�������Ƿ�Ϊ��
	if (ads->num == 0)
	{
		cout << "ͨѶ¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < ads->num; i++)
		{
			cout << "������" << ads->perArray[i].m_Name << "\t";
			cout << "�Ա�" << ads->perArray[i].m_Sex << "\t";
			cout << "���䣺" << ads->perArray[i].m_Age << "\t";
			cout << "��ϵ�绰��" << ads->perArray[i].m_Phone << "\t";
			cout << "��ͥסַ��" << ads->perArray[i].m_Addr << "\t" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�ж�ɾ�������ң��޸ĵ���ϵ���Ƿ����
int Exist(addressBook* ads,string name)
{
	for (int i = 0; i < ads->num; i++)
	{
		if (ads->perArray[i].m_Name == name)
		{
			//���ڷ��ض�Ӧλ��
			return i;
		}
		else
		{   //�����ڷ���-1
			return -1;
		}
	}
	//ͨѶ¼Ϊ��
	return -1;
}

//3��ɾ����ϵ��
void delectPerson(addressBook* ads)
{
	cout << "��������Ҫɾ������ϵ�˵�������";
	string name;
	cin >> name;
	int temp = Exist(ads, name);
	if (temp < 0)
	{    //ͨѶ¼Ϊ�պͲ鲻������ʱ
		cout << "���޴��ˣ�" << endl;
	}
	else
	{
		for (int i = temp; i < ads->num - 1; i++)
		{
			ads->perArray[i] = ads->perArray[i + 1];
		}
		ads->num--;
		cout << "ɾ���ɹ���" << endl;
	}
	system("pause");
	system("cls");
}

//������ϵ��
void findPerson(addressBook* ads)
{
	cout << "��������Ҫ���ҵ���ϵ�˵�������";
	string name;
	cin >> name;
	int temp = Exist(ads, name);
	if (temp < 0)
	{
		cout << "���޴��ˣ�" << endl;
	}
	else
	{
		cout << "������" << ads->perArray[temp].m_Name << "\t";
		cout << "�Ա�" << ads->perArray[temp].m_Sex << "\t";
		cout << "���䣺" << ads->perArray[temp].m_Age << "\t";
		cout << "��ϵ�绰��" << ads->perArray[temp].m_Phone << "\t";
		cout << "��ͥסַ��" << ads->perArray[temp].m_Addr << "\t";
	}
	system("pause");
	system("cls");
}

//5���޸���ϵ��
void changePerson(addressBook* ads)
{
	cout << "��������Ҫ�޸ĵ���ϵ�˵�������";
	string name;
	cin >> name;
	int temp = Exist(ads, name);
	if (temp < 0)
	{
		cout << "���޴��ˣ�" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸ĵ�ѡ�";
		cout << "1������\t";
		cout << "2���Ա�\t";
		cout << "3������\t";
		cout << "4����ϵ�绰\t";
		cout << "5����ͥסַ\t";
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
		{
			cout << "������";
			string name;
			cin >> name;
			ads->perArray[temp].m_Name = name;
			break;
		}
		case 2:
		{
			cout << "�Ա��л�Ů����";
			string sex;
			while (true)
			{
				cin >> sex;
				ads->perArray[temp].m_Sex = sex;
				if (sex == "��" || sex == "Ů")
				{
					break;
				}
				else
				{
					cout << "��������Ա𲻺Ϸ�������������" << endl;
				}
			}
			break;
		}
		case 3:
		{
			cout << "���䣺";
			int age;
			cin >> age;
			ads->perArray[temp].m_Age = age;
			break;
		}
		case 4:
		{
			cout << "��ϵ�绰��";
			Phone();
			/*cout << "��ϵ�绰��";
			string phone;
			cin >> phone;
			ads->perArray[temp].m_Phone = phone;*/
			break;
		}
		case 5:
		{
			cout << "��ͥסַ��";
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

//6�������ϵ��
void emptyPerson(addressBook* ads)
{
	ads->num = 0;
}


int main()
{
	addressBook ads;
	while (true)
	{
		//��ʾ�˵�
		showMenu();
		int select;
		cout << "������Ҫִ�еĲ�����";
		cin >> select;
		switch (select)
		{
			//1�������ϵ��
		case 1:addPerson(&ads);
			break;

			//2����ʾ��ϵ��
		case 2:showPerson(&ads);
			break;

			//3��ɾ����ϵ��
		case 3: delectPerson(&ads);
			break;

			//4��������ϵ��
		case 4:findPerson(&ads);
			break;

			//5���޸���ϵ��
		case 5:changePerson(&ads);
			break;

			//6�������ϵ��
		case 6:emptyPerson(&ads);
			break;

			//7���˳�ͨѶ¼
		case 0:
			cout << "��ӭ�´�ʹ�ã�";
			system("pause");
			return 0;
			break;

		default:
			break;
		}
	}
}