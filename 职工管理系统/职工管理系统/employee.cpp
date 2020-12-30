#include "employee.h"

//构造函数
Employee::Employee(int id, string name, int depid) 
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptID = depid;   //this指针:多个对象公用同一个类函数，每个类建立的对象都有自己的this指针用以区别
}



//重写纯虚函数,Employee的部门名称函数Get_Depart
string Employee::Get_Depart(void)
{
	return string("员工");
}


//重写纯虚函数,Employee的显示函数Show_Info
void Employee::Show_Info(void)
{
	cout << "职工编号:" << this->m_Id
		<< " \t职工姓名:" << this->m_Name
		<< " \t岗位:" << this->Get_Depart()
		<< " \t岗位职责:完成经理交给的任务" << endl;   
}
