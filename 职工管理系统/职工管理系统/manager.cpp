#include "manager.h"

//Manager有参构造函数
Manager::Manager(int id, string name, int depid)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = depid;
}

//重写纯虚构造函数
string Manager::Get_Depart(void)
{
	return string("经理");
}

void Manager::Show_Info(void)
{
	cout << "职工编号:" << this->m_Id
		<< " \t职工姓名:" << this->m_Name
		<< " \t岗位:" << this->Get_Depart()
		<< " \t岗位职责:老板和员工之间承上启下" << endl;
}