/*
boss��̬ �̳� ����Worker
��д����Worker�Ĵ��麯��
���캯�����빲��ֵ �� ��дGet_Depart�õ��Լ��Ĳ�������show��ʾ����
*/
#pragma once
#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

class Boss : public Worker //���ּ̳� public private protected
{
public:
	//�вι��캯�� ����
	Boss(int id, string name, int depid);

	//��д���鹹�캯��
	virtual string Get_Depart(void);
	virtual void Show_Info(void);

public:
	/*��Ա�Ǹ���̳еģ����Կ�����*/

};


