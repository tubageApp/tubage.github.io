#pragma once
#include<iostream>
using namespace std;

//选手类
class Speaker
{
public:
	Speaker()
	{
		this->m_Score[0] = 0;
	}

	string m_Name; //姓名
	double m_Score[2];  //分数
};