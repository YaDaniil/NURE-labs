#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>

#include "Header.h"

int quantityOfContacts = 0;

void clean()
{
    while ( getchar() != '\n' );
}

//Creates a new Node and returns pointer to it.
struct Node* getNewNode(char* name, char* surname, char* phoneNumber)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    strcpy(newNode->surname, surname);
    strcpy(newNode->phoneNumber, phoneNumber);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(char* name, char* surname, char* phoneNumber)
{
    struct Node* newNode = getNewNode(name, surname, phoneNumber);
    if(head == NULL) {
        head = newNode;
        return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(char* name, char* surname, char* phoneNumber)
{
    struct Node* temp = head;
    struct Node* newNode = getNewNode(name, surname, phoneNumber);
    if(head == NULL) {
        head = newNode;
        return;
    }
    while(temp->next != NULL) temp = temp->next; // Go To last Node
    temp->next = newNode;
    newNode->prev = temp;
}

//Prints all the elements in linked list in forward traversal order
void print() {
    struct Node* temp = head;
    while(temp != NULL) {
        printf("Name: %s\n ",temp->name);
        printf("Surname: %s\n ",temp->surname);
        printf("Phone number: %s\n ",temp->phoneNumber);
        temp = temp->next;
    }
    printf("\n");
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

bool checkTheNumberCorrectness(char* number)
{
    if (strlen(number) > PHONE_SIZE - 1)
        return false;
    for (int i = 0; i < strlen(number); i++) {
        if (number[i] == '-' || !isdigit(number[i])) {
            puts("The phone number is invalid.");
            return false;
        }
        return true;
    }
}

void addEntry()
{
    char* name, surname, phoneNumber;
    printf("Input a name: ");
    scanf("%10s", &name);
    clean();
    printf("Input a surname: ");
    scanf("%20s", &surname);
    clean();

    do {
        printf("Input a phone number: ");
        scanf("%12s", &phoneNumber);
    } while (!checkTheNumberCorrectness((char*)phoneNumber));
    clean();

    for (int i = 0; i < quantityOfContacts; i++) {
        if (!strcmp(phoneBook[quantityOfContacts].phoneNumber, phoneBook[i].phoneNumber)) {
            puts("Cannot be added to the phone book");
            puts("The entry with this phone number is already exist.");
            return;
        }
    }

    puts("A new contact was successfully added\n");
    quantityOfContacts++;
}

void deleteEntry()
{
    if (quantityOfContacts == 0) {
        puts("The phone book is empty. There is nothing to delete.");
        return;
    }

    char numberToDelete[PHONE_SIZE];
    do {
        printf("Enter a phone number to remove the contact: ");
        scanf("%12s", numberToDelete);
    } while (!checkTheNumberCorrectness(numberToDelete));

    for (int i = 0; i < quantityOfContacts; i++) {
        if (!strcmp(phoneBook[i].phoneNumber, numberToDelete)) {
            puts("The contact below will be deleted.");
            printf("Name: %s\n", phoneBook[i].name);
            printf("Surname: %s\n",  phoneBook[i].surname);
            printf("Phone number: %s\n\n", phoneBook[i].phoneNumber);

            for (int j = i; j < quantityOfContacts; j++) {
                strcpy(phoneBook[j].name, phoneBook[j + 1].name);
                strcpy(phoneBook[j].surname, phoneBook[j + 1].surname);
                strcpy(phoneBook[j].phoneNumber, phoneBook[j + 1].phoneNumber);
            }
            quantityOfContacts--;
            break;
        }
        else
            puts("There is no existing contact in phone book\n");
    }
}

void displayAllEntries()
{
    if (quantityOfContacts == 0) {
        puts("Your phone book is empty.\n");
        return;
    }
    if (quantityOfContacts == 1) {
        puts("There is 1 contact in your phone book.\n\n");
        printf("Name: %s\n", phoneBook[quantityOfContacts - 1].name);
        printf("Surname: %s\n", phoneBook[quantityOfContacts - 1].surname);
        printf("Phone number %s\n\n", phoneBook[quantityOfContacts - 1].phoneNumber);
    }
    else {
        printf("%s %d %s", "The is ", quantityOfContacts, " contacts in your phone book.\n\n");
        for (int i = 0; i < quantityOfContacts; i++) {
            printf("Name: %s\n", phoneBook[i].name);
            printf("Surname: %s\n", phoneBook[i].surname);
            printf("Phone number: %s\n\n", phoneBook[i].phoneNumber);
        }
    }
}

void searchEntry()
{
    if (quantityOfContacts == 0) {
        puts("The phone book is empty!");
        puts("Add some contacts to search.\n");
        return;
    }
    char searchBySurname[SURNAME_SIZE];
    printf("Input the surname to search and display contact:");
    scanf("%20s", &searchBySurname);
    clean();

    for (int i = 0; i < quantityOfContacts; i++)  {

        if (!strcmp(phoneBook[i].surname, searchBySurname)) {
            puts("The contact is found!");
            printf("Name: %s\n", phoneBook[i].name);
            printf("Surname: %s\n", phoneBook[i].surname);
            printf("Phone number: %s\n\n", phoneBook[i].phoneNumber);
            break;
        }
        else
            puts("There is no existing contact in phone book\n");
    }
}

void sortEntries()
{
    puts("Sort");
}

void saveInTheFile()
{
    puts("Save");
}

void retrieveFromTheFile()
{
    puts("Retrieve");
}



void runProgramm()
{
    displayMenu();
    char choice = 0;

    do {
        printf("Select an appropriate clause: ");
        scanf("%1c", &choice);
        clean();

        switch (choice) {
            case '1':
                addEntry();
                break;
            case '2':
                deleteEntry();
                break;
            case '3':
                searchEntry();
                break;
            case '4':
                displayAllEntries();
                break;
            case '5':
                sortEntries();
                break;
            case '6':
                saveInTheFile();
                break;
            case '7':
                retrieveFromTheFile();
                break;
            case '8':
                exit(0);
            default:
                puts("Input parameters are incorrect. Try again.");
        }
    } while (choice < '1' || choice > '8');
}