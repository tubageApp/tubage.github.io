#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Manager:public Worker
{
public:
	//���캯��
	Manager(int id, string name, int dId);

	//չʾ��Ϣ
	virtual void showInfo();

	//��ø�λ���ƣ����Ը��ݸ�λ���ж���Ҫ�������飬�Լ����䲿�ţ�
	virtual string getDeptName();

	//��������
	Manager();

};