/*
.h头文件要做什么？
1.函数声明   ，cpp函数定义
2.h里声明类名、成员函数、成员变量   ，cpp里定义成员函数
3.头文件引用
*/
/*
1.管理类负责内容
	(1)与用户沟通的界面菜单
	(2)对职工内容增加操作
	(3)TXT文件读写交互
*/


#pragma once   //== #ifndef  #define  #endif
#include <iostream> //输入输出流头文件
#include <stdlib.h>
#include <iomanip>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream> //文件操作头文件
#define   SAVEFILENAME    "employeeFILE.txt" //宏定义存储的文件名

class WorkerManger
{
public:
	WorkerManger();  //构造函数    不写默认生成构造、拷贝构造、析构、赋值运算符函数
									  //赋值运算符函数让两个对象一一赋值用,出现深拷贝(堆)要重写赋值运算符函数
	~WorkerManger(); //析构

//显示与用户沟通的界面菜单接口(函数)
	void Show_Menu();
//0:退出职工管理系统接口(函数)
	void ExitSystem();

//1:增加管理员工信息(函数)
	void Add_Emp();
//1.1在Txt文件里保存职工信息
	void Save_Emp();

//2:得到文件里的员工数量
	int Get_EmpNumb();
//2.1：初始化职工变量函数，把原来文件里存储的职工全读回来
	void Init_Emp();
//2.2：显示储存文件里的所有职工信息
	void Show_Emp();

//3:删除离职职工信息 (判断职工是否存在，再删除)
//3.1判断职工是否存在
	int Emp_Is_Exit(int id);
//3.2删除职工
	void Delet_Emp();

//4:修改职工信息
	void Mod_Emp();

//5:查找职工信息,分为按姓名查找和按编号查找
	void Find_Emp_Togther(void);
//5.1 按姓名查找
	void Find_Emp_UseName(string nam);

//6:按照职工编号排序
	void Sort_Emp();
//6.1选择法排序
	void Sort_Bubbling();
//6.2冒泡法排序
	void Sort_Select();

//7:删除所有职工信息
	void Clear_All_Emp();


public:
//1:增加管理员工信息
	int m_EmpNum; //职工数量
	Worker ** m_EmpArray; //因为要把职工信息都放在堆区(栈区就丢失了),所以new出来的职工对象指针要组成一个数组
						  //设置一个都由Worker指针组成的指针数组，该数组用于存放 new出来的多个员工对象指针
	                      //这个指针数组也要存放在堆区，所以要new(指针数组)，这玩意就成了指向指针的指针，所以建立一个Worker**来存储
//判断文件内容是否为空
	bool m_File_Is_Empty;//文件初始化的时候就判断
};

