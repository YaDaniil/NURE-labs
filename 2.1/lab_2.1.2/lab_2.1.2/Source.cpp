#define MAXLEN 10000        //������������ ����� �����   #define ������ ��� ���������� ��������� ������ MAXLEN 10000
#define BASE   0			//��������� ������� ���������					BASE = 0(256) ������������

#include <iostream>
#include <ctime>		//��� ��������� ������� ������ �������
extern "C"				//����� extern "C", ������ ��� ���������� �������� �� �, � �� �� �++
{
#include "miracl.h"			//����������� ����������
}

using namespace std;


void PowMod(big x, big k, big n, big m)					//���� ���������� ������� ���������� � ������� �� ������
{											   			//x - ���������, k - �������, n - ������, m - ���������
	int bit = 31;			 							//���������� ���
	for (; !((k->w[k->len - 1] >> bit) & 1); --bit);	//��� ������ �� �����
	for (int word = k->len - 1; word >= 0; --word)		//��� �� ������ � �����. ����� - 32-� ������� �����
	{
		for (; bit >= 0; --bit)							//��� �� ����� ����� � �����
		{
			multiply(m, m, m);							//�������� ��������� � �������
			divide(m, n, n);							//���� ��������� m �� ������ n
			if ((k->w[word] >> bit) & 1)				//���� ������� ���(����� �����) ������� = 1
			{
				multiply(m, x, m);						//�������� m �� x
				divide(m, n, n);						//� ���� �� ������
			}
		}
		bit = 31;
	}
}


int main()
{
	miracl *mip = mirsys(MAXLEN, BASE);		//������������� MIRACL
	
	big x, k, n, num;						//���������� ������� ����� x - ���������, k - �������, n - ������, num - �������� ���������.
	x = mirvar(2);							//������������� ������� ����� x = 2 - ���������	
	k = mirvar(1);							//k = 1 - �������
	n = mirvar(0xedb374f56f18544d);			//������ - ��� 32-� ������ �����
	num = mirvar(1);						//��������� = 1
	cout << "Mod =";						//������� �� ����� ������(64-������ �����)
	mip->IOBASE = 10;						//������������ ������� ��������� ������� �� 10(����������)
	cotnum(n, stdout);						//����� �� ������� ������
	cout << endl;							//������� �� ����� ������
	
	for (k; k->w[0] <= 100; k->w[0]++)		//���� ��� ������� �� 1 �� 100. �������� 2 � ������� �� 1 �� 100.
	{
		PowMod(x, k, n, num);				//����� ����� ������� ���������� � ������� �� ������
		cout << "k = "; cotnum(k, stdout);	//����� �� ������� ������� 
		cout << "2^k = "; cotnum(num, stdout);//� 2 � �������
		cout << endl;						//������� �� ����� ������
		num->w[0] = 1;						//�������� ���������, ����� ������ ��� � ������� ����������� ������, � �� ���������� ���������� ��������
	}
	
	big base = mirvar(0x10555a11);			//��������� - 32-� ������ �����
	big deg = mirvar(1);					//������� = 1
	big result1 = mirvar(1), result2 = mirvar(1);//���������� ���������� � ������� �� ������ ������� ���������
	
	csprng Rng;								//���������� ���������� ���
	strong_init(&Rng, strlen("qewhrgioeqGFWE"), "qewhrgioeqGFWE", time(NULL));//��� �������������

	int count = 0;							//������� ������(������������)
	for (int i = 0; i < 16; ++i)			//���� �� 1 �� 16
	{
		strong_bigrand(&Rng, n, deg);		//�������� ���������� �������, �� �� ������ ��� n
		PowMod(base, deg, n, result1);		//�������� � ������� �� ������ ����������� ��������
		powmod(base, deg, n, result2);		//�������� � ������� �� ������ ��� ������������ ������������ ��������
		if (compare(result1, result2))		//���������� ���������� ���������� � ������� �� ������ ������� ���������.
			count++;						// ���� �� ���������� - ������� ������ ������������� �� 1
		result1->w[0] = 1;					//�������� ���������, ����� ������ ��� � ������� ����������� ���� �����(�����), � �� ���������� ���������� ��������
		result2->w[0] = 1;					//�������� ���������, ����� ������ ��� � ������� ����������� ���� �����(�����), � �� ���������� ���������� ��������

							
	}
	
	if (count)								//���� ������ ����
		cout << count << " mismatches" << endl;//������� �� ����������
	else                                    //� ���� ���
		cout << "No mismatches. All results are equal" << endl;//�������, ��� �� ���
	
	unsigned int start_time1 = clock();		//������ ������� �������
	for (int i = 0; i < 10000; ++i)			//1000 ��� �������� � ������� �� ������ ����� ��������
	{
		PowMod(base, deg, n, result1);		//��������
		result1->w[0] = 1;					//�������� ���������, ����� ������ ��� � ������� ����������� ���� �����(�����), � �� ���������� ���������� ��������
	}
	unsigned int end_time1 = clock();		//����� ������� �������
	double owrFunctionTime = end_time1 - start_time1;//������� �� ������� ������� ������� ���� �������

	unsigned int start_time2 = clock();		//������ ������� �������
	for (int i = 0; i < 10000; ++i)			//1000 ��� �������� � ������� �� ������ ������������ ��������
	{
		powmod(base, deg, n, result2);		//��������
		result2->w[0] = 1;					//�������� ���������, ����� ������ ��� � ������� ����������� ���� �����(�����), � �� ���������� ���������� ��������
	}
	unsigned int end_time2 = clock();		//����� ������� �������
	double miraclFunctionTime = end_time2 - start_time2;//������� �� ������� ������� ������� ������������ �������
	
	cout << "Miracle function time: " << miraclFunctionTime / 1000 << "seconds" << endl;//����� �� ����� ������� � ��������
	cout << "Owr function time: " << owrFunctionTime / 1000 << "seconds" << endl;




	mirkill(x);	mirkill(base);	mirkill(deg);				//������� ����������
	mirkill(k); mirkill(result1); mirkill(result2);
	mirkill(n);mirkill(num);
	mirexit();						//��������� ������ � MIRACL
	
						
	system("pause");						//�������� ������
									
	return 0;
}
















































/*
int main()
{
	srand(time(NULL));																	//������ ������
	miracl *mip = mirsys(MAXLEN, BASE);													//������������� MIRACL
	csprng Rng;																			//��������� ��������� ���
	char *str = "GYKUGto78tto86tuygoaisgyeofrwiy4oq94yr0q78y98yhUIGUGOU";				//������, ��������� ������� �� ����������. ������������ ��� ��������� ���
	strong_init(&Rng, strlen(str), str, time(NULL));									//������������� ���������� ���
	big P = mirvar(0x9551dc2c), Q = mirvar(0xba0262f8);									//������������� 16-�� ������, ������� P � Q
	big N = mirvar(0), Fn = mirvar(0), Fn1 = mirvar(0), E = mirvar(0), D = mirvar(0),	//������������� ������ ���������� ��� RSA
		C = mirvar(0), m = mirvar(0), m1 = mirvar(0), mes = mirvar(0);
	char *message = "76523098468935796";												//��� �� �������
	cout << "Message 1 : ";
	mip->IOBASE = 10;
	//           //????????????????????????????????????????
	cinstr(m, message);										//���������� ������ message � ������������� ���������� ���� big � ���������� � ���������� m
	//(strlen(message), message, mes);
	cotnum(m, stdout);										//������������� ����� �� �����. ������� ���� ��������� m
	multiply(P, Q, N);										//��������� ������: N = P * Q
	decr(P, 1, P); decr(Q, 1, Q);							//�������� �� P � �� Q ��������
	multiply(P, Q, Fn);										//������� ������: Fn = (P - 1) * (Q - 1)
	decr(Fn, 1, Fn1);										//Fn1 = Fn - 1. ��� ��� ����������� � ����������.
	do														//����
	{
		strong_bigrand(&Rng, Fn1, E);						//���������� ��������� ����� �� 0 �� Fn1, � ���������� � �
		E->w[0] |= 1;										//�������� ���������, ����� ������ ��� � ������� ����������� ������, � �� ���������� ���������� ��������
	} while (!xgcd(E, Fn, E, E, E));	//????????			//���� �� ��� ���, ���� � �� ����� ����� �������� ��������
	PowMod(m, E, N, C);										//������� m ������ � �� ������ N � ���������� ��������� � �
	PowMod(C, D, N, m1);									//�������������� � ��� ������ ���������� ����� D �� ������ N � ���������� ��������� � m1
	cout << "\nmessage 2 : "; otnum(m1, stdout);			//������� �� ����� ���������� �������������� ��������� m1

	if (compare(m, m1))										//compare - ������� ���������� m � m1					
		cout << "\n Error!";								//���� �� ����� - ����� �� ����� Error!
	else cout << " \n Successfully";						//���� ����� - �� ������
	mirkill(P); mirkill(Q); mirkill(N); mirkill(Fn);		//������� ���� ����������
	mirkill(Fn1); mirkill(E); mirkill(D); mirkill(C);		//� ���
	mirkill(m); mirkill(m1);;								//� ���
	strong_kill(&Rng);										//������� ��������� ���
	mirexit();												//���� ������
	system("pause");										//�������� �������
	return 0;
}
*/