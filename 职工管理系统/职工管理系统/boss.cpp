#include "boss.h"

//Manager�вι��캯��
Boss::Boss(int id, string name, int depid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = depid;
}

//��д���鹹�캯��
string Boss::Get_Depart(void)
{
	return string("�ϰ�");
}

void Boss::Show_Info(void)
{
	cout << "ְ�����:" << this->m_Id
		<< " \tְ������:" << this->m_Name
		<< " \t��λ:" << this->Get_Depart()
		<< " \t��λְ��:����������˾����" << endl;
}