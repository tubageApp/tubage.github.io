#include<iostream>
using namespace std;
#include"workerManager.h"

int main()
{
	WorkerManager worker;
	int choice;
	while (true)
	{
		worker.Show_Menu();
		cout << "���������ѡ��";
		cin >> choice;
		switch (choice)
		{
		case 1://����ְ����Ϣ
			worker.add_Emp();
			break;
		case 2://��ʾְ����Ϣ
			worker.show_Emp();
			break;
		case 3://ɾ����ְְ��
			worker.Del_Emp();
			break;
		case 4://�޸�ְ����Ϣ
			worker.Mod_Emp();
			break;
		case 5://����ְ����Ϣ
			worker.Find_Emp();
			break;
		case 6://�����������
			worker.Sort_Emp();
			break;
		case 7://��������ĵ�
			worker.Clean_File();
			break;
		case 8://�˳��������
			worker.exitSystem();
			break;
		default:
			cout << "�������������ȷ������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}