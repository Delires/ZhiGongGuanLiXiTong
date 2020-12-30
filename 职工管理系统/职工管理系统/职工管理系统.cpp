/*
main()函数干什么？
1.调用建立的.h文件，使用各种类建立对象
*/
#include <iostream>
using namespace std;
#include "workerManger.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

//测试多态!!工作人员Worker类:老板、经理、员工
void test_Worker(void)
{
	Worker *w1 = new Employee(001, "张三", 1);//括号法拷贝函数赋值 堆区开辟
	w1->Show_Info(); 
	delete(w1); //堆区删除，防止数据泄漏

	Worker *w2 = new Manager(002, "李四", 2);//括号法拷贝函数赋值
	w2->Show_Info();
	delete(w2);

	Worker *w3 = new Boss(9527, "王五", 3);//括号法拷贝函数赋值
	w3->Show_Info();
	delete(w3);
}

int main(void)
{
	int ret;
	int choice; //存储用户的输入功能编号
	WorkerManger wm; //实例化 管理类
	

	while (true)//死循环,程序一直运行
	{
		wm.Show_Menu();//展示菜单
		cout << "请输入功能序号:" << endl;
		cin >> choice; //输入的数字传入功能选择标号
		switch (choice)
		{
			case 0: //0:退出职工管理程序
				cout << "您选择了功能0:退出职工管理程序" << endl;
				wm.ExitSystem();
				break;
			case 1: //1:增加管理员工信息
				cout << "您选择了功能1:增加管理员工信息" << endl;
				wm.Add_Emp();
				break;
			case 2: //2:显示职工信息
				cout << "您选择了功能2:显示职工信息" << endl;
				wm.Show_Emp();
				break;
			case 3: //3:删除离职职工信息   (判断职工是否存在，再删除)
				cout << "您选择了功能3:删除离职职工信息 " << endl;
				wm.Delet_Emp();//320
				break;
			case 4: //4:修改职工信息
				cout << "您选择了功能4:修改职工信息 " << endl;
				wm.Mod_Emp();
				break;
			case 5: //5:查找职工信息
				cout << "您选择了功能5:查找职工信息 " << endl;
				wm.Find_Emp_Togther();
				break;
			case 6: //6:按照职工编号排序
				cout << "您选择了功能6:按照职工编号排序 " << endl;
				wm.Sort_Emp();
				break;
			case 7: //7:删除所有职工信息
				cout << "您选择了功能7:删除所有职工信息 " << endl;
				wm.Clear_All_Emp();
				break;
			default: //输入有误
				system("cls"); //清除屏幕,清除后又从while开始,又wm.Show_Menu();展示菜单
				break;
		}
	}

	system("pause");
	return 0;
}