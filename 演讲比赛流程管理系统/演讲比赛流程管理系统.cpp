#include<iostream>
using namespace std;
#include"speechManager.h"
#include<ctime>
//#include"Speaker.h"

int main()
{
	//�����������
	speechManager sm;
	//���������
	srand((unsigned int)time(NULL));
	while (true)
	{
		//չʾ�˵�
		sm.show_Menu();
		cout << "��ѡ��";
		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1:sm.showSpeaker();//1���鿴����ѡ��
			break;
		case 2:sm.addSpeaker();//2����Ӳ���ѡ��
			break;
		case 3:sm.deleteSpeaker();//3��ɾ������ѡ��
			break;
		case 4:sm.startSpeech();//4����ʼ�ݽ�����
			break;
		case 5:sm.viewRecord();//5���鿴�����¼
			break;
		case 6:sm.clearRecord();//6����ձ�����¼
			break;
		case 7:sm.exitSystem();//7���˳�����ϵͳ
			break;
		default:cout << "������������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}