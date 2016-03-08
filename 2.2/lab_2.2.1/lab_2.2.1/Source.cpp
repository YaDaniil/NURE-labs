#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>

#include "Header.h"

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
	if (strlen(number) > PHONE_SIZE - 1)
		return false;
	for (int i = 0; i < strlen(number); i++) {
		if (!isdigit(number[i]) || number[i] == '-') {
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
	do {
		printf("Input a phone number: ");
		scanf("%12s", &phoneBook[quantityOfContacts].phoneNumber);
	} while (!checkTheNumberCorrectness(phoneBook[quantityOfContacts].phoneNumber));
	fflush(stdin);

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
	fflush(stdin);

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



void runProgramm()
{
	displayMenu();
	char choice = 0;
	
	do {
		printf("Select an appropriate clause: ");
		scanf("%1c", &choice);
		fflush(stdin);
		if (!isdigit(choice)) {
			puts("Input parameters are incorrect. Try again.");
			return;
		}
			
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
			exit(0);
		default:
			puts("Input parameters are incorrect. Try again.");
		}
	} while (choice < '1' || choice > '4');
}