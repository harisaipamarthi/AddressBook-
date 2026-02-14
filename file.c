#include<stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    if (!addressBook) return;

    FILE *fptr = fopen("Contact.txt","w");
    if (!fptr) {
        perror("Could not open Contact.txt for writing");
        return;
    }

    fprintf(fptr, "%d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fptr, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].number,addressBook->contacts[i].email);
    }

    fflush(fptr);
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {
    if (!addressBook) return;

    FILE *fptr = fopen("Contact.txt","r");
    if(fptr == NULL) {
        // No file yet — that's fine, start with empty address book
        addressBook->contactCount = 0;
        return;
    }

    int count = 0;
    if (fscanf(fptr, "%d\n", &count) != 1) {
        // file malformed or empty
        addressBook->contactCount = 0;
        fclose(fptr);
        return;
    }

    if (count < 0) count = 0;
    if (count > MAX_CONTACTS) count = MAX_CONTACTS;

    int read = 0;
    for (int i = 0; i < count; i++) {
        // Use width limits to avoid buffer overflow (match contact.h sizes)
        if (fscanf(fptr, "%49[^,],%19[^,],%49[^,]\n",addressBook->contacts[i].name,addressBook->contacts[i].number,addressBook->contacts[i].email) == 3) 
        {
            read++;
        } 
        else {
            // failed to parse this line — stop reading further
            break;
        }
    }

    addressBook->contactCount = read;
    fclose(fptr);
}
