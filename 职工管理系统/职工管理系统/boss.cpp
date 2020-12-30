#include "boss.h"

//Manager有参构造函数
Boss::Boss(int id, string name, int depid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = depid;
}

//重写纯虚构造函数
string Boss::Get_Depart(void)
{
	return string("老板");
}

void Boss::Show_Info(void)
{
	cout << "职工编号:" << this->m_Id
		<< " \t职工姓名:" << this->m_Name
		<< " \t岗位:" << this->Get_Depart()
		<< " \t岗位职责:管理整个公司事物" << endl;
}