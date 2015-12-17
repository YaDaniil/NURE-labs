#define MAXLEN 10000
#define BASE   0

#include <iostream>
#include <time.h>
extern "C"{
#include "miracl.h"
}

using namespace std;


void initStrongRng(csprng* Rng)
{
	srand(time(NULL));
	char raw[100];
	for (int i = 0; i < 100; ++i)
		raw[i] = (char)rand();
	strong_init(Rng, 100, raw, time(NULL));
}


void formXY(csprng* Rng, big p, big g, big xi, big yi)
{
	do{
		strong_bigrand(Rng, p, xi);
	} while (xi->len == 1 && xi->w[0] < 2);
	powmod(g, xi, p, yi);
}

void signElGamal(csprng* Rng, big p, big g, big xi, big h, big r, big s)
{
	big k = mirvar(1);
	big p1 = mirvar(1);
	big temp = mirvar(1), h1 = mirvar(1);
	
	copy(p, p1);
	decr(p, 1, p1);
	do{
		do{
			do{
				strong_bigrand(Rng, p, k);
			} while (size(k) < 2);
			powmod(g, k, p, r);
			
		} while (xgcd(k, p1, k, k, k) != 1);
		
		multiply(xi, r, temp);
		divide(temp, p1, p1);
		add(h, p1, h1);
		subtract(h1, temp, temp);
		multiply(temp, k, s);
		divide(s, p1, p1);
	} while (size(s) == 0);
}



int verifyElGamal(big p, big g, big yi, big h, big r, big s)
{
	big left = mirvar(1);
	big right = mirvar(1);
	int result;
	powmod(g, h, p, left);
	powmod2(yi, r, r, s, p, right);
	result = compare(left, right);
	mirkill(left); mirkill(right);
	if (result)
		return 1;
	return 0;
}

void hashingStr(char *str, int len, char *hash)
{
	sha512 psh;
	int i;

	shs512_init(&psh);
	for (i = 0; i < len; i++)
		shs512_process(&psh, str[i]);
	shs512_hash(&psh, hash);
}


int main()
{
	miracl *mip = mirsys(MAXLEN, BASE);
	csprng rng;
	big p = mirvar(1);
	big g = mirvar(1);
	initStrongRng(&rng);
	mip->IOBASE = 16;
	cinstr(p, "8DF2A494492276AA3D25759BB06869CBEAC0D83AFB8D0CF7CBB8324F0D7882E5"
		"D0762FC5B7210EAFC2E9ADAC32AB7AAC49693DFBF83724C2EC0736EE31C80291");
	cinstr(g, "626D027839EA0A13413163A55B4CB500299D5522956CEFCB3BFF10F399CE2"
		"C2E71CB9DE5FA24BABF58E5B79521925C9CC42E9F6F464B088CC572AF53E6D78802"); 
	big r = mirvar(1); big xi = mirvar(1);
	big s = mirvar(1); big yi = mirvar(1);
	big H = mirvar(1); big H_fake = mirvar(1); big src = mirvar(1);
	char* src1 = "String for sign";
	char* src2 = "string for sign";
	const int SIZE = 64;
	char message_digest1[70], message_digest2[70];
	hashingStr(src1, strlen(src1), message_digest1);
	hashingStr(src2, strlen(src2), message_digest2);
	formXY(&rng, p, g, xi, yi);
	bytes_to_big(SIZE, message_digest1, H);
	cotnum(H, stdout);cout << endl;
	
	bytes_to_big(SIZE, message_digest2, H_fake);
	cotnum(H_fake, stdout);cout << endl;
	
	if (compare(H, H_fake) == 0)
		return 1;
	else
		cout << "Hash and Fake Hash are different" << endl;
	signElGamal(&rng, p, g, xi, H, r, s);
	int result = verifyElGamal(p, g, yi, H_fake, r, s);

	if (result == 0)
		cout << "El Gamal sign is verified" << endl;
	else
		cout << "El Gamal sign is not verified" << endl;

	mirkill(p); mirkill(g); mirkill(r); mirkill(s);
	mirkill(xi); mirkill(yi); mirkill(H);
	mirexit();
	system("PAUSE");
	return 0;
}