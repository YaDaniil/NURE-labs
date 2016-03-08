#ifndef HEADER_H
#define HEADER_H

#define PHONE_BOOK_SIZE 20
#define NAME_SIZE 11
#define SURNAME_SIZE 21
#define PHONE_SIZE 13

extern int quantityOfContacts;

typedef struct PhoneBook
{
	char name[NAME_SIZE];
	char surname[SURNAME_SIZE];
	char phoneNumber[PHONE_SIZE];
}Contact;

extern PhoneBook phoneBook[PHONE_BOOK_SIZE];

void displayMenu();
void addEntry();
void deleteEntry();
void searchEntry();
void displayAllEntries();
void runProgramm();

#endif