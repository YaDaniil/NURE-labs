#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "declaration.h"


DblLinkedList* createDblLinkedList()
{
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}

void deleteDblLinkedList(DblLinkedList **list)
{
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}



void pushFront(DblLinkedList *list, char* name, char* surname, char* phoneNumber)
{
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    strcpy(tmp->name, name);
    strcpy(tmp->surname, surname);
    strcpy(tmp->phoneNumber, phoneNumber);
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}


Node* popFront(DblLinkedList *list)
{
    Node *prev;
    Node* tmp;
    if (list->head == NULL) {
        exit(2);
    }

    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }

    strcpy(tmp->name, prev->name);
    strcpy(tmp->surname, prev->surname);
    strcpy(tmp->phoneNumber, prev->phoneNumber);

    free(prev);

    list->size--;
    return tmp;
}


void pushBack(DblLinkedList *list, char* name, char* surname, char* phoneNumber)
{
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    strcpy(tmp->name, name);
    strcpy(tmp->surname, surname);
    strcpy(tmp->phoneNumber, phoneNumber);

    tmp->next = NULL;
    tmp->prev = list->tail;

    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

Node* popBack(DblLinkedList *list)
{
    Node *next;
    Node* tmp;
    if (list->tail == NULL) {
        exit(4);
    }

    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    strcpy(tmp->name, next->name);
    strcpy(tmp->surname, next->surname);
    strcpy(tmp->phoneNumber, next->phoneNumber);
    free(next);

    list->size--;
    return tmp;
}

Node* getNthq(DblLinkedList *list, size_t index)
{
    Node *tmp = NULL;
    size_t i;

    if (index < list->size/2) {
        i = 0;
        tmp = list->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    } else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }

    return tmp;
}


void insert(DblLinkedList *list, size_t index, char* name, char* surname, char* phoneNumber)
{
    Node *elm = NULL;
    Node *ins = NULL;
    elm = getNthq(list, index);
    if (elm == NULL) {
        exit(5);
    }
    ins = (Node*) malloc(sizeof(Node));
    strcpy(ins->name, name);
    strcpy(ins->surname, surname);
    strcpy(ins->phoneNumber, phoneNumber);
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;

    if (!elm->prev) {
        list->head = elm;
    }
    if (!elm->next) {
        list->tail = elm;
    }

    list->size++;
}

Node* deleteNth(DblLinkedList *list, size_t index)
{
    Node *elm = NULL;
    Node *tmp = NULL;

    elm = getNthq(list, index);
    if (elm == NULL) {
        exit(5);
    }
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }

    strcpy(tmp->name, elm->name);
    strcpy(tmp->surname, elm->surname);
    strcpy(tmp->phoneNumber, elm->phoneNumber);

    if (!elm->prev) {
        list->head = elm->next;
    }
    if (!elm->next) {
        list->tail = elm->prev;
    }

    free(elm);

    list->size--;

    return tmp;
}

void printDblLinkedList(DblLinkedList *list)
{
    Node* tmp = list->head;
    printf("You have %d contacts:\n", (int) list->size);
    while(tmp != NULL) {
        printf("Name: %s\n", tmp->name);
        printf("Surname: %s\n", tmp->surname);
        printf("Phone number %s\n\n", tmp->phoneNumber);
        tmp = tmp->next;
    }
    printf("\n");
}



void clean()
{
    while ( getchar() != '\n' );
}

int checkNumberCorrectness(char* number)
{
    if (strlen(number) > PHONE_SIZE - 1)
        return 0;
    for (int i = 0; i < strlen(number); i++) {
        if (number[i] == '-' || !isdigit(number[i])) {
            puts("The phone number is invalid.");
            return 0;
        }
        return 1;
    }
}

void displayMenu()
{
    puts("\n\t\t\t********Phone Book Manager********\n");
    puts("1. Add entry\n");
    puts("2. Delete entry\n");
    puts("3. Search entry\n");
    puts("4. Display all entries\n");
    puts("5. Sort entries\n");
    puts("6. Save in the file\n");
    puts("7. Retrieve from the file\n");
    puts("8. Exit program\n");
}

void addEntry(DblLinkedList* list)
{
    char* name;// = "\0";
    char* surname;// = "\0";
    char* phoneNumber;// = "\0";
    printf("Input a name: ");
    scanf("%10s", &name);
    clean();
    printf("Input a surname: ");
    scanf("%20s", &surname);
    clean();

    do {
        printf("Input a phone number: ");
        scanf("%12s", &phoneNumber);
    } while (!checkNumberCorrectness(&phoneNumber));
    clean();

    /*
    This doesn't work!! Exit code 139(segmentation fault)
    Node* tmp = list->head;

    while(tmp != NULL) {
        if (!strcmp(phoneNumber, tmp->phoneNumber)) {
            puts("Cannot be added to the phone book");
            puts("The contact with this phone number is already exist.");
            return;
        }
        tmp = tmp->next;
    }
*/
    pushBack(list, &name, &surname, &phoneNumber);

    puts("A new contact was successfully added\n");
}

void deleteEntry(DblLinkedList* list)
{
    if (list->size == 0) {
        puts("The phone book is empty. There is nothing to delete.");
        return;
    }

    char numberToDelete[PHONE_SIZE];
    do {
        printf("Enter a phone number to remove the contact: ");
        scanf("%12s", numberToDelete);
    } while (!checkNumberCorrectness(numberToDelete));

    for (int i = 0; i < list->size; i++) {
        if (!strcmp(getNthq(list, i)->phoneNumber, numberToDelete)) {
            puts("The contact below will be deleted.");
            printf("Name: %s\n", getNthq(list, i)->name);
            printf("Surname: %s\n",  getNthq(list, i)->surname);
            printf("Phone number: %s\n\n", getNthq(list, i)->phoneNumber);
            deleteNth(list, (size_t) i);
            break;
        }
        else
            puts("There is no existing contact in phone book\n");
    }
}

void displayAllEntries(DblLinkedList* list)
{
    if (list->size == 0) {
        puts("Your phone book is empty.\n");
        return;
    }
    if (list->size == 1) {
        puts("There is 1 contact in your phone book.\n\n");
        printf("Name: %s\n", list->head->name);
        printf("Surname: %s\n", list->head->surname);
        printf("Phone number %s\n\n", list->head->phoneNumber);
    }
    else {
        printDblLinkedList(list);
    }
}

void searchEntry(DblLinkedList* list)
{
    if (list->size == 0) {
        puts("The phone book is empty!");
        puts("Add some contacts to search.\n");
        return;
    }
    char searchBySurname[SURNAME_SIZE];
    printf("Input the surname to search and display contact:");
    scanf("%20s", &searchBySurname);
    clean();

    Node* tmp = list->head;
    while(tmp != NULL) {
        if (!strcmp(tmp->surname, searchBySurname)) {
            puts("The contact is found!");
            printf("Name: %s\n", tmp->name);
            printf("Surname: %s\n", tmp->surname);
            printf("Phone number %s\n\n", tmp->phoneNumber);
            break;
        }else
            puts("There is no existing contact in phone book\n");
        tmp = tmp->next;
    }
}


void sortEntries(DblLinkedList *list)
{
    Node *tmp, *current, *next;
    int count = list->size;
    for(int i = 0; i < count; i++)
    {
        current = list->head;
        for(int j = 0; j < count - 1 - i; j++ )
        {
            if(strcmp(current->surname, current->next->surname) > 0 ||
                        (strcmp(current->surname, current->next->surname) == 0 &&
                            strcmp(current->name, current->next->name) > 0))
            {
                next = current->next;
                current->next = next->next;
                next->next = current;
                if(current == list->head)
                {
                    list->head = next;
                    current = next;
                }
                else
                {
                    current = next;
                    tmp->next = next;
                }
            }
            tmp = current;
            current = current->next;
        }
    }

    puts("The sort of the phone book was completed successfully\n");
}


void saveInTheFile(DblLinkedList* list)
{
    puts("Save");
    FILE* file = fopen("/home/yadaniil/phone.dat", "a");
    if(!file) {
        puts("ERROR. The file cannot be opened");
        return;
    }

    Node* tmp = list->head;
    while(tmp) {
        fprintf(file, "Name: %s\n", tmp->name);
        fprintf(file, "Surname: %s\n", tmp->surname);
        fprintf(file, "Phone number: %s\n\n", tmp->phoneNumber);
        tmp = tmp->next;
    }
    fclose(file);

    puts("Your contacts have been successfully written to the file : \"phone.dat\"");
}

void retrieveFromTheFile(DblLinkedList* list)
{
    FILE* file = fopen("/home/yadaniil/phone.dat", "rb");
    if(!file) {
        puts("ERROR. The file cannot be opened");
        return;
    }

    Node *tmp = list->head;
    char *name, *surname, *phoneNumber;
    char *str;

    while (!feof(file)) {
        fscanf(file, "%s %s", &str, &name);
        fscanf(file, "%s %s", &str, &surname);
        fscanf(file, "%s %s %s", &str, &str, &phoneNumber);
        printf("%s\n", name);
        printf("%s\n", surname);
        printf("%s\n\n", phoneNumber);
        puts("koko");
        pushBack(list, &name, &surname, &phoneNumber);
        puts("moloko");
        tmp = tmp->next;
    }

    fclose(file);
    puts("Your contacts have been successfully retrieved from the file : \"phone.dat\"");
}

void runProgram(DblLinkedList *list)
{
    displayMenu();
    char choice = 0;

    do {
        printf("Select an appropriate clause: ");
        scanf("%1c", &choice);
        clean();

        switch (choice) {
            case '1':
                addEntry(list);
                break;
            case '2':
                deleteEntry(list);
                break;
            case '3':
                searchEntry(list);
                break;
            case '4':
                displayAllEntries(list);
                break;
            case '5':
                sortEntries(list);
                break;
            case '6':
                saveInTheFile(list);
                break;
            case '7':
                retrieveFromTheFile(list);
                break;
            case '8':
                exit(0);
            default:
                puts("Input parameters are incorrect. Try again.");
        }
    } while (choice < '1' || choice > '8');
}