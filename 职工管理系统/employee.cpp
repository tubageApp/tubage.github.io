#include"employee.h"

Employee::Employee(int id,string name,int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

//展示信息
void Employee::showInfo()
{
	cout << "职工号：" << this->m_Id
		<< "\t姓名：" << this->m_Name
		<< "\t职位：" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务。" << endl;
}

//获得岗位名称（可以根据岗位来判断需要做的事情，以及分配部门）
string Employee::getDeptName()
{
	return string("普通员工");
}

//析构函数
Employee::Employee()
{

}