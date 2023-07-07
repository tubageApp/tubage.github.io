#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	//8���˳��������
	void exitSystem();

	//1�����ְ����Ϣ
	//��¼�ļ��е�����
	int m_EmpNum;
	//Ա������ָ��
	Worker** m_EmpArray;
	void add_Emp();

	//���浽�ļ���
	void save();

	//��ȡ�ļ�
	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//2����ʾְ����Ϣ
	void show_Emp();

	//���ز��ҵ���λ�ã�ɾ�����޸��Լ����ҿ����õ���
	int IsExist(int id);

	//3��ɾ����ְְ��
	void Del_Emp();

	//4���޸�ְ����Ϣ
	void Mod_Emp();

	//5������ְ��
	void Find_Emp();

	//6������ְ��
	void Sort_Emp();

	//7������ļ�
	void Clean_File();

	//��������
	~WorkerManager();
};
