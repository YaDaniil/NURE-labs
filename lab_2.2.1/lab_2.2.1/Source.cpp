#define _CRT_SECURE_NO_WARNINGS
#define PHONE_BOOK_SIZE 20

#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>

static int quantityOfContacts = 0;
PhoneBook phoneBook[PHONE_BOOK_SIZE];

void displayMenu()
{
	puts("\n\t\t\t********Phone Book Manager********\n");
	puts("1. Add entry\n");
	puts("2. Delete entry\n");
	puts("3. Search entry\n");
	puts("4. Display all entries\n");
	puts("5. Exit programm\n");
}

bool checkTheNumberCorrectness(char* number)
{
	for (int i = 0; i < strlen(number); i++) {
		if (isdigit(number[i])) {
			puts("The phone number is invalid.");
			return false;
		}
		return true;
	}
}

void addEntry()
{
	if (quantityOfContacts > PHONE_BOOK_SIZE) {
		puts("The phone book is full. Remove a contact to add another one");
		return;
	}
	printf("Input a name: ");
	scanf("%10s", &phoneBook[quantityOfContacts].name);
	fflush(stdin);
	printf("Input a surname: ");
	scanf("%20s", &phoneBook[quantityOfContacts].surname);
	fflush(stdin);
	printf("Input a phone number: ");
	scanf("%10s", &phoneBook[quantityOfContacts].phoneNumber);
	fflush(stdin);
	
	puts("A new contact was successfully added\n");
	quantityOfContacts++;
}

void deleteEntry()
{
	char numberToDelete[13];
	do {
		printf("Enter a phone number to remove the contact: ");
		scanf("%s", numberToDelete);

	} while (!checkTheNumberCorrectness(numberToDelete));
			
}

void displayAllEntries()
{
	if (quantityOfContacts == 0) {
		puts("Your phone book is empty.\n");
		return;
	}
	if (quantityOfContacts == 1) {
		puts("There is 1 contact in your phone book.\n\n");
		printf("%s %s\n", "Name:", phoneBook[quantityOfContacts - 1].name);
		printf("%s %s\n", "Surname:", phoneBook[quantityOfContacts - 1].surname);
		printf("%s %s\n\n", "Phone number:", phoneBook[quantityOfContacts - 1].phoneNumber);
	}
	else {
		printf("%s %d %s", "The is ", quantityOfContacts, " contacts in your phone book.\n\n");
		for (int i = 0; i < quantityOfContacts; i++) {
			printf("%s %s\n", "Name:", phoneBook[i].name);
			printf("%s %s\n", "Surname:", phoneBook[i].surname);
			printf("%s %s\n\n", "Phone number:", phoneBook[i].phoneNumber);
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
	char searchBySurname[21];
	printf("Input the surname to search and display contact:");
	scanf("%20s", &searchBySurname);
	fflush(stdin);

	for (int i = 0; i < quantityOfContacts; i++)  {

		if (!strcmp(phoneBook[i].surname, searchBySurname)) {
			puts("The contact is found!");
			printf("%s, %s\n", "Name:", phoneBook[i].name);
			printf("%s, %s\n", "Surname:", phoneBook[i].surname);
			printf("%s, %s\n\n", "Phone number:", phoneBook[i].phoneNumber);
			break;
		}
		else
			puts("There is no existing contact in phone book\n");
	}
}



void runProgramm()
{
	displayMenu();
	int choice = 0;
	
	do {
		printf("Select an appropriate clause: ");
		scanf("%d", &choice);
		if (!isdigit(choice)) {
			puts("Input parameters are incorrect. Try again.");
			fflush(stdin);
			return;
		}
			
		switch (choice) {
		case 1:
			addEntry();
			break;
		case 2:
			deleteEntry();
			break;
		case 3:
			searchEntry();
			break;
		case 4:
			displayAllEntries();
			break;
		case 5:
			exit(0);
		default:
			puts("Input parameters are incorrect. Try again.");
			
		}
	} while (choice < 1 || choice > 4);
}