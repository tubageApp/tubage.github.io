#include"employee.h"

Employee::Employee(int id,string name,int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}

//չʾ��Ϣ
void Employee::showInfo()
{
	cout << "ְ���ţ�" << this->m_Id
		<< "\t������" << this->m_Name
		<< "\tְλ��" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}

//��ø�λ���ƣ����Ը��ݸ�λ���ж���Ҫ�������飬�Լ����䲿�ţ�
string Employee::getDeptName()
{
	return string("��ͨԱ��");
}

//��������
Employee::Employee()
{

}