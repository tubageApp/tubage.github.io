#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

//展示信息
void Boss::showInfo()
{
	cout << "职工号：" << this->m_Id
		<< "\t姓名：" << this->m_Name
		<< "\t职位：" << this->getDeptName()
		<< "\t岗位职责：给经理分配任务。" << endl;
}

//获得岗位名称（可以根据岗位来判断需要做的事情，以及分配部门）
string Boss::getDeptName()
{
	return string("老板");
}

//析构函数
Boss::Boss()
{

}