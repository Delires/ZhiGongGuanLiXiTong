#include "manager.h"

//Manager�вι��캯��
Manager::Manager(int id, string name, int depid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = depid;
}

//��д���鹹�캯��
string Manager::Get_Depart(void)
{
	return string("����");
}

void Manager::Show_Info(void)
{
	cout << "ְ�����:" << this->m_Id
		<< " \tְ������:" << this->m_Name
		<< " \t��λ:" << this->Get_Depart()
		<< " \t��λְ��:�ϰ��Ա��֮���������" << endl;
}