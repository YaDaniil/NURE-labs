#ifndef HEADER_H
#define HEADER_H

#define NAME_SIZE 11
#define SURNAME_SIZE 21
#define PHONE_SIZE 13



typedef struct ListNode
{
    char name[NAME_SIZE];
    char surname[SURNAME_SIZE];
    char phoneNumber[PHONE_SIZE];
    struct Node* next;
    struct Node* prev;
}PhoneBook;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

struct Node* head; // global variable - pointer to head node.

//Creates a new Node and returns pointer to it.
struct Node* getNewNode(char* name, char* surname, char phoneNumber);

//Inserts a Node at head of doubly linked list
void InsertAtHead(char* name, char* surname, char* phoneNumber);

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(char* name, char* surname, char* phoneNumber);

//Prints all the elements in linked list in forward traversal order
void print();

void clean();
void displayMenu();
void addEntry();
void deleteEntry();
void searchEntry();
void sortEntries();
void saveInTheFile();
void retrieveFromTheFile();
void displayAllEntries();
void runProgramm();

#endif