#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>


int search_name(AddressBook *addressBook, const char *name) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
            return i;
    }
    return -1;
}

int search_number(AddressBook *addressBook, const char *number) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].number, number) == 0)
            return i;
    }
    return -1;
}

int search_mail(AddressBook *addressBook, const char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return i;
    }
    return -1;
}


int valid_mail(char *mail)
{
    int start = 0, end = 0, i;
    
    for(i = 0; mail[i]; i++) {
        if(mail[i] == '@') start = 1;
        if(start && mail[i] == '.') end = 1;
        if(mail[i] == ' ') {
            printf("Email should not contain spaces\n");
            return 1;
        }
    }
    if(!start || !end) {
        printf("Invalid email format. Must contain '@' and '.'\n");
        return 1;
    }
    return 0;
}


int valid_number(char *number)
{
    int i,valid;
    int len=strlen(number);

    if(len!=10)
    {
        printf("Number sholud have 10 numbers\n");
        return 1;
    }
    for(i=0;number[i];i++)
           {
            if(!(isdigit(number[i])))
            {
                valid=1;
                printf("MObile number sholud be only numbers ");
                return 1;
            }
            return 0;
        }
}



int valid_name(char *name)
{
    int i;
    for(i=0;name[i];i++)
        {
            if(!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <='Z') || name[i] == ' '))
            {
                printf("Name should not have any digits and special charecters\n");
                return 1;
            }

        }
        return 0;
}



void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    int n = addressBook->contactCount;
    int i, j;
    for(i = 0; i < n-1; i++) {
        for(j = i + 1; j < n; j++) {
            int cmp = 0;
            if(sortCriteria == 1)
                cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[i].name);
            else if(sortCriteria == 2)
                cmp = strcmp(addressBook->contacts[j].number, addressBook->contacts[i].number);
            else if(sortCriteria == 3)
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[i].email);
            if(cmp < 0) {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
    for(i=0;i<n;i++) {
        printf("+-----------------+----------------+--------------------------+\n");
        printf("| %-15s | %-14s | %-24s |\n", addressBook->contacts[i].name, addressBook->contacts[i].number, addressBook->contacts[i].email);
        printf("+-----------------+----------------+--------------------------+\n");
    }
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
    
}


void createContact(AddressBook *addressBook)
{
     if (addressBook ->contactCount >= 100)
     {
        printf("Address Book contacts are full ! Cannot add more contacts.\n");
        return ;
     }
	/* Define the logic to create a Contacts */
    char name[40],phone[13],mail[20];
    int valid, i;
    char *start, *end;

    // validation for name
    do 
    {
        printf("Enter name: ");
        scanf(" %[^\n]", name);

        valid=valid_name(name);
        
        
    }while(valid);

    // Vaidation for number     
    do {
        valid = 0;
        printf("Enter mobile number : ");
        scanf(" %[^\n]", phone);

        valid=valid_number(phone);
    }while(valid);

    // Validation for mail
    do {
        valid = 0;
        printf("Enter the mail ");
        scanf(" %[^\n]", mail);

        valid=valid_mail(mail);
    }while(valid);

    strcpy(addressBook->contacts[addressBook ->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook ->contactCount].number,phone);
    strcpy(addressBook->contacts[addressBook ->contactCount].email,mail);


}


void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int i,search,index,found;
    char compare[30];
    int size = addressBook->contactCount;
    if(size==0)
    {
        printf(" NO contacts avalible to search\n");
        return;
    }
    while(1)
    {
        printf("Enter search criteria: ");
        printf("\n1.Search by name\n2.Search by number\n3.search by email id\n4.Exit\nEnter your choice:");
        scanf("%d",&search);
        if(search==1)
            printf("Enter your name:");
        else if(search==2)
            printf("Enter your number:");
        else if(search==3)
            printf("Enter your mail id:");
        else if(search==4)
            break;
        if(search <= 0 || search > 4)
        {
            printf("Invalid input\n");
            continue;
        }
        scanf(" %[^\n]",compare);
        int match=0;
        for(i=0;i<size;i++)
        {
            found=0;
            if(search==1 && strcasestr(addressBook->contacts[i].name,compare))
                found=1;
            else if(search==2 && strcasestr(addressBook->contacts[i].number,compare))
                found=1;
            else if(search==3 && strcasestr(addressBook->contacts[i].email,compare))
                found=1;
            if(found)
            {
                if(match==0)
                {
                    printf("+-----------------+----------------+--------------------------+\n");
                    printf("| %-15s | %-14s | %-24s |\n", "Name", "Number", "Email ID");
                    printf("+-----------------+----------------+--------------------------+\n");
                }
                printf("| %-15s | %-14s | %-24s |\n", addressBook->contacts[i].name, addressBook->contacts[i].number, addressBook->contacts[i].email);
                printf("+-----------------+----------------+--------------------------+\n");
                match=1;
            }
        }
        if(match==0)
        {
            printf("\033[1;31m");// red bold text
            printf("\n╔═════════════════════════════════╗\n");
            printf("║       ❌  NO CONTACT FOUND       ║\n");
            printf("╚═════════════════════════════════╝\n");
            printf("\033[0m"); // Reset color
        }
    }
}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    if(addressBook->contactCount == 0)
    {
        printf("❌ No contacts available to edit.\n");
        return;
    }

    int size = addressBook->contactCount;
    int i,search,index;
    char edit[30];


    while(1)
    {
        printf("Enter search criteria: ");
        printf("\n1. Search by name\n2. Search by number\n3. Search by email id\n4. Exit\nEnter your choice: ");
        scanf("%d",&search);
        if(search==1)
        printf("Enter your name: ");

        else if(search==2)
        printf("Enter your number: ");

        else if(search==3)
        printf("Enter your mail id: ");

        else if(search==4)
        break;

        if(search <= 0 || search > 4)
        {
            printf("Invalid input\n");
            continue;
        }

        scanf(" %[^\n]",edit);


        if(search==1)
            index=search_name(addressBook,edit);

        else if(search==2)
            index=search_number(addressBook,edit);
        else if(search==3)
            index=search_mail(addressBook,edit);


        if(index==-1)
            {
                printf("\033[1;31m"); // Red bold text
                printf("\n╔═════════════════════════════════╗\n");
                printf("║       ❌  NO CONTACT FOUND       ║\n");
                printf("╚═════════════════════════════════╝\n");
                printf("\033[0m"); // Reset color
                return;
            }


        printf("+-----------------+----------------+--------------------------+\n");
        printf("| %-15s | %-14s | %-24s |\n", "Name", "Number", "Email ID");
        printf("+-----------------+----------------+--------------------------+\n");

        printf("| %-15s | %-14s | %-24s |\n",addressBook->contacts[index].name,addressBook->contacts[index].number,addressBook->contacts[index].email);
        printf("+-----------------+----------------+--------------------------+\n");

    do
    {
    printf("\nEnter edit criteria: \n");
    printf("1. Edit name\n2. Edit number\n3. Edit mail id\n4. Exit\nEnter your choice: ");
    scanf("%d",&search);



    if(search==1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]",edit);
        strcpy(addressBook->contacts[index].name,edit);
        printf("Name edited succussfully \n");
        return;
    }

    else if(search==2)
    {
        printf("Enter number: ");
        scanf(" %[^\n]",edit);
        strcpy(addressBook->contacts[index].number,edit);
        printf("Number edited succussfully \n");
        return;
    }
      else if(search==3)
    {
        printf("Enter mail id: ");
        scanf(" %[^\n]",edit);
        strcpy(addressBook->contacts[index].email,edit);
        printf("Name edited succussfully \n");
        return;
    }

    else
    {
        printf("Invalid input\n");
        continue;
    }

    }
    while(search != 4);
        
    

    }
}


    


void deleteContact(AddressBook *addressBook) {
    /* Define the logic for deletecontact */
    int size = addressBook->contactCount;
    int i, num, match, valid, found, j;
    char delete[30], confirm;

    while(1) {
        printf("Enter delete criteria: \n");
        printf("1. By Name\n2. By number\n3. By email id\n4. Exit\nEnter your choice:");
        scanf("%d", &num);

        if(num == 1)
            printf("Enter name: ");
        else if(num == 2)
            printf("Enter number: ");
        else if(num == 3)
            printf("Enter email id: ");
        else if(num == 4)
            return;
        else {
            printf("Invalid input\n");
            continue;
        }

        scanf(" %[^\n]", delete);

        match = 0;
        for(i = 0; i < size; i++) {
            found = 0;
            if(num == 1 && strcasestr(addressBook->contacts[i].name, delete))
                found = 1;
            else if(num == 2 && strcmp(addressBook->contacts[i].number, delete) == 0)
                found = 1;
            else if(num == 3 && strcasestr(addressBook->contacts[i].email, delete))
                found = 1;
            if(found) {
                if(match == 0) {
                    printf("Contact found\n");
                    printf("\n+-----------------+----------------+--------------------------+\n");
                    printf("| %-15s | %-14s | %-24s |\n", "Name", "Number", "Email ID");
                    printf("+-----------------+----------------+--------------------------+\n");
                }
                printf("| %-15s | %-14s | %-24s |\n", addressBook->contacts[i].name, addressBook->contacts[i].number, addressBook->contacts[i].email);
                printf("+-----------------+----------------+--------------------------+\n");
                match = 1;
            }
            if(match) {
                printf("Are you sure you want to delete this contact? (y/n): ");
                scanf(" %c", &confirm);
                if(confirm == 'y' || confirm == 'Y') {
                    for(j = i; j < addressBook->contactCount - 1; j++) {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("✅ Contact deleted successfully!\n");
                    return;
                } else {
                    printf("✅ Contact deleted canceled!\n");
                    return;
                }
            }
        }
        if(match == 0) {
            printf("\n❌ No contact match\n");
            return;
        }
    }
}




