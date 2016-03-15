#include <stdio.h>
#include "declaration.h"

int main()
{
    /*
    DblLinkedList *list = createDblLinkedList();
    int a, b, c, d, e, f, g, h;

    a = 10;
    b = 20;
    c = 30;
    d = 40;
    e = 50;
    f = 60;
    g = 70;
    h = 80;
    pushFront(list, &a);
    pushFront(list, &b);
    pushFront(list, &c);
    pushBack(list, &d);
    pushBack(list, &e);
    pushBack(list, &f);
    printDblLinkedList(list, printInt);
    printf("length %d\n", list->size);
    printf("nth 2 %d\n", *((int*)(getNthq(list, 2))->value));
    printf("nth 5 %d\n", *((int*)(getNthq(list, 5))->value));
    printf("popFront %d\n", *((int*)popFront(list)));
    printf("popFront %d\n", *((int*)popFront(list)));
    printf("head %d\n", *((int*)(list->head->value)));
    printf("tail %d\n", *((int*)(list->tail->value)));
    printf("popBack %d\n", *((int*)popBack(list)));
    printf("popBack %d\n", *((int*)popBack(list)));
    printf("length %d\n", list->size);
    printDblLinkedList(list, printInt);
    insert(list, 1, &g);
    printDblLinkedList(list, printInt);
    deleteNth(list, 0);
    printDblLinkedList(list, printInt);
    deleteDblLinkedList(&list);
    */

    DblLinkedList *phoneBook = createDblLinkedList();
    char rerunProgram;
    do {
        runProgram(phoneBook);
        printf("Do you want to choose another one clouse?\n"
                       "Press 'n' to exit or another key to continue: ");
        rerunProgram = getchar();
        clean();

    } while (rerunProgram != 'n');

    getchar();
    return 0;
}
