/*
cpp�ļ�����
1.�Ժ�������
2.����ĳ�Ա��������(���죬���������ص���������)���ǵ�д��������::
*/
#include "workerManger.h" //���ļ���<>  �Լ���.h�ļ���""

/*
������:WorkerManger()
��;:���캯�����������ļ����ͣ������ļ��������Ͳ�ͬ����ʼ������
					1. ��һ��ʹ�ã��ļ�δ����
					2. �ļ����ڣ��������ݱ��û����
					3. �ļ����ڣ����ұ���ְ������������
			����������ǵݽ���,ǰ�������˾Ͳ����������
*/
WorkerManger::WorkerManger()
{
	ifstream ifs;
	ifs.open(SAVEFILENAME, ios::in);//��ȡ�ļ�׼��

//1. ��һ��ʹ�ã��ļ�δ��������������³�ʼ����Ա����	
	if (!ifs.is_open())
	{  
		cout << "�ļ������ڣ����û�����ݣ�" << endl;
	//�ļ������ڣ�����=0  ��ų�Աָ�������=0
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL; //˫��ָ��
		m_File_Is_Empty = true;
		ifs.close();
		return;
	}

//2. �ļ����ڣ��������ݱ��û���ա���������³�ʼ����Ա����
	char ch;
	ifs >> ch; //�ļ�Ϊ�ջ����н�β�ַ�0xFF,�ȶ��������жϣ������ļ�����Ϊ����
	if (ifs.eof())//�ж��ļ��Ƿ�Ϊ��,����true(0xFF������)
	{
		cout << "�ļ����ڣ����ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = 0;
		this->m_File_Is_Empty = true; //ɶʱ���־λΪfalse��?��ÿһ�������Ա��
		ifs.close();
		return;
	}

//3. �ļ����ڣ����ұ���ְ�����������ݡ���������³�ʼ����Ա����
	//���� cout << "�ļ����ڣ���������" << this->Get_EmpNumb() << "��Ա��" << endl;
	this->m_EmpNum = this->Get_EmpNumb();//ְ��������ֵ

	this->m_EmpArray = new Worker*[this->m_EmpNum];//��ʼ��m_EmpArray(ָ�������ָ��)�Ĵ�С����Ȼ�洢�����,��С��ƥ��
	this->Init_Emp();//��ȡְ�����ݵ�����,�����´β���        
	////����for (int i = 0; i < this->m_EmpNum; i++)//����
	//{
	//	cout <<setw(15) <<left << (*(this->m_EmpArray + i))->m_Id
	//		 <<setw(15) <<left << (*(this->m_EmpArray + i))->m_Name
	//		 <<setw(15) <<left << (*(this->m_EmpArray + i))->m_DeptID
	//  << endl;               //<<setw(15) <<left<<xxx    xxx�ַ�ռ�����,ռ15���ַ����㲹0
	//}
	return;
}




/**
������:~WorkerManger()
��;:���������������������ĳ�Ա����(�洢ְ�������ָ��)
**/
WorkerManger::~WorkerManger()
{
//�����������������������ŵ�����
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
		/*
		Add_Emp()���Worker��newSpaceҲ�Ƕ��������ģ�Ϊʲô���ͷ��أ�
		newSpace:this->m_EmpArray = newSpace;
				 ��newSpace�ĵ�ַ��ֵ��m_EmpArray����ַָ��Ķ���ֻ��һ�ݣ��ͷ�m_EmpArray�͵ȼ����ͷ�newSpace
		Worker: *(newSpace+i)=Worker;
				 �ٶ��Worker�����newSpace���ͷ�newSpace�͵ȼ����ͷŶ��Worker
				 �ڵ�ַָ��Ķ���ֻ��һ�ݣ�ÿ���ͷ�Worker,����newSpaceӦ���е�Ա����Ϣ�����ǿ����𣿱���ȱ����ͳһ�ͷŰ�
		*/
	}	

}




/**
������:Show_Menu()
��;:���û���ͨ�Ľ���˵�����
**/
void WorkerManger::Show_Menu()
{
	cout << "*����������ȡ�ó���Դ��,ף��������죡������Ա:���޼� QQ:985550861*******" << endl;
	cout << "*********************��ӭʹ��ְ������ϵͳ,�������£������ѡ����*********" << endl;
	cout << "*********************0:�˳�ְ���������************************************" << endl;
	cout << "*********************1:���ӹ���Ա����Ϣ************************************" << endl;
	cout << "*********************2:��ʾְ����Ϣ    ************************************" << endl;
	cout << "*********************3:ɾ����ְְ����Ϣ************************************" << endl;
	cout << "*********************4:�޸�ְ����Ϣ    ************************************" << endl;
	cout << "*********************5:����ְ����Ϣ    ************************************" << endl;
	cout << "*********************6:����Ա���������************************************" << endl;
	cout << "*********************7:ɾ������ְ����Ϣ************************************" << endl;
}




/**
������:ExitSystem()
��;:�˳�ְ������ϵͳ
**/
void WorkerManger::ExitSystem()
{
	cout << "��ӭ�´�ʹ��ְ������ϵͳ" << endl;
	system("pause"); //�����������ַ��˳�����ֹexit(0);�˳���Ӳ
	exit(0); //C �⺯�� void exit(int status) ������ֹ���ý���
}



/**
������:Add_Emp()
��;:���ӹ���Ա����Ϣ(����)
**/
void WorkerManger::Add_Emp()
{
	cout << "���������ӵ�Ա������:" << endl;
	int addNum = 0; //�������ӵ��û�����
	cin >> addNum;

	if (addNum > 0)
	{
	//���
	//�������Ա�����µĿռ��С�����ڿ��ٴ��Ա��ָ���"ָ������"��С
		int newSize = this->m_EmpNum + addNum; //ԭԱ����+��Ա����
	//���ݳ�Ա�����´�С��"ָ������"
		Worker ** newSpace = new Worker*[newSize];//Worker*[newSize] "ָ������", ���new�����Ķ��Ա������ָ��
		                                          //���"ָ������"��Ҫ��new��������һ������ָ�룬��Ÿ�workerָ��
    //��ԭ�������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)//ԭ����worker�����ŵĶ��Ա������ָ������m_EmpArray
		{
			for (int i = 0; i < this->m_EmpNum; i++)//m_EmpNumԭ���Ķ���洢�ĳ�Ա����
			{
				*(newSpace+i) = *(this->m_EmpArray+i);
				                 //newSpace��m_EmpArray��Ϊ����ָ�룬*һ�ξ͵���һ������ָ��
								 //һ������ָ���ŵľ�����ӵĳ�Աָ�룬��֮ǰ�洢�ĳ�Աָ��ŵ��¿ռ���

			}
			
		}
	//�������������
		for (int i = 0; i < addNum; i++)//addNum����ӵĳ�Ա����
		{
		//���������û���Ϣ
			int id;
			string name;
			int  dSelect;  
			cin.width(15); //�����������ݵĳ��ȣ������ÿո���

		//��ȡ������Ϣ
			cout << "�������" << i + 1 << "����ְ�����:" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ������:" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "����ְ�����ű��:" << endl;
			cout << "1:��ͨԱ��"<< endl;
			cout << "2:����" << endl;
			cout << "3:�ϰ�" << endl;
			cin >> dSelect;

		//����һ���洢��̬�²�ͬ��ְ�������ָ��
			Worker *Worker = NULL; //��ָ�룬������Ŷ�̬��new��ͬ��ְ������ָ��
		//SWITCH���ݲ�ͬ����Ա������ ��������ͬ����
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
				cout << "����Ա�������д�" << endl;
				system("pause");
				system("cls");
				return;
				break;
			}
		//��������Workerָ�룬���浽ָ������newSpace;��
			*(newSpace + this->m_EmpNum + i) = Worker;
			              //Worker ** newSpace  *(newSpace)�͵��˵�һ��ָ����������
			              //*(newSpace)��ǰ���ִ���˹�ȥ�����ݣ���this->m_EmpNum�������Դ�this->m_EmpNum��ʼ�洢
		}

	//�ͷ�ԭ�еĶ����ռ䣬�����¿ռ�ָ��
		//��ԭ���ռ��ֵȫ�����¿ռ���,û�����ͷŵ�
		delete[] this->m_EmpArray; //m_EmpArray�Ƕ���ָ�룬ָ�����һ��ָ�����飬����Ҫdelete[]
		//�ڸ���WorkerManger��� ְ������ �� ְ������ָ������
		this->m_EmpArray = newSpace; //�����µ�Ա��ָ��洢���� ����ָ��֮��ĵ�ַ��ֵ
		this->m_EmpNum = newSize; //����Ա����
		this->m_File_Is_Empty = false;//�����ļ�Ϊ�ձ�־λ
	
	//�����ж��ְ������ָ�������ָ�� ������ �洢���ļ��У���
	
	//���������Ա����Ϣ
		this->Save_Emp();//�ֽ�д���ļ��洢����

	//���ӳ�Ա��������
		cout << "�ɹ����" << addNum << "����Ա����";
	
	

	}
	else
	{
		cout << "��������" << endl;
	}

	//��������󣬻ص���һĿ¼
	system("pause"); //�����������
	system("cls");  //����  ����֮������������н����ˣ����ֵ�while(true)����ʾĿ¼
}



//1.1��Txt�ļ��ﱣ��ְ����Ϣ
void WorkerManger::Save_Emp()
{
	if (this->m_EmpArray != NULL)
	{
		ofstream ofs; //�ļ����
		ofs.open(SAVEFILENAME, ios::out); //�����ʽ�򿪣�д���� (��ʱ����׷��)	
		for (int i = 0; i < this->m_EmpNum; i++)
		{
		//д���ļ����ʽofs<<
			ofs << (*(this->m_EmpArray + i))->m_Id << "\t"
				<< (*(this->m_EmpArray + i))->m_Name << "\t"
				<< (*(this->m_EmpArray + i))->m_DeptID << endl;
						//m_EmpArray ����Ϊ  Worker ** m_EmpArray;//ָ��ָ�������ָ��
						//*(this->m_EmpArray + i)��һ������ã���ȡ�����ָ��ֵ
						//(*(this->m_EmpArray + i))->m_DeptID ��ȡָ��ֵ��ָ�����ĳ�Ա
		}

		ofs.close(); //�ر�
	
	/*ÿ���ٴα���Ա����Ϣ���ͻᱣ��һ���ϴε�Ա����Ϣ��ô�죿
	  �����ȣ������׷�ӵķ�ʽios::app ���洢�ļ��Ͳ��ᱣ���ϴ�
	  �ڵ��������ͻḲ�ǵ��ļ������ݡ������ڳ�������ǰ�Ȱ�ԭ�ļ������ݶ���m_EmpArray
	  ���ڰ�д������׷�ӵ�m_EmpArray����д�������Ͳ����ظ�����򸲸���
	  �ܴӶ��ļ��ĵط��¹��򣬷�����
				1. ��һ��ʹ�ã��ļ�δ����
				2. �ļ����ڣ��������ݱ��û����
				3. �ļ����ڣ����ұ���ְ������������
	    
	*/   
		           
	}
	
}



/**
������:Get_EmpNumb()
��;:�õ��ļ����Ա������,���ݶ���������,����ʼ��m_EmpArray��Ϊ�����ֳ�ʼ����ʽ��׼��
**/
int WorkerManger::Get_EmpNumb()
{
//��ʱ�洢�ļ�������
	int Id;
	string Name;
	int DeptID;
//��¼ְ������
	int num=0;
//����ʽ��ȡ�ļ�
	ifstream ifs;
	ifs.open(SAVEFILENAME, ios::in);

	while(ifs>>Id && ifs>>Name && ifs>>DeptID)//��Щ�����У�֤����һ��Ա��
	{
		num++;
	}
	ifs.close();
	return num;

}



/**
������:Init_Emp()
��;:��ʼ��������ĳ�Ա���� Worker ** m_EmpArray����ԭ���ļ���洢��ְ��ȫ����������Ա������
     ��Ϊÿ�γ������н�����m_EmpArray������ݶ��ᱻ�ͷŵ�,�����Ҫÿ���Ȱ��ļ��洢�����ݴ��¶���������m_EmpArray
**/
void WorkerManger::Init_Emp()
{
	ifstream ifs;
	ifs.open(SAVEFILENAME, ios::in);
//��ʱ�洢�ļ�������
	int Id;
	string Name;
	int DeptID;
	int num=0;
	while (ifs >> Id && ifs >> Name && ifs >> DeptID)
	{
		Worker *worker = NULL;
		if (DeptID == 1)//���ݲ������Ͳ�ͬ��"��̬"������ͬ�� ְ������
		{
			worker = new Employee(Id, Name, DeptID);//ָ�������ָ��
		}
		else if (DeptID == 2)
		{
			worker = new Manager(Id, Name, DeptID);
		}
		else if (DeptID == 3)
		{
			worker = new Boss(Id, Name, DeptID);
		}  
		//m_EmpArray����Ϊ Worker **m_EmpArray   Boss Manager Employee���ڶ�̬����Ҳ��Worker

		*(this->m_EmpArray + num) = worker;
		num++;
	}
	ifs.close();
}


/**
������:Show_Emp()
��;:��ʾ�����ļ��������ְ����Ϣ
ʵ�ַ���:forѭ������ָ��������ÿ��Ա��ָ��ĳ�Ա����Show_Info(void)
**/
void WorkerManger::Show_Emp()
{
	if (this->m_File_Is_Empty)//�ļ��ձ�־λ
	{
		cout << "�ļ������ڻ�洢Ա����Ϣ���ļ�Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{//���ö�̬����ְ����Ա����ĺ���
			(*(this->m_EmpArray + i))->Show_Info();
		}
	}
	system("pause");
	system("cls");//������Ȼ��while(1)�ֵ��ʼ����
}


/**
������:Emp_Is_Exit(int id);
��;:�ж�Ҫɾ����ְ���Ƿ����
����ֵ:-1����  ���Ա����ָ�������˳��
ʵ�ַ���:�����������id���ڴ洢ָ�������ָ��m_EmpArray�б���Ѱ��
**/
int WorkerManger::Emp_Is_Exit(int id)
{
	int index = -1;//�����־λ
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if ((*(this->m_EmpArray + i))->m_Id == id)
		{
			index = i; //����ָ�������˳��
			break; //�ҵ������Ѱ��
		}
	}
	return index;
}

/**
������:Delet_Ewenmp(void);
��;:���������ְ�����ɾ����ְ��
����ֵ:
ʵ�ַ���:�����������id���ҵ�m_EmpArray�����ָ�룬Ȼ��ɾ��ָ������������(������ǰ�Ƹ��Ƿ���)
**/
void WorkerManger::Delet_Emp(void)
{
	int del_id;
	int idex;//��Ա���ڵ�ָ�������˳��
	if(this->m_File_Is_Empty == true)
	{
		cout << "�ļ������ڻ�洢Ա����Ϣ���ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "����Ҫɾ����Ա�����:" << endl;
		cin >> del_id;
		idex = this->Emp_Is_Exit(del_id);//��m_EmpArrayָ��(ָ������Ķ���ָ��)Ѱ�������������
 		if (idex == -1)
		{
			cout << "ɾ��ʧ��,Ҫɾ����Ա��������!"<<endl;
		}
		else//ְ��������ɾ��ָ������idexλ�õ�ְ��
		{
			cout << "���Ա����ָ������m_EmpArray��˳��Ϊ"<<idex << endl;
			for (int i = idex; i < this->m_EmpNum-1; i++)//�����Ǵ�0��ʼ������ѭ���ĳ���ְ������-1
			{
				//ָ����������ǰ����ɾ������
				*(this->m_EmpArray + i) = *(this->m_EmpArray + i + 1); //ָ�������һ���𽥸���ǰһ��
			}
			this->m_EmpNum--;//��������
			this->Save_Emp();//�����µ�ָ������
			cout << "ɾ���ɹ�!" << endl;
			cout << "����" << this->m_EmpNum << "��Ա��" << endl;
		}

	}
	system("pause");
	system("cls");
}



/**
������:Mod_Emp(int id);
��;:���������ְ����ţ����޸������ŵ�ְ����Ϣ
����ֵ:��
ʵ�ַ���:�����������id���ҵ�m_EmpArray�����ָ�룬delete���������ָ���ŵĶ����������½���workerָ�븳ֵ
**/
void WorkerManger::Mod_Emp()
{
	int del_id;
	int idex = 0;//��Ա���ڵ�ָ�������˳��
	if (this->m_File_Is_Empty)
	{
		cout << "�ļ������ڻ�洢Ա����Ϣ���ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ְ�����:" << endl;
		cin >> del_id;
		idex = this->Emp_Is_Exit(del_id);//��ȡ��Ա����ָ���������˳��
		if (idex == -1)
		{
			cout << "�޸�ʧ��,Ҫ�޸ĵ�Ա��������!" << endl;
		}
		else //����,�޸�Ա����Ϣ
		{
			delete *(this->m_EmpArray + idex); //�ͷ������Աָ��ָ��Ķ���,���¸�ֵ
		//�洢�������ݵ���ʱ����
			int new_id=0;
			string new_name="";
			int new_dep_id=0;//�ǵ�Ҫ��ʼ��
			Worker *worker = NULL;//����ָ��洢�����µ�ְ������ָ��
		//���ո��ĵ�ֵ
			cout << "�鵽ָ�������е�" << idex << "��Ա��" << "�������µ�Ա�����:" << endl;
			cin >> new_id;
			cout << "�������µ�Ա������:" << endl;
			cin >> new_name;
			cout << "�������µ�Ա�����ű�� 1��ͨԱ�� 2���� 3�ϰ�:" << endl;
			cin >> new_dep_id;
			switch (new_dep_id)
			{
				
			case 1:
				worker = new Employee(new_id, new_name, new_dep_id);
				break;      //ʹ�ö�̬�������
			case 2:
				worker = new Manager(new_id, new_name, new_dep_id);
				break;
			case 3:
				worker = new Boss(new_id, new_name, new_dep_id);
				break;
			default:
				cout << "�����д�" << endl;
				return;
				break;
			}
			*(this->m_EmpArray + idex) = worker; //���޸ĵ����ݸ��µ�ָ��������

			this->Save_Emp();//ָ������洢���ļ�
			cout << "�޸ĳɹ�" << endl;
	/*
	Ϊɶ��ֱ�Ӹ��ǣ���Ҫ��delete *(this->m_EmpArray + idex);�ڸ���*(this->m_EmpArray + idex);?
	    ����*(this->m_EmpArray + idex)��ŵ�Emplyee��ָ�룬�޸ĳ�Bossָ�롣�����ĸ�����û���⣬��
	�൱�ڰ�Boss��ʺ������Emplyee��é���ˣ�����д�Ĵ��鹹�캯��Get_Depart(void)��Ȼ�Ǵ�İ�
	��������Ҫ����delete�ڸ��£�����Boss��ʺ������Boss��é����
	*/

		}
	}
	system("pause");
	system("cls");
}



/**
������:Find_Emp_Togther();
��;:��Ϊ���������ҺͰ���Ų���ְ����Ϣ
����ֵ:��
ʵ�ַ���:�����������id�Ͷ�������������ҵ�m_EmpArray�����ָ��
**/
void WorkerManger::Find_Emp_Togther()
{
	int fin_method; //���ҷ�����׼Ϊ
	int id; //�洢����ְ�����
	string nam; //�洢��������
	cout << "������ҷ�����š�1:��ְ����Ų��� 2:��ְ����������" << endl;
	cin >> fin_method;
	if (this->m_File_Is_Empty)
	{
		cout << "�ļ����洢�ڻ��ļ��������޷�����";
		return;
	}
	if (fin_method == 1)
	{
		cout << "��ѡ��1:��ְ����Ų��� " << "������Ҫ���ҵ�ְ����ţ�" << endl;
		cin >> id;
		int index = this->Emp_Is_Exit(id);
		if (index == -1)
		{
			cout << "���ҵ�ְ��������" << endl;
		}
		else
		{
			cout << "���ҳɹ�!" << endl;
			cout << "�����ڴ洢�������е�" << index<<"��,��ϢΪ:"<<endl;
			(*(this->m_EmpArray + index))->Show_Info();
		}
	}
	else if(fin_method == 2)
	{
		cout << "��ѡ��2:��ְ���������� " << "������Ҫ���ҵ�ְ��������" << endl;
		cin >> nam;
		this->Find_Emp_UseName(nam);
	}
	else
	{
		cout << "����Ĳ��ҷ������������������" << endl; 
		system("pause");
		system("cls");
	    return;
	}
	system("pause");
	system("cls");
}
/**
������:Find_Emp_UseName(string nam)
��;:��������ָ�����������
����ֵ:��
ʵ�ַ���:������������������������ҵ�m_EmpArray�����ָ��
**/
void WorkerManger::Find_Emp_UseName(string nam)
{
	int index;
	bool flag = false;//�жϲ����Ƿ�ɹ���־
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if ((*(this->m_EmpArray + i))->m_Name == nam)
		{
			index = this->Emp_Is_Exit((*(this->m_EmpArray + i))->m_Id);
			cout <<"���ҳɹ�!" << "�����ڴ洢�������е�" << index << "��,��ϢΪ:" << endl;
			(*(this->m_EmpArray + i))->Show_Info();
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "���ҵ�ְ��������" << endl;
	}
}





/**
������:Sort_Emp()
��;:����Ա����Ŵ�С��Ա��˳���������
����ֵ:��
ʵ�ַ���:ð�ݷ�/���򷨣���������ָ������m_EmpArray�������
**/
void WorkerManger::Sort_Emp()
{
	if (this->m_File_Is_Empty)//�ļ��ձ�־λ
	{
		cout << "�ļ������ڻ�洢Ա����Ϣ���ļ�Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		int select = 0;
		cout << "��ѡ�������㷨��������.1:ð�ݷ� 2:����" << endl;
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
������:Sort_Bubbling()
��;:ʹ��ð�ݷ���m_EmpArrayָ������������ݰ�ְ���������
����ֵ:��
ʵ�ַ���:ð�ݷ�����for,��for���ƱȽ�����,��for���ƱȽϴ�������������Ԫ�ذ�����,��ľ�������һ��ð��ȥ
**/
void WorkerManger::Sort_Bubbling()
{
	int set = 0;
	cout << "���ʰ������Ż��ǽ�����?����:1 ����:2" << endl;
	cin >> set;
	for (int i = 0; i < this->m_EmpNum; i++) //i���ƱȽ�����
	{
		for (int j = 0; j < this->m_EmpNum - i - 1; j++)//j���ƱȽϴ���(Խ����Ƚϴ���Խ��)
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
	cout << "����ɹ��������Ľ��Ϊ:" << endl;
	this->Save_Emp();
	this->Show_Emp();
}
/**
������:Sort_Select()
��;:ʹ��ѡ�񷨶�m_EmpArrayָ������������ݰ�ְ���������
����ֵ:��
ʵ�ַ���:�ٶ�����ĵ�һ��Ԫ��Ϊ��С���������������Ԫ�رȽϣ�С�˾ͽ���������������ȣ��ٱȵڶ���
**/
void WorkerManger::Sort_Select()
{
	int set = 0;
	cout << "���ʰ������Ż��ǽ�����?����:1 ����:2" << endl;
	cin >> set;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		int min = i; //���谴����ָ��˳��ÿһ��������С��
		for (int j = i + 1; j < this->m_EmpNum; j++)//��iԪ�غ������ʼ������
		{
			if (set == 1)
			{
				if ((*(this->m_EmpArray + min))->m_Id > (*(this->m_EmpArray + j))->m_Id)//�����ֱ�ӻ����
				{
					min = j;
				}
			}
			else if (set == 2)
			{
				if ((*(this->m_EmpArray + min))->m_Id < (*(this->m_EmpArray + j))->m_Id)//�����ֱ�ӻ����
				{
					min = j;
				}
			}
			
		}
		//ÿһ�ֱȽ��꣬�ʼ�϶��Ĳ�����Сֵ���ͽ���ָ�����������
		if (min != i)
		{
			Worker *temp;
			temp = *(this->m_EmpArray + i);  //����Ԫ��
			*(this->m_EmpArray + i) = *(this->m_EmpArray + min);
			*(this->m_EmpArray + min) = temp;
		}
	}
	cout << "����ɹ��������Ľ��Ϊ:" << endl;
	this->Save_Emp();
	this->Show_Emp();
}



/**
������:Clear_All_Emp();
��;:��մ洢������ְ����Ϣ
����ֵ:��
ʵ�ַ���:���������txt�ļ��Ĵ�����������ָ��ָ������ݢ���ն���ָ��(ָ������ָ���ָ��)��������0�ݸ����ļ�Ϊ�ձ�־λ
**/
void WorkerManger::Clear_All_Emp()
{
	string str;
	cout << "�����Ҫ���������Ϣ��������:ɾ������ְ����Ϣ" << endl;
	cin >> str;
	if (str == "ɾ������ְ����Ϣ")
	{
	//���������txt�ļ��Ĵ���
		ofstream ofs;
		ofs.open(SAVEFILENAME, ios::trunc); 
		ofs.close();
	//���������ָ��ָ�������
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (*(this->m_EmpArray + i) != NULL)
			{
				delete *(this->m_EmpArray + i);
			}	
		}
	//����ն���ָ��(ָ������ָ���ָ��)
		if (this->m_EmpArray != NULL)
		{
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
		}
	//��������0
		this->m_EmpNum = 0;
	//�ݸ����ļ�Ϊ�ձ�־λ
		this->m_File_Is_Empty = true;

		cout << "��մ洢������ְ����Ϣ�ɹ�!" << endl;
	}
	else
	{ 
		cout << "������󣬲���ɾ��!" << endl;
	}
	system("pause");
	system("cls");
}

