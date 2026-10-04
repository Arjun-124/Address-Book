#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts1.csv", "w");//create+ the file in the write mode

    if(fp == NULL)
    {
        printf("File opening failed\n");
        return;
    }

    for(int i = 0; i < addressBook->contactCount; i++)//printing upto the last of matchcount
    {
        fprintf(fp, "%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fp);

    printf("Contacts saved successfully\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp = fopen("contacts1.csv", "r");//open file in the read mode for loading

    if(fp == NULL)
    {
        printf("No contacts file found\n");
        return;
    }

    while(fscanf(fp, "%[^,],%[^,],%[^\n]\n",
        addressBook->contacts[addressBook->contactCount].name,
        addressBook->contacts[addressBook->contactCount].phone,
        addressBook->contacts[addressBook->contactCount].email) == 3)// it reads the date upto , with it equal to three
    {
        addressBook->contactCount++;
    }

    fclose(fp);

    printf("Contacts loaded successfully\n");
    printf("Loaded contacts count = %d\n", addressBook->contactCount);//display the data
    
}
