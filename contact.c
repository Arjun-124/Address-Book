#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int matchedindex[100];//creating the global array with count 100
int matchcount;

int isValidName(char ch[]);//function declarations
int isValidphone(char phone[],AddressBook *addressBook,int duplicate);
int isValidmail(char email[],AddressBook *addressBook,int duplicate);

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    switch(sortCriteria)//using switch case for how we sort 
    {
        case 1:printf("sort by name :\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)//sorting by the name a to z
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;

                }
            }

        }
        printf("Index No Name\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)//printing upto the contactcount
        {
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        case 2:printf("sort by number :\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)//soring the by the phone number 6 to 9
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;

                }
            }

        }
        printf("Index No Name\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        case 3:printf("sort by gmail :\n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)//soring by the mail from a to z
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;

                }
            }

        }
        printf("Index No Name\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);//load the contact s from the file
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[100];
    char phone[20];
    char email[50];
    int count=1;
    while(count<=3)//upto 3 times wrong enter name is executed
    {
        //char c[100];
        printf("Enter the name: ");
         scanf(" %99[^\n]",name);
         if(isValidName(name))//validate the name by using valid name function
         {
            printf("Sucessfully name is added\n");
            break;
         }
         else
         {
            count++;
            if(count<=3)
            {
                printf("try again........\n");
            }
        }
    }
    if(count>3)
    {
        printf("We enter 3 times wrong name\n");//if more than times enter wrong name the it automatically  break
        //exit(1);
        return;
    }
    count=1;
    while(count<=3)//upto 3 times wrong enter phone number is executed
    {
        //char c[100];
        printf("Enter the phone number: ");
         scanf("%s", phone);
         if(isValidphone(phone,addressBook,1))//calling the validphone functuion for checking
         {
            printf("Sucessfully phone number is added\n");
            break;
         }
         else
         {
            count++;
            if(count<=3)
            {
                printf("try again........\n");

            }
        }
    }
    if(count>3)
    {
        printf("you enter 3 times wrong phone number\n");//if more than times enter wrong name the it automatically  break
        //exit(1);
        return;
    }
    count=1;
    while(count<=3)////upto 3 times wrong enter phone number is executed
    {
        //char email[100];
        printf("Enter the mail: ");
         scanf("%s", email);
         if(isValidmail(email,addressBook,1))
         {
            printf("Sucessfully mail is added\n");
            break;
         }
         else
         {
            count++;
            if(count<=3)
            {
                printf("try again........\n");
            }
        }
    }
    if(count>3)
    {
        printf("We enter 3 times wrong mail\n");//if more than times enter wrong name the it automatically  break
        //exit(1);
        return;
    }
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);//copied the details to the addresbook
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount++;
    printf("contacts is sucessfully added.......");


    
}

int searchContact(AddressBook *addressBook,int searchoption) 
{
    /* Define the logic for search */
    int count=0;
    char name[100];
    char phone[20];
    char email[50];
    switch(searchoption)//using switch case  select by how we search the details
    {
        case 1:printf("search by the name\n");
          count=1;
          while(count<=3)
          {
              printf("enter the name\n");
              scanf(" %[^\n]",name);
             if(isValidName(name))//calling is validName function
            {
            //printf("name is found ");
                int i=0;
                int found=0;
                matchcount=0;
               for(int i = 0; i < addressBook->contactCount; i++)
               {
               if(strcmp(addressBook->contacts[i].name, name) == 0)//compare the enter name with all names in address book if it si eqaul print details
               {
                    matchedindex[matchcount] = i;
                    printf("%d. %s\t%s\t%s\n",matchcount + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    matchcount++;
                }
            }
           if(matchcount == 0)
           {
               printf("Contact not found\n");//if contact is not there print not found
               return 0;
            }
            return matchcount;
           }
            else{
               count++;
               if(count<=3)
               {
                 printf("tryagain.......\n");//try uptothree times error
               }
            }
        }
        if(count>3)
        {
           printf("we entered three times worng name..\n");
           return -1;
        }
        break;
        case 2:printf("enter the phone number\n");
        count=1;
          while(count<=3)
          {
              printf("enter the phone\n");
              scanf(" %[^\n]",phone);
             if(isValidphone(phone,addressBook,0))//calling the validphone number
            {
            //printf("name is found ");
                int i=0;
                int found=0;
                while(i<addressBook->contactCount)
                {
                    if(strcmp(addressBook->contacts[i].phone,phone)==0)//comparing the phone in addreesbook
                    {
                         found=1;
                        break;
                    }
                    i++;
                }
                if(found==1)//if its found print the details
                {
                   printf("details of persons\n");
                   printf("%s %s %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   matchedindex[0] = i;
                   matchcount = 1;
                   return matchcount;
                }
                else{
                    printf("not found\n");
                }
                break;
            }
            else{
               count++;
               if(count<=3)
               {
                 printf("tryagain.......\n");
               }
            }
        }
        if(count>3)
        {
           printf("we entered three times worng phone number..\n");
           return -1;
        }
        break;
        case 3:printf("search by the mail");
         count=1;
          while(count<=3)
          {
              printf("enter the mail\n");
              scanf(" %[^\n]",email);
             if(isValidmail(email,addressBook,0))//calling the validmail function
            {
            //printf("name is found ");
                int i=0;
                int found=0;
                while(i<addressBook->contactCount)
                {
                    if(strcmp(addressBook->contacts[i].email,email)==0)//checkin name is present or not
                    {
                         found=1;
                        break;
                    }
                    i++;
                }
                if(found==1)
                {
                   printf("details of persons\n");//if found the details then print the details of person
                   printf("%s %s %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   matchedindex[0] = i;
                   matchcount = 1;
                   return matchcount;
                }
                else{
                    printf("not found\n");
                }
                break;
            }
            else{
               if(count<=3)//checking the count value if it is less than then again reenter
               {
                 printf("tryagain.......\n");
                 count++;
               }
            }
        }
        if(count>3)
        {
           printf("we entered three times worng password..\n");
           return -1;
        }
        break;
        case 4:
          printf("exit....");//exit the switch case
          return 0;
         
     }
     return 0;       
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int option;
    int selectIndex;
    printf("Search contact using:\n");//printing the search options
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d",&option);
    int count=searchContact(addressBook,option);//calling search contact 
    if(count==0)
    {
        printf("details is not found");//if the count zero details not found
        return;
    }
    if(count == -1)
    {
        return;
    }
    if(count==1)
    {
        selectIndex = matchedindex[0];
    }
    else{
        int serial;
        printf("enter the serial no");//it is used for we similar names then the enter serial number what we want edit
        scanf("%d",&serial);
        selectIndex=matchedindex[serial-1];
    }
    int choice;
    printf("enter the option\n");//then selct what we edit 
    printf("1. edit by name\n");
    printf("2. edit by Phone\n");
    printf("3. edit by Email\n");
    printf("4.exit\n");
    printf("enter the choice");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        char name[100];
        printf("enter th new name");
        scanf(" %[^\n]",name);
        int value=isValidName(name);//calling the validName functiuon
        if(!value)
        {
            printf("error...enter the valid name\n");//if it not valid then error is occur
            return;
        }
        else{
            strcpy(addressBook->contacts[selectIndex].name, name);//strcpy is used to copy the old name with new name
            printf("Name updated successfully\n");
            break;

        }
        case 2:
        char phone[100];
        printf("enter th new phone number");
        scanf(" %[^\n]",phone);
        value=isValidphone(phone,addressBook,1);//calling the validphone function
        if(!value)
        {
            printf("error...enter the valid phone number\n");
            return;
        }
        else{
            strcpy(addressBook->contacts[selectIndex].phone, phone);//cpoying old one to new one
            printf("phone number is updated successfully\n");
            break;

        }
        case 3:
        char email[100];
        printf("enter th new mail");
        scanf(" %[^\n]",email);
        value=isValidmail(email,addressBook,1);//calling validmail function
        if(!value)
        {
            printf("error...enter the valid mail\n");
            return;
        }
        else{
            strcpy(addressBook->contacts[selectIndex].email, email);//copying old mail with new one
            printf("phone number is updated successfully\n");
            break;

        }
        case 4:
           printf("Exiting edit menu...\n");
           return;
        default:
           printf("Invalid choice\n");
           break;


    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int option;
    int selectIndex;
    printf("enter the option\n");//sewlecting the search option
    printf("1.search by name\n");
    printf("2.search by phone number\n");
    printf("3.search by email\n");
    printf("4.exit\n");
    printf("enter the choices\n");
    scanf("%d",&option);
     if(option == 4)
    {
        printf("Exit from delete menu\n");
        return;
    }
    int count=searchContact(addressBook,option);//calling the search contact
    if(count==0)
    {
        printf("details not found\n");
        return;
    }
    if(count == -1)
    {
       return;
    }
    if(count==1)
    {
        selectIndex=matchedindex[0];//for only one name is present directly asking yes or no
    }
    else{
        int serial;
        printf("enter the serial\n");//these for selecting the one name 
        scanf("%d",&serial);
        if(serial < 1 || serial > count)
        {
            printf("Invalid serial number\n");
            return;
        }
        selectIndex=matchedindex[serial-1];
    }
    int choice;

    printf("\nDo you want to delete this contact..\n");//once again asking yes or no for delete
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 2)
    {
        printf("Delete cancelled.\n");//no means directly cancle
        return;
    }

    if(choice == 1)
    {
        for(int i = selectIndex; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];//shifing the one place foeward onn delete index onwards
        }

        addressBook->contactCount--;

        printf("Contact deleted successfully.\n");
    }  
}
int isValidName(char name[])//creating the validname function
{
    int i=0;
    int count=1;
    if(!isalpha(name[i]))//checking the name is should in alphabet or not fo the first element
    {
        printf("Name should contain only alphabets\n");//error msg if we enter other than alpahbet 
        return 0;
    }
    else{
    for(int i = 0; name[i] != '\0'; i++)
    {
        
        if(isalpha(name[i])|| name[i]==' '||isdigit(name[i]))//in the name should only contain space and alphabet and digit is checking
        {
            
            count++;
        }
        else{
            return 0;
        }
    }
    }
    if(count<=4)
    {
        printf("Name should contain atleat 4 charcter");//it atleast contain 4 chatracters
        return 0;
    }
    return 1;
}
int isValidphone(char phone[], AddressBook *addressBook,int duplicate)//creating the  validphone  function
{
    int i;
    if(phone[0] < '6' || phone[0] > '9')//checking the number should start above or equal to 6 and less than or equla to 9
    {
        printf("First digit must be in between 6 to 9");
         return 0;
    }
    for(i = 0; phone[i] != '\0'; i++)//reading the character by character
    {
        if(isalpha(phone[i]))
        {
          printf("Alphabets are not allowed in phone number\n");
          return 0;
        }
        else if(!isdigit(phone[i]))//checking the enter number is digit are not
        {
            printf("Symobls are not allowed in phone number");
            return 0;
        }
    }
    if(i != 10)//size should be equal to 10
    {
        printf("Phone number must contain exactly 10 digits");
        return 0;
    }
    if(duplicate==1)//checking duplicate if the numbne alrady present are not
    {
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)//comparing all phone number in address book
        {
            printf("Phone number already exists.\n");
            return 0;
        }
    }
}

    return 1;
}

int isValidmail(char email[], AddressBook *addressBook, int duplicate)//creating  the valid mail  function
{
    int a = 0;
    int dot=0;
    int com= 0;
    int apoint=-1;
    int dotpoint=-1;
    int i=0;
    if(email[0] < 'a' || email[0] > 'z')//checking the the char ter is in between the a to z
    {
        printf("Email must start with a lowercase letter\n");
        return 0;
    }
    for(i=0; email[i]!='\0'; i++)
    {
        if(email[i]=='@')//checking the @ is present or not
        {
            a++;
            apoint=i;//assigning the index value of @
        }
        if(email[i]=='.')////checking the . is present or not
        {
            dot++;
            dotpoint=i;//assigning the index value of .
        }
        if(!isalnum(email[i]) && email[i]!='@' && email[i]!='.')//using isalnum checking the it should only presen aplabets anmd numbers 
        {
          printf("Email id must contain only the @ and . symbol\n");
          return 0;
        }
    }
    if(a != 1)//only @ should present
    {
        printf("Email id must contain exactly one @ symbol\n");
        return 0;
    }
    if(dot != 1)//only one . should present
    {
        printf("Email id must contain exactly one . symbol\n");
        return 0;
    }
    if(dotpoint < apoint)//. must come after @
    {
        printf(". must come after @\n");
        return 0;
    }
    if(dotpoint == apoint + 1)//Domain checking
    {
        printf("Domain missing\n");
        return 0;
    }
    if(strcmp(email + strlen(email) - 4, ".com") != 0)//checking the last four charcter sof the mail should present only .com
    {
        printf("Email must end with .com\n");
        return 0;
    }
    if(duplicate == 1)//checking is already present or not
    {
        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].email,email)==0)//comparing the each and every mail
            {
                printf("Mail already exists.\n");
                return 0;
            }
        }
    }
     return 1;
}


