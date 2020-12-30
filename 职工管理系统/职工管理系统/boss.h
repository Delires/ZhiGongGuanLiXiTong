/*
boss多态 继承 父类Worker
重写父类Worker的纯虚函数
构造函数输入共性值 ， 重写Get_Depart得到自己的部门名，show显示内容
*/
#pragma once
#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

class Boss : public Worker //三种继承 public private protected
{
public:
	//有参构造函数 共性
	Boss(int id, string name, int depid);

	//重写纯虚构造函数
	virtual string Get_Depart(void);
	virtual void Show_Info(void);

public:
	/*成员是父类继承的，可以看父类*/

};


