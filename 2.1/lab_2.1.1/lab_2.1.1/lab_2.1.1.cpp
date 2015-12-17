#include <iostream>
#include <conio.h> 
#include "MMATH.H"
#include "MDEF.H"
#include "DivTest.h"

using namespace std;

void print(M_LONG M) //вывод числа поразрядно
{
	for (int i = 1; i <= M[0]; i++)
	{
		printf("%x ", M[i]);
	}
}

void Binpowmod(M_LONG x, M_LONG k, M_LONG N, M_LONG y)
{
	M_LONG a, b;
	if ((k[0] == 1) && (k[1] == 0)) //если k==1
	{
		y[0] = 1;
		y[1] = 1;
		return; //результат -- 1
	}
	m_copy(y, x);
	int i;
	for (i = 31; !(k[k[0]] & (1 << i)); i--); //поиск старшего еденичного бита в старшем слове
	i--;
	int tmp;
	for (tmp = k[0]; tmp>0; tmp--) { //цикл по словам
		for (i; i >= 0; i--) //цикл по битам
		{
			m_sqr(y, a); //возводим в квадрат y
			m_div(a, N, b, y); //по модулю
			if (k[tmp] & (1 << i)) //если в k-м слове установлен i-й бит
			{
				m_mul(y, x, a); //домножаем y на х
				m_div(a, N, b, y); //по модулю
			}
		}
		i = 31; //на следующей итерации начинаем опять со старшего бита
	};
}

int TLeman(M_LONG P, int k) //тест лемана, все как в прошлой лабе
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

	k, M_LONG P) //генерация простого, тоже кусок 1-й лабы
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
	GenProst(16, 120, P); //генерация простых
	GenProst(16, 120, Q);
	m_mul(P, Q, N); //формируем модуль
	P[1]--;
	Q[1]--;
	m_mul(P, Q, Fn); //фи
	do //все с первой лабы
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
//Проверка работы функции при основании степени 2.
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
	M_LONG n = { 2, 0x6f18544d, 0xedb374f5 }; //модуль
	M_LONG o = { 1, 0 }; //степень
	M_LONG q = { 1, 1 }; //единица
	for (int i = 0; i<11; i++)
	{
		Binpowmod(b, o, n, c);
		m_add(o, q, o); //увеличиваем значение степени на 1
		cout << "result" << i << "-"; //выводим степень
		printf("%x", c[1]); //значение результата
		cout << "\n";
	}
	cin.get();
	return 0;
}
