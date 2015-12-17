#define MAXLEN 50
#define BASE   0
#include <iostream>
#include <time.h>
extern "C"{
#include "miracl.h"
}

using namespace std;

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
	unsigned clock1 = 0, clock2 = 0, clock3 = 0;
	unsigned min1 = 9999999999, min2 = 9999999999, min3 = 9999999999;
	unsigned sumMin1 = 0, sumMin2 = 0, sumMin3 = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 10; j++){

			__asm rdtsc;
			__asm mov[clock1], eax;
			powmod2(x, y, a, b, p, r1);
			__asm rdtsc;
			__asm sub eax, [clock1];
			__asm mov[clock1], eax;
			if (clock1 < min1)
				min1 = clock1;

			__asm rdtsc;
			__asm mov[clock2], eax;
			powmod(x, y, p, r2);
			powmod(a, b, p, temp2);
			multiply(r2, temp2, r2);
			divide(r2, p, p);
			__asm rdtsc;
			__asm sub eax, [clock2];
			__asm mov[clock2], eax;
			if (clock2 < min2)
				min2 = clock2;

			__asm rdtsc;
			__asm mov[clock3], eax;
			PowMod(x, y, p, r3);
			PowMod(a, b, p, temp3);
			multiply(r3, temp3, r3);
			divide(r3, p, p);
			__asm rdtsc;
			__asm sub eax, [clock3];
			__asm mov[clock3], eax;
			if (clock3 < min3)
				min3 = clock3;
		}
		sumMin1 += min1; // sumMin1 = sumMin1 + min1;
		sumMin2 += min2;
		sumMin3 += min3;
	}
	cout << "Time of execution powmod2 routine: " << (unsigned)sumMin1 / 100.0 << endl;
	cout << "Time of execution powmod and others routines: " << (unsigned)sumMin2 / 100.0 << endl;
	cout << "Time of execution PowMod and others routines: " << (unsigned)sumMin3 / 100.0 << endl;
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




/*

void powmod2Time(csprng rng, big x, big y, big a, big b, big p, big r){
	unsigned clock = 0;
	unsigned temp = 999999999, min = 0;
	ull sumMin = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 100; j++){

			__asm rdtsc;
			__asm mov[clock], eax;
			powmod2(x, y, a, b, p, r);
			__asm rdtsc;
			__asm sub eax, [clock];
			__asm mov[clock], eax;

			if (clock < temp){
				min = clock;
				temp = min;
			}
		}
		sumMin += min;
	}

	cout << "Time of execution powmod2 routine: " << (unsigned)sumMin / 1000 << endl;
}

void powmodTime(csprng rng, big x, big y, big a, big b, big p, big dest1, big dest2){
	unsigned clock = 0;
	unsigned temp = 999999999, min = 0;
	ull sumMin = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 100; j++){

			__asm rdtsc;
			__asm mov[clock], eax;
			powmod(x, y, p, dest1);
			powmod(a, b, p, dest2);
			multiply(dest1, dest2, dest1);
			divide(dest1, p, p);
			__asm rdtsc;
			__asm sub eax, [clock];
			__asm mov[clock], eax;

			if (clock < temp){
				min = clock;
				temp = min;
			}
		}
		sumMin += min;
	}
	cout << "Time of execution powmod and others routines: " << (unsigned)sumMin / 1000 << endl;
}


void PowModTime(csprng rng, big x, big y, big a, big b, big p, big dest1, big dest2){
	unsigned clock = 0;
	unsigned temp = 999999999, min = 0;
	ull sumMin = 0;

	for (register int i = 0; i < 100; i++){
		strong_bigrand(&rng, p, y);
		strong_bigrand(&rng, p, b);
		for (register int j = 0; j < 100; j++){

			__asm rdtsc;
			__asm mov[clock], eax;
			PowMod(x, y, p, dest1);
			PowMod(a, b, p, dest2);
			multiply(dest1, dest2, dest1);
			divide(dest1, p, p);
			__asm rdtsc;
			__asm sub eax, [clock];
			__asm mov[clock], eax;

			if (clock < temp){
				min = clock;
				temp = min;
			}
		}
		sumMin += min;
	}
	cout << "Time of execution PowMod and others routines: " << (unsigned)sumMin / 1000 << endl;
}
*/
/*
big P = mirvar(0x9551dc2c), Q = mirvar(0xba0262f8);
big N = mirvar(0), Fn = mirvar(0), Fn1 = mirvar(0), E = mirvar(0), D = mirvar(0),
C = mirvar(0), m = mirvar(0), m1 = mirvar(0), mes = mirvar(0);
cout << "Message 1 : ";
mip->IOBASE = 10;
cinstr(m, "76523098468935796");
cotnum(m, stdout);
multiply(P, Q, N);
decr(P, 1, P); decr(Q, 1, Q);
multiply(P, Q, Fn);
decr(Fn, 1, Fn1);
do{
strong_bigrand(&rng, Fn1, E);
E->w[0] |= 1;
} while (!xgcd(E, Fn, E, E, E));
//xgcd(D, E, D, D, D);
multi_inverse(1, &E, Fn1, &D);
powmod(m, E, N, C);
powmod(C, D, N, m1);
cout << "\nmessage 2 : "; cotnum(m1, stdout);
if (compare(m, m1))
cout << "\nError!" << endl;
else cout << " \n Successfully" << endl;
mirkill(P); mirkill(Q); mirkill(N); mirkill(Fn);
mirkill(Fn1); mirkill(E); mirkill(D); mirkill(C);
mirkill(m); mirkill(m1);
*/