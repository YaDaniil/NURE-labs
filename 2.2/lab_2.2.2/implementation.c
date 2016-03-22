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


void addNode(DblLinkedList *list, Node *node)
{
    if(!list->head) {
        list->head = node;
        list->tail = node;
        node->next = NULL;
        node->prev = NULL;
    }else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->size++;
}


void printDblLinkedList(DblLinkedList *list)
{
    Node* tmp = list->head;
    printf("You have %d contacts:\n\n", list->size);
    while(tmp) {
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


void addEntry(DblLinkedList * list)
{
    Node *current = malloc(sizeof(Node));

    if(!current)
        return;

    printf("Input a name: ");
    scanf("%10s", current->name);
    clean();
    printf("Input a surname: ");
    scanf("%20s", current->surname);
    clean();

    do {
        printf("Input a phone number: ");
        scanf("%12s", current->phoneNumber);
    } while (!checkNumberCorrectness(current->phoneNumber));
    clean();

    Node* tmp = list->head;

    while(tmp) {
        if (!strcmp(current->phoneNumber, tmp->phoneNumber)) {
            puts("Cannot be added to the phone book");
            puts("The contact with this phone number is already exist.");
            return;
        }
        tmp = tmp->next;
    }
    addNode(list, current);
    puts("A new contact was successfully added\n");

}

void deleteNode(DblLinkedList *list, Node *node)
{
    if(list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else if(node == list->head) {
        list->head = list->head->next;
        free(list->head->prev);
        list->head->prev = NULL;
    } else if(node == list->tail) {
        list->tail = list->tail->prev;
        free(list->tail->next);
        list->tail->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node);
    }
    list->size--;
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

    Node *tmp = list->head;

    while(tmp) {
        if (!strcmp(tmp->phoneNumber, numberToDelete)) {
            puts("The contact below will be deleted.");
            printf("Name: %s\n", tmp->name);
            printf("Surname: %s\n",  tmp->surname);
            printf("Phone number: %s\n\n", tmp->phoneNumber);

            deleteNode(list, tmp);
            return;
        }
        tmp = tmp->next;
    }
    puts("There is no existing contact in phone book\n");
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
    while(tmp) {
        if (!strcmp(tmp->surname, searchBySurname)) {
            puts("The contact is found!");
            printf("Name: %s\n", tmp->name);
            printf("Surname: %s\n", tmp->surname);
            printf("Phone number %s\n\n", tmp->phoneNumber);
            return;
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

    puts("Your contacts have been successfully written to the file : \"phone.dat\"\n");
}


void retrieveFromTheFile(DblLinkedList* list)
{
    FILE* file = fopen("/home/yadaniil/phone.dat", "r");
    if(!file) {
        puts("ERROR. The file cannot be opened");
        return;
    }

    Node *tmp;
    Node *cur;
    char str[10];


    while (!feof(file)) {
        tmp = malloc(sizeof(Node));

        fscanf(file, "%s %s\n", str, tmp->name);
        fscanf(file, "%s %s\n", str, tmp->surname);
        fscanf(file, "%s %s %s\n\n", str, str, tmp->phoneNumber);
        addNode(list, tmp);
/*
        if(list->head)
            cur = list->head;

        if(list->head) {
            while(cur) {
                if (!strcmp(cur->phoneNumber, tmp->phoneNumber)) {
                    printf("Contact with phone number %s ", cur->phoneNumber);
                    puts("cannot be added to the phone book");
                    puts("The contact with this phone number is already exist.");
                } else {
                    addNode(list, tmp);
                }
                if(cur->next)
                    cur = cur->next;
                else
                    break;
            }
        } else {
            addNode(list, tmp);
        }
        */
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