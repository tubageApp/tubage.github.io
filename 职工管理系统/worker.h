#pragma once
#include<iostream>
using namespace std;
#include<string>

class Worker
{
public:
	//���캯��

	//չʾ��Ϣ
	virtual void showInfo() = 0;

	//��ø�λ���ƣ����Ը��ݸ�λ���ж���Ҫ�������飬�Լ����䲿�ţ�
	virtual string getDeptName() = 0;

	//��������

	int m_Id;
	string m_Name;
	int m_DeptId;
};
