#pragma once
#include<iostream>
using namespace std;

//ѡ����
class Speaker
{
public:
	Speaker()
	{
		this->m_Score[0] = 0;
	}

	string m_Name; //����
	double m_Score[2];  //����
};