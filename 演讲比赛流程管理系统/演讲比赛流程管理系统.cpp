#include<iostream>
using namespace std;
#include"speechManager.h"
#include<ctime>
//#include"Speaker.h"

int main()
{
	//创建管理对象
	speechManager sm;
	//随机数种子
	srand((unsigned int)time(NULL));
	while (true)
	{
		//展示菜单
		sm.show_Menu();
		cout << "请选择：";
		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1:sm.showSpeaker();//1、查看参赛选手
			break;
		case 2:sm.addSpeaker();//2、添加参赛选手
			break;
		case 3:sm.deleteSpeaker();//3、删除参赛选手
			break;
		case 4:sm.startSpeech();//4、开始演讲比赛
			break;
		case 5:sm.viewRecord();//5、查看往届记录
			break;
		case 6:sm.clearRecord();//6、清空比赛记录
			break;
		case 7:sm.exitSystem();//7、退出比赛系统
			break;
		default:cout << "输入的有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}