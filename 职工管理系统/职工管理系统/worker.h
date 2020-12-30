/*
该系统分为三类员工:老板，经理，员工三者
三者共性为:不管哪类员工都有： 职工编号，职工姓名，职工部门编号
三者特性为:但不同类员工的：岗位职责和岗位名称 不同
既有共性又有特性，所以要用多态，多态根据传入的类不同调用不同的函数
一个基本的员工类包含其共性，然后多态继承包含三类员工的特性

牵扯到概念:纯虚函数，虚函数，抽象类，继承，动态多态
*/
/*
头文件声明类，成员函数，成员变量      cpp文件具体定义成员函数
*/
#pragma once
#include <iostream> //输入输出流头文件
#include <string>
using namespace std;

class Worker
{
public:
//显示成员信息函数
	virtual void Show_Info(void) = 0; //纯虚函数，则这个类就为抽象类，抽象类不能实体化对象，因此不需要cpp文件
	                                     //继承必须重新函数否则也是抽象类
//特性:获取岗位名称
	virtual string Get_Depart(void) = 0;

public:
//这三者为共性，基类里
	int m_Id;  
	string m_Name;
	int m_DeptID;
};


