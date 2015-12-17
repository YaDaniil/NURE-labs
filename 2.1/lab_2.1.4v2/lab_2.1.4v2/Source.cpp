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

void powmod2Time(csprng rng, big x, big y, big a, big b, big p, big r){
	ld temp = 999999999.0, min = 0;
	ld sumMin = 0, clock = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 100; j++){

			StartCounter();
			powmod2(x, y, a, b, p, r);
			clock = GetCounter();

			if (clock < temp){
				min = clock;
				temp = min;
			}
		}
	}
	sumMin += min;
	cout << "Time of execution powmod2 routine: " << (ld)sumMin / 1000 << endl;
}

void powmodTime(csprng rng, big x, big y, big a, big b, big p, big dest1, big dest2){
	ld temp = 999999999.0, min = 0;
	ld sumMin = 0, clock = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 100; j++){

			StartCounter();
			powmod(x, y, p, dest1);
			powmod(a, b, p, dest2);
			multiply(dest1, dest2, dest1);
			divide(dest1, p, p);
			clock = GetCounter();

			if (clock < temp){
				min = clock;
				temp = min;
			}
		}
	}
	sumMin += min;
	cout << "Time of execution powmod, powmod, multiply, divide routines: " << (ld)sumMin / 1000 << endl;

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

void PowModTime(csprng rng, big x, big y, big a, big b, big p, big dest1, big dest2){
	ld temp = 999999999.0, min = 0;
	ld sumMin = 0, clock = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 100; j++){

			StartCounter();
			PowMod(x, y, p, dest1);
			PowMod(a, b, p, dest2);
			multiply(dest1, dest2, dest1);
			divide(dest1, p, p);
			clock = GetCounter();

			if (clock < temp){
				min = clock;
				temp = min;
			}
		}
	}
	sumMin += min;
	cout << "Time of execution PowMod, PowMod, multiply, divide routines: " << (ld)sumMin / 1000 << endl;
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
		r = mirvar(1),
		r2 = mirvar(1);
	mip->IOBASE = 16;
	cinstr(p, "6f18544dedb374f5ffbc3bcc7249bb52b09152ec9551dc2c7f6e2853a4db"
	"a914a9bd6e9b70cd54ce31fe7bd3cc61f6d25d45c7fc11a20acc39b8708c9df3ef1d");
	strong_bigrand(&rng, p, x);
	strong_bigrand(&rng, p, a);
	powmod2Time(rng, x, y, a, b, p, r);
	powmodTime(rng, x, y, a, b, p, r, r2);
	PowModTime(rng, x, y, a, b, p, r, r2);
	mirkill(p); mirkill(a); mirkill(r); mirkill(r2);
	mirkill(x); mirkill(y); mirkill(b);
	strong_kill(&rng);
	mirexit();
	cin.get();
	return 0;
}