#include"boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

//չʾ��Ϣ
void Boss::showInfo()
{
	cout << "ְ���ţ�" << this->m_Id
		<< "\t������" << this->m_Name
		<< "\tְλ��" << this->getDeptName()
		<< "\t��λְ�𣺸������������" << endl;
}

//��ø�λ���ƣ����Ը��ݸ�λ���ж���Ҫ�������飬�Լ����䲿�ţ�
string Boss::getDeptName()
{
	return string("�ϰ�");
}

//��������
Boss::Boss()
{

}