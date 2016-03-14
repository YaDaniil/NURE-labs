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
        rerunProgramm = getchar();
        clean();

    } while (rerunProgramm != 'n');

    return 0;
}