/*
多态，继承Worker父类
目的是显示employee的特性:岗位名称，岗位职责
重写纯虚函数
*/
#pragma once
#include <iostream> 
#include <string>
#include "worker.h" //多态父类的头文件
using namespace std;
//多态继承Worker
class Employee : public Worker  //继承的三种方式:public protected private 三者区别是什么呢?
{
public:
//构造函数，成员赋值
	Employee(int id, string name, int depid);

//重写纯虚函数，否则子类也是抽象类
	virtual void Show_Info(void);
	virtual string Get_Depart(void);

public:
	 /*成员是父类继承的，可以看父类*/
};




/*
1.继承的三种方式:public protected private 三者区别是什么呢?
  公共继承public    :不能继承父类的private，继承后父类其余成员的权限继续保持
  私有继承private   :不能继承父类的private，继承后父类其余成员的权限为private
  保护继承protected :不能继承父类的private，继承后父类其余的成员权限为protected，则子子类可以继承protected
*/