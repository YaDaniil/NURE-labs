#ifndef HEADER_H
#define HEADER_H

extern int quantityOfContacts;

typedef struct PhoneBook
{
	char name[11];
	char surname[21];
	char phoneNumber[13];
}Contact;

extern PhoneBook phoneBook[20];

void displayMenu();
void addEntry();
void deleteEntry();
void searchEntry();
void displayAllEntries();
void runProgramm();

#endif