/*
.hͷ�ļ�Ҫ��ʲô��
1.��������   ��cpp��������
2.h��������������Ա��������Ա����   ��cpp�ﶨ���Ա����
3.ͷ�ļ�����
*/
/*
1.�����ฺ������
	(1)���û���ͨ�Ľ���˵�
	(2)��ְ���������Ӳ���
	(3)TXT�ļ���д����
*/


#pragma once   //== #ifndef  #define  #endif
#include <iostream> //���������ͷ�ļ�
#include <stdlib.h>
#include <iomanip>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream> //�ļ�����ͷ�ļ�
#define   SAVEFILENAME    "employeeFILE.txt" //�궨��洢���ļ���

class WorkerManger
{
public:
	WorkerManger();  //���캯��    ��дĬ�����ɹ��졢�������졢��������ֵ���������
									  //��ֵ�������������������һһ��ֵ��,�������(��)Ҫ��д��ֵ���������
	~WorkerManger(); //����

//��ʾ���û���ͨ�Ľ���˵��ӿ�(����)
	void Show_Menu();
//0:�˳�ְ������ϵͳ�ӿ�(����)
	void ExitSystem();

//1:���ӹ���Ա����Ϣ(����)
	void Add_Emp();
//1.1��Txt�ļ��ﱣ��ְ����Ϣ
	void Save_Emp();

//2:�õ��ļ����Ա������
	int Get_EmpNumb();
//2.1����ʼ��ְ��������������ԭ���ļ���洢��ְ��ȫ������
	void Init_Emp();
//2.2����ʾ�����ļ��������ְ����Ϣ
	void Show_Emp();

//3:ɾ����ְְ����Ϣ (�ж�ְ���Ƿ���ڣ���ɾ��)
//3.1�ж�ְ���Ƿ����
	int Emp_Is_Exit(int id);
//3.2ɾ��ְ��
	void Delet_Emp();

//4:�޸�ְ����Ϣ
	void Mod_Emp();

//5:����ְ����Ϣ,��Ϊ���������ҺͰ���Ų���
	void Find_Emp_Togther(void);
//5.1 ����������
	void Find_Emp_UseName(string nam);

//6:����ְ���������
	void Sort_Emp();
//6.1ѡ������
	void Sort_Bubbling();
//6.2ð�ݷ�����
	void Sort_Select();

//7:ɾ������ְ����Ϣ
	void Clear_All_Emp();


public:
//1:���ӹ���Ա����Ϣ
	int m_EmpNum; //ְ������
	Worker ** m_EmpArray; //��ΪҪ��ְ����Ϣ�����ڶ���(ջ���Ͷ�ʧ��),����new������ְ������ָ��Ҫ���һ������
						  //����һ������Workerָ����ɵ�ָ�����飬���������ڴ�� new�����Ķ��Ա������ָ��
	                      //���ָ������ҲҪ����ڶ���������Ҫnew(ָ������)��������ͳ���ָ��ָ���ָ�룬���Խ���һ��Worker**���洢
//�ж��ļ������Ƿ�Ϊ��
	bool m_File_Is_Empty;//�ļ���ʼ����ʱ����ж�
};

