#include <iostream>
#include <conio.h> 
#include "MMATH.H"
#include "MDEF.H"
#include "DivTest.h"

using namespace std;

void print(M_LONG M) //����� ����� ����������
{
	for (int i = 1; i <= M[0]; i++)
	{
		printf("%x ", M[i]);
	}
}

void Binpowmod(M_LONG x, M_LONG k, M_LONG N, M_LONG y)
{
	M_LONG a, b;
	if ((k[0] == 1) && (k[1] == 0)) //���� k==1
	{
		y[0] = 1;
		y[1] = 1;
		return; //��������� -- 1
	}
	m_copy(y, x);
	int i;
	for (i = 31; !(k[k[0]] & (1 << i)); i--); //����� �������� ���������� ���� � ������� �����
	i--;
	int tmp;
	for (tmp = k[0]; tmp>0; tmp--) { //���� �� ������
		for (i; i >= 0; i--) //���� �� �����
		{
			m_sqr(y, a); //�������� � ������� y
			m_div(a, N, b, y); //�� ������
			if (k[tmp] & (1 << i)) //���� � k-� ����� ���������� i-� ���
			{
				m_mul(y, x, a); //��������� y �� �
				m_div(a, N, b, y); //�� ������
			}
		}
		i = 31; //�� ��������� �������� �������� ����� �� �������� ����
	};
}

int TLeman(M_LONG P, int k) //���� ������, ��� ��� � ������� ����
{
	M_LONG P1, P2, a, R;
	int g = 0;
	m_copy(P1, P);
	P1[1]--;
	m_copy(P2, P1);
	m_shr(P2, 1);
	for (int i = 0; i<k; i++)
	{
		m_rand(a, P[0] - 1);
		Binpowmod(a, P2, P, R);
		if ((R[0] != 1) || (R[1] != 1))
		{
			if (m_cmp(R, P1) == 0)
				g++;
			else
				return 1;
		}
	}
	if (g != 0)
	{
		return 0;
	}
	return 1;
}

void GenProst(int l, int

	k, M_LONG P) //��������� ��������, ���� ����� 1-� ����
{
	m_rand(P, l);
	M_LONG two = { 1, 2 };
	P[1] |= 1;
	while ((DivTest(P)) || (TLeman(P, k)))
		m_add(P, two, P);
}


int main()
{
	M_LONG P, Q, N, Fn, E, D, C, M = { 3, 0x6f18544d, 0xedb374f5, 0xffbc3bcc }, M1;
	cout << "message 1 : ";
	print(M);
	GenProst(16, 120, P); //��������� �������
	GenProst(16, 120, Q);
	m_mul(P, Q, N); //��������� ������
	P[1]--;
	Q[1]--;
	m_mul(P, Q, Fn); //��
	do //��� � ������ ����
	{
		m_rand(E, Fn[0] - 1);
		E[1] |= 1;
	} while (m_inv(E, Fn, D));
	Binpowmod(M, E, N, C);
	Binpowmod(C, D, N, M1);
	cout << "\nmessage 2 : ";
	print(M1);
	if (m_cmp(M, M1))
		cout << "\n error!";
	else cout << " \n successfully";
	m_zero(P, P[0]);
	m_zero(Q, Q[0]);
	m_zero(Fn, Fn[0]);
	m_zero(E, E[0]);
	m_zero(D, D[0]);
	cin.get();
	return 0;
}
//�������� ������ ������� ��� ��������� ������� 2.
void Binpowmod(M_LONG x, M_LONG k, M_LONG N, M_LONG y)
{
	M_LONG a, b;
	if ((k[0] == 1) && (k[1] == 0))
	{
		y[0] = 1;
		y[1] = 1;
		return;
	}
	m_copy(y, x);
	int i;
	for (i = 31; !(k[k[0]] & (1 << i)); i--);
	i--;
	int tmp;
	for (tmp = k[0]; tmp>0; tmp--) {
		for (i; i >= 0; i--)
		{
			m_sqr(y, a);
			m_div(a, N, b, y);
			if (k[tmp] & (1 << i))
			{
				m_mul(y, x, a);
				m_div(a, N, b, y);
			}
		}
		i = 31;
	};
}

int main()
{
	M_LONG c, b = { 1, 2 };
	M_LONG n = { 2, 0x6f18544d, 0xedb374f5 }; //������
	M_LONG o = { 1, 0 }; //�������
	M_LONG q = { 1, 1 }; //�������
	for (int i = 0; i<11; i++)
	{
		Binpowmod(b, o, n, c);
		m_add(o, q, o); //����������� �������� ������� �� 1
		cout << "result" << i << "-"; //������� �������
		printf("%x", c[1]); //�������� ����������
		cout << "\n";
	}
	cin.get();
	return 0;
}
