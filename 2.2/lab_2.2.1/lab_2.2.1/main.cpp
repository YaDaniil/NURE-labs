#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	char rerunProgramm = '\0';
	do {
		runProgramm();
		printf("Do you want to choose another one clouse?\n"
			   "Press 'n' to exit or another button to continue: ");
		scanf("%1s", &rerunProgramm);
		fflush(stdin);
		if (rerunProgramm == 'n')
			exit(0);
	} while (rerunProgramm != 'n');
	
	return 0;
}