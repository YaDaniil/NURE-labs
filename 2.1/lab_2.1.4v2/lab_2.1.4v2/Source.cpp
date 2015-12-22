//*********************************The second version of forth lab**********************************************
#include <windows.h>
#include <iostream>
#include <time.h>
extern "C"{
#include "miracl.h"
}
#define MAXLEN 50
#define BASE   0

using namespace std;

typedef long double ld;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter(){
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double GetCounter(){
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void initStrongRng(csprng* Rng){
	srand(time(NULL));
	char raw[100];
	for (int i = 0; i < 100; ++i)
		raw[i] = (char)rand();
	strong_init(Rng, 100, raw, time(NULL));
}

void PowMod(big x, big k, big n, big m){
	int bit = 31;
	for (; !((k->w[k->len - 1] >> bit) & 1); --bit);
	for (int word = k->len - 1; word >= 0; --word){
		for (; bit >= 0; --bit){
			multiply(m, m, m);
			divide(m, n, n);
			if ((k->w[word] >> bit) & 1){
				multiply(m, x, m);
				divide(m, n, n);
			}
		}
		bit = 31;
	}
}

void routinesTime(csprng rng, big x, big y, big a, big b, big p, big r1, big r2, big temp2, big r3, big temp3){
	ld clock1 = 0, clock2 = 0, clock3 = 0;
	ld min1 = 9999999999, min2 = 9999999999, min3 = 9999999999;
	ld sumMin1 = 0, sumMin2 = 0, sumMin3 = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 10; j++){

			StartCounter();
			powmod2(x, y, a, b, p, r1);
			clock1 = GetCounter();
			if (clock1 < min1)
				min1 = clock1;

			StartCounter();
			powmod(x, y, p, r2);
			powmod(a, b, p, temp2);
			multiply(r2, temp2, r2);
			divide(r2, p, p);
			clock2 = GetCounter();
			if (clock2 < min2)
				min2 = clock2;

			StartCounter();
			PowMod(x, y, p, r3);
			PowMod(a, b, p, temp3);
			multiply(r3, temp3, r3);
			divide(r3, p, p);
			clock3 = GetCounter();
			if (clock3 < min3)
				min3 = clock3;
		}
		sumMin1 += min1;
		sumMin2 += min2;
		sumMin3 += min3;
	}
	cout << "Time of execution powmod2 routine: " << (ld)sumMin1 << endl;
	cout << "Time of execution powmod and others routines: " << (ld)sumMin2 << endl;
	cout << "Time of execution PowMod and others routines: " << (ld)sumMin3 << endl;
}

int main()
{
	miracl* mip = mirsys(MAXLEN, BASE);
	csprng rng;
	initStrongRng(&rng);
	big p = mirvar(1),
		x = mirvar(1),
		a = mirvar(1),
		y = mirvar(1),
		b = mirvar(1),
		r1 = mirvar(1),
		r2 = mirvar(1),
		temp2 = mirvar(1),
		r3 = mirvar(1),
		temp3 = mirvar(1);
	mip->IOBASE = 16;
	cinstr(p, "6f18544dedb374f5ffbc3bcc7249bb52b09152ec9551dc2c7f6e2853a4db"
		"a914a9bd6e9b70cd54ce31fe7bd3cc61f6d25d45c7fc11a20acc39b8708c9df3ef1d");
	strong_bigrand(&rng, p, x);
	strong_bigrand(&rng, p, a);
	routinesTime(rng, x, y, a, b, p, r1, r2, temp2, r3, temp3);

	mirkill(p); mirkill(a); mirkill(r1); mirkill(r2);
	mirkill(temp2); mirkill(r3); mirkill(temp3);
	mirkill(x); mirkill(y); mirkill(b);
	mirexit();

	cin.get();
	return 0;
}