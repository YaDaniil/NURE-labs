#define MAXLEN 10000        //максимальная длина числа   #define значит что компилятор подставит вместо MAXLEN 10000
#define BASE   0			//основание системы счисления					BASE = 0(256) максимальное

#include <iostream>
#include <ctime>		//для измерения времени работы функций
extern "C"				//через extern "C", потому что библиотека написана на С, а не на С++
{
#include "miracl.h"			//подключение библиотеки
}

using namespace std;


void PowMod(big x, big k, big n, big m)					//наша реализация функции возведения в степень по модулю
{											   			//x - основание, k - степень, n - модуль, m - результат
	int bit = 31;			 							//количество бит
	for (; !((k->w[k->len - 1] >> bit) & 1); --bit);	//сам ничего не понял
	for (int word = k->len - 1; word >= 0; --word)		//идём по словам с конца. Слово - 32-х битовое слово
	{
		for (; bit >= 0; --bit)							//идём по битам слова с конца
		{
			multiply(m, m, m);							//возводим результат в квадрат
			divide(m, n, n);							//берём результат m по модулю n
			if ((k->w[word] >> bit) & 1)				//если старший бит(самый левый) степени = 1
			{
				multiply(m, x, m);						//умножаем m на x
				divide(m, n, n);						//и берём по модулю
			}
		}
		bit = 31;
	}
}


int main()
{
	miracl *mip = mirsys(MAXLEN, BASE);		//инициализация MIRACL
	
	big x, k, n, num;						//объявление больших чисел x - основание, k - степень, n - модуль, num - конечный результат.
	x = mirvar(2);							//инициализация больших чисел x = 2 - основание	
	k = mirvar(1);							//k = 1 - степень
	n = mirvar(0xedb374f56f18544d);			//модуль - два 32-х битных слова
	num = mirvar(1);						//результат = 1
	cout << "Mod =";						//выводим на экран модуль(64-битное слово)
	mip->IOBASE = 10;						//переставляем систему счисления миракла на 10(десятичная)
	cotnum(n, stdout);						//вывод на консоль модуль
	cout << endl;							//переход на новую строку
	
	for (k; k->w[0] <= 100; k->w[0]++)		//цикл для степени от 1 до 100. Возводим 2 в степень от 1 до 100.
	{
		PowMod(x, k, n, num);				//вызов нашей функции возведения в степень по модулю
		cout << "k = "; cotnum(k, stdout);	//вывод на консоль степень 
		cout << "2^k = "; cotnum(num, stdout);//и 2 в степени
		cout << endl;						//переход на новую строку
		num->w[0] = 1;						//обнуляем результат, чтобы каждый раз в степень возводилась двойка, а не предыдущее полученное значение
	}
	
	big base = mirvar(0x10555a11);			//основание - 32-ч битное слово
	big deg = mirvar(1);					//степень = 1
	big result1 = mirvar(1), result2 = mirvar(1);//результаты возведения в степень по модулю разными функциями
	
	csprng Rng;								//объявление генератора ПСЧ
	strong_init(&Rng, strlen("qewhrgioeqGFWE"), "qewhrgioeqGFWE", time(NULL));//его инициализация

	int count = 0;							//счётчик ошибок(несовпадений)
	for (int i = 0; i < 16; ++i)			//цикл от 1 до 16
	{
		strong_bigrand(&Rng, n, deg);		//рандомно генерируем степень, но не больше чем n
		PowMod(base, deg, n, result1);		//возводим в степень по модулю собственной функцией
		powmod(base, deg, n, result2);		//возводим в степень по модулю уже миракловской библиотечной функцией
		if (compare(result1, result2))		//сравниваем разультаты возведения в степень по модулю разными функциями.
			count++;						// Если не совпадение - счётчик ошибок увеличивается на 1
		result1->w[0] = 1;					//обнуляем результат, чтобы каждый раз в степень возводилось наше число(слово), а не предыдущее полученное значение
		result2->w[0] = 1;					//обнуляем результат, чтобы каждый раз в степень возводилось наше число(слово), а не предыдущее полученное значение

							
	}
	
	if (count)								//если ошибки есть
		cout << count << " mismatches" << endl;//выводим их количество
	else                                    //а если нет
		cout << "No mismatches. All results are equal" << endl;//выводим, что их нет
	
	unsigned int start_time1 = clock();		//начало отсчёта времени
	for (int i = 0; i < 10000; ++i)			//1000 раз возводим в степень по модулю нашей функцией
	{
		PowMod(base, deg, n, result1);		//возводим
		result1->w[0] = 1;					//обнуляем результат, чтобы каждый раз в степень возводилось наше число(слово), а не предыдущее полученное значение
	}
	unsigned int end_time1 = clock();		//конец отсчёта времени
	double owrFunctionTime = end_time1 - start_time1;//считаем за сколько времени возвела наша функция

	unsigned int start_time2 = clock();		//начало отсчёта времени
	for (int i = 0; i < 10000; ++i)			//1000 раз возводим в степень по модулю миракловской функцией
	{
		powmod(base, deg, n, result2);		//возводим
		result2->w[0] = 1;					//обнуляем результат, чтобы каждый раз в степень возводилось наше число(слово), а не предыдущее полученное значение
	}
	unsigned int end_time2 = clock();		//конец отсчёта времени
	double miraclFunctionTime = end_time2 - start_time2;//считаем за сколько времени возвела миракловская функция
	
	cout << "Miracle function time: " << miraclFunctionTime / 1000 << "seconds" << endl;//вывод на экран времени в секундах
	cout << "Owr function time: " << owrFunctionTime / 1000 << "seconds" << endl;




	mirkill(x);	mirkill(base);	mirkill(deg);				//удаляем переменные
	mirkill(k); mirkill(result1); mirkill(result2);
	mirkill(n);mirkill(num);
	mirexit();						//завершаем работу с MIRACL
	
						
	system("pause");						//задержка экрана
									
	return 0;
}
















































/*
int main()
{
	srand(time(NULL));																	//вводим рандом
	miracl *mip = mirsys(MAXLEN, BASE);													//инициализация MIRACL
	csprng Rng;																			//объявляем генератор ПСЧ
	char *str = "GYKUGto78tto86tuygoaisgyeofrwiy4oq94yr0q78y98yhUIGUGOU";				//строка, написаная головой по клавиатуре. Используется для генерации ПСЧ
	strong_init(&Rng, strlen(str), str, time(NULL));									//инициализация генератора ПСЧ
	big P = mirvar(0x9551dc2c), Q = mirvar(0xba0262f8);									//инициализация 16-ти битных, простых P и Q
	big N = mirvar(0), Fn = mirvar(0), Fn1 = mirvar(0), E = mirvar(0), D = mirvar(0),	//инициализация других переменных для RSA
		C = mirvar(0), m = mirvar(0), m1 = mirvar(0), mes = mirvar(0);
	char *message = "76523098468935796";												//это мы шифруем
	cout << "Message 1 : ";
	mip->IOBASE = 10;
	//           //????????????????????????????????????????
	cinstr(m, message);										//превращаем строку message в мираколовскую переменную типа big и записываем в переменную m
	//(strlen(message), message, mes);
	cotnum(m, stdout);										//мираколовский вывод на экран. Выводим наше сообщение m
	multiply(P, Q, N);										//формируем модуль: N = P * Q
	decr(P, 1, P); decr(Q, 1, Q);							//отнимаем от P и от Q единичку
	multiply(P, Q, Fn);										//функция Эйлера: Fn = (P - 1) * (Q - 1)
	decr(Fn, 1, Fn1);										//Fn1 = Fn - 1. Это нам понадобится в дальнейшем.
	do														//цикл
	{
		strong_bigrand(&Rng, Fn1, E);						//генерируем случайное число от 0 до Fn1, и записываем в Е
		E->w[0] |= 1;										//обнуляем результат, чтобы каждый раз в степень возводилась двойка, а не предыдущее полученное значение
	} while (!xgcd(E, Fn, E, E, E));	//????????			//цикл до тех пор, пока Е не будет иметь обтаного элемента
	PowMod(m, E, N, C);										//шифруем m ключём Е по модулю N и записываем результат в С
	PowMod(C, D, N, m1);									//расшифровываем С при помощи приватного ключа D по модулю N и записываем результат в m1
	cout << "\nmessage 2 : "; otnum(m1, stdout);			//выводим на экран полученное расшифрованное сообщение m1

	if (compare(m, m1))										//compare - функция сравнивает m и m1					
		cout << "\n Error!";								//если не равны - вывод на экран Error!
	else cout << " \n Successfully";						//если равны - всё удачно
	mirkill(P); mirkill(Q); mirkill(N); mirkill(Fn);		//удаляем наши переменные
	mirkill(Fn1); mirkill(E); mirkill(D); mirkill(C);		//и тут
	mirkill(m); mirkill(m1);;								//и тут
	strong_kill(&Rng);										//удаляем генератор ПСЧ
	mirexit();												//пока Миракл
	system("pause");										//задержка консоли
	return 0;
}
*/