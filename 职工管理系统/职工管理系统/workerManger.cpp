/*
cpp文件作用
1.对函数定义
2.对类的成员函数定义(构造，析构，重载等其他函数)，记得写类名类名::
*/
#include "workerManger.h" //库文件用<>  自己的.h文件用""

/*
函数名:WorkerManger()
用途:构造函数。按三种文件类型，根据文件存在类型不同来初始化变量
					1. 第一次使用，文件未创建
					2. 文件存在，但是数据被用户清空
					3. 文件存在，并且保存职工的所有数据
			这三种情况是递进的,前面的完成了就不到后面的了
*/
WorkerManger::WorkerManger()
{
	ifstream ifs;
	ifs.open(SAVEFILENAME, ios::in);//读取文件准备

//1. 第一次使用，文件未创建。这种情况下初始化成员变量	
	if (!ifs.is_open())
	{  
		cout << "文件不存在，因此没有数据！" << endl;
	//文件不存在，人数=0  存放成员指针的数组=0
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL; //双重指针
		m_File_Is_Empty = true;
		ifs.close();
		return;
	}

//2. 文件存在，但是数据被用户清空。这种情况下初始化成员变量
	char ch;
	ifs >> ch; //文件为空还会有结尾字符0xFF,先读出来再判断，这样文件就真为空了
	if (ifs.eof())//判断文件是否为空,空是true(0xFF读走了)
	{
		cout << "文件存在，但文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = 0;
		this->m_File_Is_Empty = true; //啥时候标志位为false呢?在每一次添加人员后
		ifs.close();
		return;
	}

//3. 文件存在，并且保存职工的所有数据。这种情况下初始化成员变量
	//测试 cout << "文件存在，且里面有" << this->Get_EmpNumb() << "个员工" << endl;
	this->m_EmpNum = this->Get_EmpNumb();//职工数量赋值

	this->m_EmpArray = new Worker*[this->m_EmpNum];//初始化m_EmpArray(指针数组的指针)的大小，不然存储会尿崩,大小不匹配
	this->Init_Emp();//读取职工数据到堆区,便于下次操作        
	////测试for (int i = 0; i < this->m_EmpNum; i++)//测试
	//{
	//	cout <<setw(15) <<left << (*(this->m_EmpArray + i))->m_Id
	//		 <<setw(15) <<left << (*(this->m_EmpArray + i))->m_Name
	//		 <<setw(15) <<left << (*(this->m_EmpArray + i))->m_DeptID
	//  << endl;               //<<setw(15) <<left<<xxx    xxx字符占左对齐,占15个字符不足补0
	//}
	return;
}




/**
函数名:~WorkerManger()
用途:析构函数，析构管理对象的成员变量(存储职工对象的指针)
**/
WorkerManger::~WorkerManger()
{
//对象用完后，主动析构堆区存放的数据
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
		/*
		Add_Emp()里的Worker和newSpace也是堆区创建的，为什么不释放呢？
		newSpace:this->m_EmpArray = newSpace;
				 将newSpace的地址赋值给m_EmpArray，地址指向的东西只有一份，释放m_EmpArray就等价于释放newSpace
		Worker: *(newSpace+i)=Worker;
				 ①多个Worker组成了newSpace，释放newSpace就等价于释放多个Worker
				 ②地址指向的东西只有一份，每次释放Worker,那再newSpace应该有的员工信息不就是空了吗？必须等保存后统一释放啊
		*/
	}	

}




/**
函数名:Show_Menu()
用途:与用户沟通的界面菜单函数
**/
void WorkerManger::Show_Menu()
{
	cout << "*您可以随便获取该程序源码,祝您生活愉快！开发人员:曹无极 QQ:985550861*******" << endl;
	cout << "*********************欢迎使用职工管理系统,功能如下，按序号选择功能*********" << endl;
	cout << "*********************0:退出职工管理程序************************************" << endl;
	cout << "*********************1:增加管理员工信息************************************" << endl;
	cout << "*********************2:显示职工信息    ************************************" << endl;
	cout << "*********************3:删除离职职工信息************************************" << endl;
	cout << "*********************4:修改职工信息    ************************************" << endl;
	cout << "*********************5:查找职工信息    ************************************" << endl;
	cout << "*********************6:按照员工编号排序************************************" << endl;
	cout << "*********************7:删除所有职工信息************************************" << endl;
}




/**
函数名:ExitSystem()
用途:退出职工管理系统
**/
void WorkerManger::ExitSystem()
{
	cout << "欢迎下次使用职工管理系统" << endl;
	system("pause"); //再输入任意字符退出，防止exit(0);退出生硬
	exit(0); //C 库函数 void exit(int status) 立即终止调用进程
}



/**
函数名:Add_Emp()
用途:增加管理员工信息(函数)
**/
void WorkerManger::Add_Emp()
{
	cout << "请输入增加的员工数量:" << endl;
	int addNum = 0; //保存增加的用户数量
	cin >> addNum;

	if (addNum > 0)
	{
	//添加
	//计算添加员工后新的空间大小，便于开辟存放员工指针的"指针数组"大小
		int newSize = this->m_EmpNum + addNum; //原员工数+新员工数
	//根据成员开辟新大小的"指针数组"
		Worker ** newSpace = new Worker*[newSize];//Worker*[newSize] "指针数组", 存放new出来的多个员工对象指针
		                                          //这个"指针数组"又要被new出来，是一个二重指针，存放给worker指针
    //将原来的数据，拷贝在新空间里
		if (this->m_EmpArray != NULL)//原来的worker类里存放的多个员工对象指针数组m_EmpArray
		{
			for (int i = 0; i < this->m_EmpNum; i++)//m_EmpNum原来的对象存储的成员个数
			{
				*(newSpace+i) = *(this->m_EmpArray+i);
				                 //newSpace和m_EmpArray均为二重指针，*一次就到了一重数组指针
								 //一重数组指针存放的就是添加的成员指针，把之前存储的成员指针放到新空间里

			}
			
		}
	//批量添加新数据
		for (int i = 0; i < addNum; i++)//addNum新添加的成员数量
		{
		//存放输入的用户信息
			int id;
			string name;
			int  dSelect;  
			cin.width(15); //设置输入数据的长度，不够用空格补齐

		//获取输入信息
			cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个新职工部门编号:" << endl;
			cout << "1:普通员工"<< endl;
			cout << "2:经理" << endl;
			cout << "3:老板" << endl;
			cin >> dSelect;

		//建立一个存储多态下不同的职工对象的指针
			Worker *Worker = NULL; //空指针，用来存放多态下new不同的职工对象指针
		//SWITCH根据不同输入员工类型 来创建不同对象
			switch (dSelect)
			{
			case 1:
				Worker = new Employee(id, name, dSelect);
				break;
			case 2:
				Worker = new Manager(id, name, dSelect);
				break;
			case 3:
				Worker = new Boss(id, name, dSelect);  
				break;
			default:
				cout << "输入员工类型有错" << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
		//将创建的Worker指针，保存到指针数组newSpace;里
			*(newSpace + this->m_EmpNum + i) = Worker;
			              //Worker ** newSpace  *(newSpace)就到了第一层指针数组里了
			              //*(newSpace)的前部分存放了过去的数据，有this->m_EmpNum个，所以从this->m_EmpNum开始存储
		}

	//释放原有的堆区空间，更改新空间指向
		//①原来空间的值全部到新空间了,没用了释放掉
		delete[] this->m_EmpArray; //m_EmpArray是二重指针，指向的是一个指针数组，所以要delete[]
		//②更新WorkerManger类的 职工数量 和 职工对象指针数组
		this->m_EmpArray = newSpace; //更新新的员工指针存储堆区 二重指针之间的地址赋值
		this->m_EmpNum = newSize; //更新员工数
		this->m_File_Is_Empty = false;//更新文件为空标志位
	
	//将含有多个职工对象指针的数组指针 的内容 存储到文件中！！
	
	//保存输入的员工信息
		this->Save_Emp();//字节写的文件存储函数

	//增加成员结束提醒
		cout << "成功添加" << addNum << "名新员工！";
	
	

	}
	else
	{
		cout << "输入有误" << endl;
	}

	//按任意键后，回到上一目录
	system("pause"); //按任意键结束
	system("cls");  //清屏  清屏之后，这个函数运行结束了，就又到while(true)又显示目录
}



//1.1在Txt文件里保存职工信息
void WorkerManger::Save_Emp()
{
	if (this->m_EmpArray != NULL)
	{
		ofstream ofs; //文件句柄
		ofs.open(SAVEFILENAME, ios::out); //输出方式打开，写数据 (暂时不用追加)	
		for (int i = 0; i < this->m_EmpNum; i++)
		{
		//写入文件表达式ofs<<
			ofs << (*(this->m_EmpArray + i))->m_Id << "\t"
				<< (*(this->m_EmpArray + i))->m_Name << "\t"
				<< (*(this->m_EmpArray + i))->m_DeptID << endl;
						//m_EmpArray 定义为  Worker ** m_EmpArray;//指向指针数组的指针
						//*(this->m_EmpArray + i)第一层解引用，提取数组的指针值
						//(*(this->m_EmpArray + i))->m_DeptID 提取指针值所指向对象的成员
		}

		ofs.close(); //关闭
	
	/*每次再次保存员工信息，就会保存一次上次的员工信息怎么办？
	  ①首先，不搞成追加的方式ios::app 来存储文件就不会保存上次
	  ②但是这样就会覆盖掉文件的数据。所以在程序运行前先把原文件的数据读到m_EmpArray
	  ③在把写的数据追加到m_EmpArray后，在写入这样就不会重复保存或覆盖了
	  ④从读文件的地方下功夫，分三种
				1. 第一次使用，文件未创建
				2. 文件存在，但是数据被用户清空
				3. 文件存在，并且保存职工的所有数据
	    
	*/   
		           
	}
	
}



/**
函数名:Get_EmpNumb()
用途:得到文件里的员工数量,根据堆区的数据,来初始化m_EmpArray。为第三种初始化方式做准备
**/
int WorkerManger::Get_EmpNumb()
{
//临时存储文件数据用
	int Id;
	string Name;
	int DeptID;
//记录职工数量
	int num=0;
//读方式读取文件
	ifstream ifs;
	ifs.open(SAVEFILENAME, ios::in);

	while(ifs>>Id && ifs>>Name && ifs>>DeptID)//这些数据有，证明有一个员工
	{
		num++;
	}
	ifs.close();
	return num;

}



/**
函数名:Init_Emp()
用途:初始化管理类的成员变量 Worker ** m_EmpArray，把原来文件里存储的职工全读回来到成员变量。
     因为每次程序运行结束后m_EmpArray里的数据都会被释放掉,因此需要每次先把文件存储的数据从新读到堆区的m_EmpArray
**/
void WorkerManger::Init_Emp()
{
	ifstream ifs;
	ifs.open(SAVEFILENAME, ios::in);
//临时存储文件数据用
	int Id;
	string Name;
	int DeptID;
	int num=0;
	while (ifs >> Id && ifs >> Name && ifs >> DeptID)
	{
		Worker *worker = NULL;
		if (DeptID == 1)//根据部门类型不同用"多态"建立不同的 职工对象
		{
			worker = new Employee(Id, Name, DeptID);//指针数组存指针
		}
		else if (DeptID == 2)
		{
			worker = new Manager(Id, Name, DeptID);
		}
		else if (DeptID == 3)
		{
			worker = new Boss(Id, Name, DeptID);
		}  
		//m_EmpArray定义为 Worker **m_EmpArray   Boss Manager Employee由于多态本质也是Worker

		*(this->m_EmpArray + num) = worker;
		num++;
	}
	ifs.close();
}


/**
函数名:Show_Emp()
用途:显示储存文件里的所有职工信息
实现方法:for循环调用指针数组里每个员工指针的成员函数Show_Info(void)
**/
void WorkerManger::Show_Emp()
{
	if (this->m_File_Is_Empty)//文件空标志位
	{
		cout << "文件不存在或存储员工信息的文件为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{//利用多态调用职工成员对象的函数
			(*(this->m_EmpArray + i))->Show_Info();
		}
	}
	system("pause");
	system("cls");//清屏，然后while(1)又到最开始界面
}


/**
函数名:Emp_Is_Exit(int id);
用途:判断要删除的职工是否存在
返回值:-1错误  或成员所在指针数组的顺序
实现方法:对输入的数据id，在存储指针数组的指针m_EmpArray中遍历寻找
**/
int WorkerManger::Emp_Is_Exit(int id)
{
	int index = -1;//错误标志位
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if ((*(this->m_EmpArray + i))->m_Id == id)
		{
			index = i; //返回指针数组的顺序
			break; //找到后结束寻找
		}
	}
	return index;
}

/**
函数名:Delet_Ewenmp(void);
用途:根据输入的职工编号删除的职工
返回值:
实现方法:对输入的数据id，找到m_EmpArray里序号指针，然后删除指针数组里的这个(用数据前移覆盖方法)
**/
void WorkerManger::Delet_Emp(void)
{
	int del_id;
	int idex;//成员所在的指针数组的顺序
	if(this->m_File_Is_Empty == true)
	{
		cout << "文件不存在或存储员工信息的文件为空" << endl;
	}
	else
	{
		cout << "输入要删除的员工序号:" << endl;
		cin >> del_id;
		idex = this->Emp_Is_Exit(del_id);//在m_EmpArray指针(指针数组的二重指针)寻找有无这个变量
 		if (idex == -1)
		{
			cout << "删除失败,要删除的员工不存在!"<<endl;
		}
		else//职工存在且删除指针数组idex位置的职工
		{
			cout << "这个员工在指针数组m_EmpArray的顺序为"<<idex << endl;
			for (int i = idex; i < this->m_EmpNum-1; i++)//数组是从0开始，数组循环的长度职工人数-1
			{
				//指针数组数据前移来删除数据
				*(this->m_EmpArray + i) = *(this->m_EmpArray + i + 1); //指针数组后一个逐渐覆盖前一个
			}
			this->m_EmpNum--;//更新人数
			this->Save_Emp();//保存新的指针数组
			cout << "删除成功!" << endl;
			cout << "还有" << this->m_EmpNum << "名员工" << endl;
		}

	}
	system("pause");
	system("cls");
}



/**
函数名:Mod_Emp(int id);
用途:根据输入的职工编号，来修改这个编号的职工信息
返回值:无
实现方法:对输入的数据id，找到m_EmpArray里序号指针，delete掉这个堆区指针存放的东西，再重新建立worker指针赋值
**/
void WorkerManger::Mod_Emp()
{
	int del_id;
	int idex = 0;//成员所在的指针数组的顺序
	if (this->m_File_Is_Empty)
	{
		cout << "文件不存在或存储员工信息的文件为空" << endl;
	}
	else
	{
		cout << "请输入要修改的职工的职工编号:" << endl;
		cin >> del_id;
		idex = this->Emp_Is_Exit(del_id);//获取到员工在指针数组里的顺序
		if (idex == -1)
		{
			cout << "修改失败,要修改的员工不存在!" << endl;
		}
		else //存在,修改员工信息
		{
			delete *(this->m_EmpArray + idex); //释放这个成员指针指向的堆区,重新赋值
		//存储输入数据的临时变量
			int new_id=0;
			string new_name="";
			int new_dep_id=0;//记得要初始化
			Worker *worker = NULL;//父类指针存储开辟新的职工类型指针
		//接收更改的值
			cout << "查到指针数组中第" << idex << "个员工" << "请输入新的员工编号:" << endl;
			cin >> new_id;
			cout << "请输入新的员工姓名:" << endl;
			cin >> new_name;
			cout << "请输入新的员工部门编号 1普通员工 2经理 3老板:" << endl;
			cin >> new_dep_id;
			switch (new_dep_id)
			{
				
			case 1:
				worker = new Employee(new_id, new_name, new_dep_id);
				break;      //使用多态构造对象
			case 2:
				worker = new Manager(new_id, new_name, new_dep_id);
				break;
			case 3:
				worker = new Boss(new_id, new_name, new_dep_id);
				break;
			default:
				cout << "输入有错" << endl;
				return;
				break;
			}
			*(this->m_EmpArray + idex) = worker; //将修改的数据更新到指针数组里

			this->Save_Emp();//指针数组存储到文件
			cout << "修改成功" << endl;
	/*
	为啥不直接覆盖，而要先delete *(this->m_EmpArray + idex);在更新*(this->m_EmpArray + idex);?
	    假设*(this->m_EmpArray + idex)存放的Emplyee的指针，修改成Boss指针。单纯的覆盖是没问题，但
	相当于把Boss的屎拉到了Emplyee的茅坑了，那重写的纯虚构造函数Get_Depart(void)必然是错的啊
	所以我们要，先delete在更新，这样Boss的屎拉到了Boss的茅坑了
	*/

		}
	}
	system("pause");
	system("cls");
}



/**
函数名:Find_Emp_Togther();
用途:分为按姓名查找和按编号查找职工信息
返回值:无
实现方法:对输入的数据id和对输入的姓名，找到m_EmpArray里序号指针
**/
void WorkerManger::Find_Emp_Togther()
{
	int fin_method; //查找方法标准为
	int id; //存储输入职工编号
	string nam; //存储输入姓名
	cout << "输入查找方法序号。1:按职工编号查找 2:按职工姓名查找" << endl;
	cin >> fin_method;
	if (this->m_File_Is_Empty)
	{
		cout << "文件不存储在或文件无内容无法查找";
		return;
	}
	if (fin_method == 1)
	{
		cout << "您选择1:按职工编号查找 " << "请输入要查找的职工编号：" << endl;
		cin >> id;
		int index = this->Emp_Is_Exit(id);
		if (index == -1)
		{
			cout << "查找的职工不存在" << endl;
		}
		else
		{
			cout << "查找成功!" << endl;
			cout << "此人在存储的数据中第" << index<<"个,信息为:"<<endl;
			(*(this->m_EmpArray + index))->Show_Info();
		}
	}
	else if(fin_method == 2)
	{
		cout << "您选择2:按职工姓名查找 " << "请输入要查找的职工姓名：" << endl;
		cin >> nam;
		this->Find_Emp_UseName(nam);
	}
	else
	{
		cout << "输入的查找方法序号有误，重新输入" << endl; 
		system("pause");
		system("cls");
	    return;
	}
	system("pause");
	system("cls");
}
/**
函数名:Find_Emp_UseName(string nam)
用途:按姓名在指针数组里查找
返回值:无
实现方法:对输入的姓名。挨个索引，找到m_EmpArray里序号指针
**/
void WorkerManger::Find_Emp_UseName(string nam)
{
	int index;
	bool flag = false;//判断查找是否成功标志
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if ((*(this->m_EmpArray + i))->m_Name == nam)
		{
			index = this->Emp_Is_Exit((*(this->m_EmpArray + i))->m_Id);
			cout <<"查找成功!" << "此人在存储的数据中第" << index << "个,信息为:" << endl;
			(*(this->m_EmpArray + i))->Show_Info();
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "查找的职工不存在" << endl;
	}
}





/**
函数名:Sort_Emp()
用途:按照员工序号大小对员工顺序进行排序
返回值:无
实现方法:冒泡法/排序法，重新排列指针数组m_EmpArray里的数据
**/
void WorkerManger::Sort_Emp()
{
	if (this->m_File_Is_Empty)//文件空标志位
	{
		cout << "文件不存在或存储员工信息的文件为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		int select = 0;
		cout << "请选择按哪种算法进行排序.1:冒泡法 2:排序法" << endl;
		cin >> select;
		if (select == 1)
		{
			this->Sort_Bubbling();
		}
		else if (select == 2)
		{
			this->Sort_Select();
		}
	}
}
/**
函数名:Sort_Bubbling()
用途:使用冒泡法对m_EmpArray指针数组里的数据安职工编号排序
返回值:无
实现方法:冒泡法两个for,外for控制比较轮数,内for控制比较次数。数组两个元素挨个比,大的就像泡泡一样冒上去
**/
void WorkerManger::Sort_Bubbling()
{
	int set = 0;
	cout << "请问按升序排还是降序排?升序:1 降序:2" << endl;
	cin >> set;
	for (int i = 0; i < this->m_EmpNum; i++) //i控制比较轮数
	{
		for (int j = 0; j < this->m_EmpNum - i - 1; j++)//j控制比较次数(越往后比较次数越少)
		{
			if (set == 1)
			{
				if ((*(this->m_EmpArray + j))->m_Id > (*(this->m_EmpArray + j + 1))->m_Id)
				{
					Worker *temp = (*(this->m_EmpArray + j + 1));
					(*(this->m_EmpArray + j + 1)) = (*(this->m_EmpArray + j));
					(*(this->m_EmpArray + j)) = temp;

				}
			}
			else if (set == 2)
			{
				if ((*(this->m_EmpArray + j))->m_Id < (*(this->m_EmpArray + j + 1))->m_Id)
				{
					Worker *temp = (*(this->m_EmpArray + j + 1));
					(*(this->m_EmpArray + j + 1)) = (*(this->m_EmpArray + j));
					(*(this->m_EmpArray + j)) = temp;

				}
			}
		}
	}
	cout << "排序成功，排序后的结果为:" << endl;
	this->Save_Emp();
	this->Show_Emp();
}
/**
函数名:Sort_Select()
用途:使用选择法对m_EmpArray指针数组里的数据安职工编号排序
返回值:无
实现方法:假定数组的第一个元素为最小，挨个和数组里的元素比较，小了就交换，交换后继续比，再比第二个
**/
void WorkerManger::Sort_Select()
{
	int set = 0;
	cout << "请问按升序排还是降序排?升序:1 降序:2" << endl;
	cin >> set;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		int min = i; //假设按数组指针顺序每一个都是最小的
		for (int j = i + 1; j < this->m_EmpNum; j++)//从i元素后的数开始挨个比
		{
			if (set == 1)
			{
				if ((*(this->m_EmpArray + min))->m_Id > (*(this->m_EmpArray + j))->m_Id)//如果大直接换序号
				{
					min = j;
				}
			}
			else if (set == 2)
			{
				if ((*(this->m_EmpArray + min))->m_Id < (*(this->m_EmpArray + j))->m_Id)//如果大直接换序号
				{
					min = j;
				}
			}
			
		}
		//每一轮比较完，最开始认定的不是最小值，就交换指针数组的数据
		if (min != i)
		{
			Worker *temp;
			temp = *(this->m_EmpArray + i);  //交换元素
			*(this->m_EmpArray + i) = *(this->m_EmpArray + min);
			*(this->m_EmpArray + min) = temp;
		}
	}
	cout << "排序成功，排序后的结果为:" << endl;
	this->Save_Emp();
	this->Show_Emp();
}



/**
函数名:Clear_All_Emp();
用途:清空存储的所有职工信息
返回值:无
实现方法:①清空整个txt文件的储存②清空数组指针指向的内容③清空二重指针(指向数组指针的指针)④人数置0⑤更改文件为空标志位
**/
void WorkerManger::Clear_All_Emp()
{
	string str;
	cout << "如果需要清空所有信息，请输入:删除所有职工信息" << endl;
	cin >> str;
	if (str == "删除所有职工信息")
	{
	//①清空整个txt文件的储存
		ofstream ofs;
		ofs.open(SAVEFILENAME, ios::trunc); 
		ofs.close();
	//②清空数组指针指向的内容
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (*(this->m_EmpArray + i) != NULL)
			{
				delete *(this->m_EmpArray + i);
			}	
		}
	//③清空二重指针(指向数组指针的指针)
		if (this->m_EmpArray != NULL)
		{
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
		}
	//④人数置0
		this->m_EmpNum = 0;
	//⑤更改文件为空标志位
		this->m_File_Is_Empty = true;

		cout << "清空存储的所有职工信息成功!" << endl;
	}
	else
	{ 
		cout << "口令错误，不予删除!" << endl;
	}
	system("pause");
	system("cls");
}

