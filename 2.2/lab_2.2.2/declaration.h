#ifndef DOUBLELINKEDLIST_DECLARATION_H
#define DOUBLELINKEDLIST_DECLARATION_H

#include <stdlib.h>

#define NAME_SIZE 11
#define SURNAME_SIZE 21
#define PHONE_SIZE 13

typedef struct _Node {
    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char phoneNumber[PHONE_SIZE];
    struct _Node *next;
    struct _Node *prev;
} Node;


typedef struct _DblLinkedList {
    size_t size;
    Node *head;
    Node *tail;
} DblLinkedList;

DblLinkedList* createDblLinkedList();
void deleteDblLinkedList(DblLinkedList **list);
void addNode(DblLinkedList *list, Node *node);
void deleteNode(DblLinkedList *list, Node *node);
void printDblLinkedList(DblLinkedList *list);


void clean();
int checkNumberCorrectness(char* number);
void displayMenu();
void addEntry(DblLinkedList* list);
void deleteEntry(DblLinkedList* list);
void searchEntry(DblLinkedList* list);
void displayAllEntries(DblLinkedList* list);
void runProgram(DblLinkedList* list);


#endif //DOUBLELINKEDLIST_DECLARATION_H
