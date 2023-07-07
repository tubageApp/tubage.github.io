#pragma once
#include<iostream>
using namespace std;
#include<string>

class Worker
{
public:
	//构造函数

	//展示信息
	virtual void showInfo() = 0;

	//获得岗位名称（可以根据岗位来判断需要做的事情，以及分配部门）
	virtual string getDeptName() = 0;

	//析构函数

	int m_Id;
	string m_Name;
	int m_DeptId;
};
