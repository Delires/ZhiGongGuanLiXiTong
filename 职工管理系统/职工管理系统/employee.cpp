#include "employee.h"

//���캯��
Employee::Employee(int id, string name, int depid) 
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = depid;   //thisָ��:���������ͬһ���ຯ����ÿ���ཨ���Ķ������Լ���thisָ����������
}



//��д���麯��,Employee�Ĳ������ƺ���Get_Depart
string Employee::Get_Depart(void)
{
	return string("Ա��");
}


//��д���麯��,Employee����ʾ����Show_Info
void Employee::Show_Info(void)
{
	cout << "ְ�����:" << this->m_Id
		<< " \tְ������:" << this->m_Name
		<< " \t��λ:" << this->Get_Depart()
		<< " \t��λְ��:��ɾ�����������" << endl;   
}
