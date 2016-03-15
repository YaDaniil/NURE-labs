#include <stdio.h>
#include "declaration.h"

int main()
{
    DblLinkedList *phoneBook = createDblLinkedList();
    char rerunProgram;
    do {
        runProgram(phoneBook);
        printf("Do you want to choose another one clouse?\n"
                       "Press 'n' to exit or another key to continue: ");
        rerunProgram = getchar();
        clean();

    } while (rerunProgram != 'n');

    deleteDblLinkedList(phoneBook);

    return 0;
}
