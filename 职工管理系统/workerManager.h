#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//展示菜单
	void Show_Menu();

	//8、退出管理程序
	void exitSystem();

	//1、添加职工信息
	//记录文件中的人数
	int m_EmpNum;
	//员工数组指针
	Worker** m_EmpArray;
	void add_Emp();

	//保存到文件中
	void save();

	//读取文件
	//判断文件是否为空
	bool m_FileIsEmpty;
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//2、显示职工信息
	void show_Emp();

	//返回查找到的位置（删除和修改以及查找可以用到）
	int IsExist(int id);

	//3、删除离职职工
	void Del_Emp();

	//4、修改职工信息
	void Mod_Emp();

	//5、查找职工
	void Find_Emp();

	//6、排序职工
	void Sort_Emp();

	//7、清除文件
	void Clean_File();

	//析构函数
	~WorkerManager();
};
