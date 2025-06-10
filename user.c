#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include <string.h>

void addUser( User **userHead ) {    
    User * newUser = (struct User *) malloc (sizeof (struct User)) ;
    if (!newUser) {
        printf("Memory allocation failed!!!");
        return;
    }

    inputUserData(newUser);
    newUser->next = NULL;

    if (isUserListEmpty(*userHead)) {
        *userHead = newUser;
    } else {
        User* temp = *userHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newUser;
    }
    
}

void inputUserData(User *newUser) {
    setColor(11);
    printf("\n+++ New User +++\n");
    setColor( 14);

    printf("Name: ");
    scanf(" %[^\n]", newUser->data.name);

    printf("ID: ");
    scanf("%d", &newUser->data.userID);

    newUser->data.tasksAssigned = 0;
    newUser->data.tasksCompleted = 0;
}
void printUsers( User *userHead) {
    User* tempUser = userHead;

    if (tempUser == NULL) {
       setColor(12);
        printf("No users found.\n");
        setColor( 14);
        return;
    }
    setColor(10);
    printf("\n=== USER LIST ===\n");
        setColor( 14);
    while (tempUser != NULL) {
        setColor(14);
        printf("\n----------------------------------------\n");
        printf("User Name : %s\n", tempUser->data.name);
        printf("User ID   : %d\n", tempUser->data.userID);
        printf("Assigned  : %d\n", tempUser->data.tasksAssigned);
        printf("Completed : %d\n", tempUser->data.tasksCompleted);
        tempUser = tempUser->next;
    }
    free(tempUser);
        
}

bool saveUsersToFile(User* userHead, FILE* fptr) {
     if (userHead ==NULL || fptr == NULL) {
        printf("\nError :  Null pointer");
        return false;
    }

    User* current = userHead;
    while (current != NULL ) {
        
        fwrite(&(current->data), sizeof(UserData), 1, fptr);
        current = current ->next;
    }

    fclose(fptr);
    free(current);
    return true;
}

bool loadUsersFromFile(User** userHead, FILE* fptr) {

    UserData newData;
    User * tempUser = *userHead;

    if (fptr == NULL || userHead == NULL) {
        printf("Error: Pointer is Null \n");
        return false;
    }

     while (fread (&newData, sizeof(UserData), 1, fptr)) {
        User * new_User = (User *) malloc(sizeof(User));

        new_User->data = newData;
        new_User->next = NULL;

        if(*userHead == NULL)   
        {
            *userHead = new_User;
            tempUser = *userHead;
        }
        else
        {
            tempUser->next = new_User;
            tempUser = tempUser->next;
        }

    }
    fclose(fptr);
    if (tempUser == NULL) {
        printf("Error: No users loaded from file.\n");
        return false;
    }
    free(tempUser);
    return true;

}


bool isUserListEmpty(User * userHead)
{
    return (userHead == NULL);
}
