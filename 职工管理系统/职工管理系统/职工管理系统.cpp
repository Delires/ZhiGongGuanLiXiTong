/*
main()������ʲô��
1.���ý�����.h�ļ���ʹ�ø����ཨ������
*/
#include <iostream>
using namespace std;
#include "workerManger.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

//���Զ�̬!!������ԱWorker��:�ϰ塢����Ա��
void test_Worker(void)
{
	Worker *w1 = new Employee(001, "����", 1);//���ŷ�����������ֵ ��������
	w1->Show_Info(); 
	delete(w1); //����ɾ������ֹ����й©

	Worker *w2 = new Manager(002, "����", 2);//���ŷ�����������ֵ
	w2->Show_Info();
	delete(w2);

	Worker *w3 = new Boss(9527, "����", 3);//���ŷ�����������ֵ
	w3->Show_Info();
	delete(w3);
}

int main(void)
{
	int ret;
	int choice; //�洢�û������빦�ܱ��
	WorkerManger wm; //ʵ���� ������
	

	while (true)//��ѭ��,����һֱ����
	{
		wm.Show_Menu();//չʾ�˵�
		cout << "�����빦�����:" << endl;
		cin >> choice; //��������ִ��빦��ѡ����
		switch (choice)
		{
			case 0: //0:�˳�ְ���������
				cout << "��ѡ���˹���0:�˳�ְ���������" << endl;
				wm.ExitSystem();
				break;
			case 1: //1:���ӹ���Ա����Ϣ
				cout << "��ѡ���˹���1:���ӹ���Ա����Ϣ" << endl;
				wm.Add_Emp();
				break;
			case 2: //2:��ʾְ����Ϣ
				cout << "��ѡ���˹���2:��ʾְ����Ϣ" << endl;
				wm.Show_Emp();
				break;
			case 3: //3:ɾ����ְְ����Ϣ   (�ж�ְ���Ƿ���ڣ���ɾ��)
				cout << "��ѡ���˹���3:ɾ����ְְ����Ϣ " << endl;
				wm.Delet_Emp();//320
				break;
			case 4: //4:�޸�ְ����Ϣ
				cout << "��ѡ���˹���4:�޸�ְ����Ϣ " << endl;
				wm.Mod_Emp();
				break;
			case 5: //5:����ְ����Ϣ
				cout << "��ѡ���˹���5:����ְ����Ϣ " << endl;
				wm.Find_Emp_Togther();
				break;
			case 6: //6:����ְ���������
				cout << "��ѡ���˹���6:����ְ��������� " << endl;
				wm.Sort_Emp();
				break;
			case 7: //7:ɾ������ְ����Ϣ
				cout << "��ѡ���˹���7:ɾ������ְ����Ϣ " << endl;
				wm.Clear_All_Emp();
				break;
			default: //��������
				system("cls"); //�����Ļ,������ִ�while��ʼ,��wm.Show_Menu();չʾ�˵�
				break;
		}
	}

	system("pause");
	return 0;
}