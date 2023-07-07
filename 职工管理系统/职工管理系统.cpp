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
		cout << "请输入你的选择：";
		cin >> choice;
		switch (choice)
		{
		case 1://增加职工信息
			worker.add_Emp();
			break;
		case 2://显示职工信息
			worker.show_Emp();
			break;
		case 3://删除离职职工
			worker.Del_Emp();
			break;
		case 4://修改职工信息
			worker.Mod_Emp();
			break;
		case 5://查找职工信息
			worker.Find_Emp();
			break;
		case 6://按照序号排序
			worker.Sort_Emp();
			break;
		case 7://清空所有文档
			worker.Clean_File();
			break;
		case 8://退出管理程序
			worker.exitSystem();
			break;
		default:
			cout << "你输入的数不正确，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}