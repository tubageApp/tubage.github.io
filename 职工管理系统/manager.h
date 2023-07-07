#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Manager:public Worker
{
public:
	//构造函数
	Manager(int id, string name, int dId);

	//展示信息
	virtual void showInfo();

	//获得岗位名称（可以根据岗位来判断需要做的事情，以及分配部门）
	virtual string getDeptName();

	//析构函数
	Manager();

};