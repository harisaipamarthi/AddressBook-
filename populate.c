#include "contact.h"
// Dummy contact data

void populateAddressBook(AddressBook* addressBook)
{
    //int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);
    for (int i = 0; i < addressBook->contactCount && addressBook->contactCount < MAX_CONTACTS; ++i) {
        addressBook->contacts[addressBook->contactCount++] = addressBook->contacts[i];
    }
}