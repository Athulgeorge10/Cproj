#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Contact{
    char name[50];
    char phone[15];
    char email[50];
    char category[50];
};

#define MAX_CONTACTS 1000
#define MAX_LINE 500

void addContact(){
    
    struct Contact contact;
    printf("Enter name: ");
    fgets(contact.name,sizeof(contact.name),stdin);
    contact.name[strlen(contact.name)-1] = '\0';
    
    FILE *fp = fopen("contacts.txt","r");
    if (fp != NULL) {
        char line[MAX_LINE];
        while (fgets(line,sizeof(line),fp)) {
            char *token = strtok(line,",");
            if (token != NULL && strcmp(token,contact.name) == 0){
                printf("Contact already exists.\n");
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    
    printf("Enter phone: ");
    fgets(contact.phone,sizeof(contact.phone),stdin);
    contact.phone[strlen(contact.phone)-1] = '\0'; 

    printf("Enter email: ");
    fgets(contact.email,sizeof(contact.email),stdin);
    contact.email[strlen(contact.email)-1] = '\0';

    printf("Enter category: ");
    fgets(contact.category,sizeof(contact.category),stdin);
    contact.category[strlen(contact.category)-1] = '\0';

    fp = fopen("contacts.txt","a");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp,"%s,%s,%s,%s,\n",contact.name,contact.phone,contact.email,contact.category);
    fclose(fp);

    printf("Contact added successfully!\n");
}

void displayContacts(){
    
    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    
    FILE *fp = fopen("contacts.txt","r");
    if (fp == NULL){
        printf("Error opening file!!!");
        return;
    }

    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp)) {
        char *token = strtok(line,",");
        if(token != NULL) {
            strcpy(contacts[numContacts].name,token);
            token = strtok(NULL,",");
            if(token != NULL) {
                strcpy(contacts[numContacts].phone,token);
                token = strtok(NULL,",");
                if (token != NULL) {
                    strcpy(contacts[numContacts].email,token);
                    token = strtok(NULL,",");
                    if (token != NULL) {
                    strcpy(contacts[numContacts].category,token);
                    }
                }
            }
        }
        numContacts++;
    }
    fclose(fp);

    if(numContacts == 0){
        printf("No contacts found.\n");
    } 
    else{
        printf("\nAll Contacts:\n\n");
        for(int i=0; i < numContacts; i++){
            printf("Name: %s\n",contacts[i].name);
            printf("Phone: %s\n",contacts[i].phone);
            printf("Email: %s\n",contacts[i].email);
            printf("Category: %s\n\n",contacts[i].category);
        }
    }
}

void searchName(){

    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0,found = 0;

    char name[50];
    printf("Enter name of contact to search: ");
    fgets(name,sizeof(name),stdin);
    name[strlen(name)-1] = '\0';
    
    FILE *fp = fopen("contacts.txt","r");
    if(fp == NULL){
        printf("Error opening file!!!");
        return;
    }
    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp)){
        char *token = strtok(line,",");
        if(token != NULL){
            strcpy(contacts[numContacts].name,token);
            token = strtok(NULL,",");
            if(token != NULL){
                strcpy(contacts[numContacts].phone,token);
                token = strtok(NULL,",");
                if(token != NULL){
                    strcpy(contacts[numContacts].email,token);
                    token = strtok(NULL,",");
                    if(token != NULL){
                        strcpy(contacts[numContacts].category,token);
                        numContacts++;
                    }
                }
            }
        }
    }
    fclose(fp);

    for(int i=0; i < numContacts; i++) {
        if(strcmp(contacts[i].name,name)==0){
            printf("\nName: %s\n",contacts[i].name);
            printf("Phone: %s\n",contacts[i].phone);
            printf("Email: %s\n",contacts[i].email);
            printf("Category: %s\n\n",contacts[i].category);
            found++;
        }
    }

    if(found==0)
        printf("No contacts found!");
    else
        printf("%d contact(s) found.",found);

}

void searchCategory(){

    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0,found = 0;

    char category[50];
    printf("Enter category of contact to search: ");
    fgets(category,sizeof(category),stdin);
    category[strlen(category)-1] = '\0';
    
    FILE *fp = fopen("contacts.txt","r");
    if(fp == NULL){
        printf("Error opening file!!!");
        return;
    }

    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp)){
        char *token = strtok(line, ",");
        if(token != NULL){
            strcpy(contacts[numContacts].name,token);
            token = strtok(NULL,",");
            if(token != NULL){
                strcpy(contacts[numContacts].phone,token);
                token = strtok(NULL,",");
                if(token != NULL){
                    strcpy(contacts[numContacts].email,token);
                    token = strtok(NULL,",");
                    if(token != NULL){
                        strcpy(contacts[numContacts].category,token);
                        numContacts++;
                    }
                }
            }
        }
    }
    fclose(fp);

    for(int i=0; i < numContacts; i++){
        if(strcmp(contacts[i].category,category)==0){
            printf("\nName: %s\n",contacts[i].name);
            printf("Phone: %s\n",contacts[i].phone);
            printf("Email: %s\n",contacts[i].email);
            printf("Category: %s\n\n",contacts[i].category);
            found++;
        }
    }

    if(found==0)
        printf("No contacts found!");
    else
        printf("%d contact(s) found.",found);

}

void editContact(){

    displayContacts();

    char name[50];
    printf("Enter name of contact to edit: ");
    fgets(name,sizeof(name),stdin);
    name[strlen(name)-1] = '\0';
    
    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0,found = 0;
    
    FILE *fp = fopen("contacts.txt","r");
    if(fp == NULL){
        printf("Error opening file!!!\n");
        return;
    }

    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp)){
        char *token = strtok(line,",");
        if(token != NULL && strcmp(token,name) == 0){
            found = 1;
            strcpy(contacts[numContacts].name,token);
            token = strtok(NULL,",");
            if(token != NULL){
                strcpy(contacts[numContacts].phone,token);
                printf("\nCurrent phone: %s\n",contacts[numContacts].phone);
                printf("Enter new phone: ");
                fgets(contacts[numContacts].phone,sizeof(contacts[numContacts].phone),stdin);
                contacts[numContacts].phone[strlen(contacts[numContacts].phone)-1] = '\0';

                token = strtok(NULL,",");
                if(token != NULL){
                    strcpy(contacts[numContacts].email,token);
                    printf("\nCurrent email: %s", contacts[numContacts].email);
                    printf("\nEnter new email: ");
                    fgets(contacts[numContacts].email,sizeof(contacts[numContacts].email),stdin);
                    contacts[numContacts].email[strlen(contacts[numContacts].email)-1] = '\0';

                    token = strtok(NULL,",");
                    if(token != NULL){
                        strcpy(contacts[numContacts].category,token);
                        printf("\nCurrent category: %s",contacts[numContacts].category);
                        printf("\nEnter new category: ");
                        fgets(contacts[numContacts].category,sizeof(contacts[numContacts].category),stdin);
                        contacts[numContacts].category[strlen(contacts[numContacts].category)-1] = '\0';
                        numContacts++;
                    }
                }
            }
        }
        else{
            strcpy(contacts[numContacts].name,token);
            token = strtok(NULL,",");
            if(token != NULL){
                strcpy(contacts[numContacts].phone,token);
                token = strtok(NULL,",");
                if(token != NULL){
                    strcpy(contacts[numContacts].email,token);
                    token = strtok(NULL,",");
                    if(token != NULL){
                        strcpy(contacts[numContacts].category,token);
                        numContacts++;
                    }
                }
            }
        }
    }
    fclose(fp);

    if(found==0){
        printf("Contact not found.\n");
        return;
    }

    fp = fopen("contacts.txt","w");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }

    for(int i=0; i < numContacts; i++){
        fprintf(fp,"%s,%s,%s,%s,\n",contacts[i].name,contacts[i].phone,contacts[i].email,contacts[i].category);
    }

    fclose(fp);
    printf("Contact edited successfully!\n");
}

void deleteContact(){

    displayContacts();

    char name[50];
    printf("Enter name of contact to delete: ");
    fgets(name,sizeof(name),stdin);
    name[strlen(name)-1] = '\0';

    FILE *fp = fopen("contacts.txt","r");
    if(fp == NULL){
        printf("Error opening file!!!");
        return;
    }

    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0,found = 0;
    char line[MAX_LINE];

    while(fgets(line, sizeof(line),fp)){
        char *token = strtok(line,",");
        if(token != NULL && strcmp(token,name) == 0){
            found = 1;
        } else{
            strcpy(contacts[numContacts].name,token);
            token = strtok(NULL,",");
            if(token != NULL){
                strcpy(contacts[numContacts].phone,token);
                token = strtok(NULL,",");
                if(token != NULL){
                    strcpy(contacts[numContacts].email,token);
                    token = strtok(NULL,",");
                    if(token != NULL){
                        strcpy(contacts[numContacts].category,token);
                        numContacts++;
                    }
                }
            }
        }
    }
    fclose(fp);
    
    if(found == 0){
        printf("Contact not found.\n");
        return;
    }
    fp = fopen("contacts.txt", "w");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }

    for(int i=0; i < numContacts; i++){
        fprintf(fp,"%s,%s,%s,%s,\n",contacts[i].name,contacts[i].phone,contacts[i].email,contacts[i].category);
    }

    fclose(fp);
    printf("Contact deleted successfully!\n");

}

void deleteAllContacts(){

    char check;
    printf("Are you sure you want to delete all contacts? (y/n):");
    scanf("%c",&check);
    if(check=='y' || check=='Y'){
        FILE *fp = fopen("contacts.txt", "w");
        fclose(fp);
        printf("All contacts have been deleted successfully!\n");
    }
}

void main(){
    printf("*** Welcome to CONTACT MANAGEMENT SYSTEM ***\n\n");
    int choice,search;
    char cont = 'y';

    while(cont == 'y' || cont == 'Y'){
        printf("\n\nACTION MENU:\n");
        printf("[1] Add contact\n");
        printf("[2] Display contacts\n");
        printf("[3] Search contacts\n");
        printf("[4] Edit contact\n");
        printf("[5] Delete a contact\n");
        printf("[6] Delete all contacts\n");
        printf("[7] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                printf("\n\nSEARCH MENU:\n");
                printf("[1] Search using Name\n");
                printf("[2] Search using Category\n");
                printf("Enter your choice: ");
                scanf("%d", &search);
                getchar();

                switch(search){
                    case 1:
                        searchName();
                        break;
                    case 2:
                        searchCategory();
                        break;
                    default:
                        printf("Invalid choice.");
                        break;
                }
                break;
            case 4:
                editContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                deleteAllContacts();
                break;
            case 7:
                printf("Exiting...\n");
                cont = 'n';
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 5.\n");
                break;
        }
        if(choice != 7){
            printf("\nDo you want to continue? (y/n): ");
            scanf(" %c", &cont);
            getchar();
            system("cls");
        }
    }
}