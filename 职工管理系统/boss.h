#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Boss : public Worker
{
public:
	//���캯��
	Boss(int id, string name, int dId);

	//չʾ��Ϣ
	virtual void showInfo();

	//��ø�λ���ƣ����Ը��ݸ�λ���ж���Ҫ�������飬�Լ����䲿�ţ�
	virtual string getDeptName();

	//��������
	Boss();
};