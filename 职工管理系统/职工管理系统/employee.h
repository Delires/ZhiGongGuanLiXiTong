/*
��̬���̳�Worker����
Ŀ������ʾemployee������:��λ���ƣ���λְ��
��д���麯��
*/
#pragma once
#include <iostream> 
#include <string>
#include "worker.h" //��̬�����ͷ�ļ�
using namespace std;
//��̬�̳�Worker
class Employee : public Worker  //�̳е����ַ�ʽ:public protected private ����������ʲô��?
{
public:
//���캯������Ա��ֵ
	Employee(int id, string name, int depid);

//��д���麯������������Ҳ�ǳ�����
	virtual void Show_Info(void);
	virtual string Get_Depart(void);

public:
	 /*��Ա�Ǹ���̳еģ����Կ�����*/
};




/*
1.�̳е����ַ�ʽ:public protected private ����������ʲô��?
  �����̳�public    :���ܼ̳и����private���̳к��������Ա��Ȩ�޼�������
  ˽�м̳�private   :���ܼ̳и����private���̳к��������Ա��Ȩ��Ϊprivate
  �����̳�protected :���ܼ̳и����private���̳к�������ĳ�ԱȨ��Ϊprotected������������Լ̳�protected
*/