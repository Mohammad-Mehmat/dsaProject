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
    printf("Enter the name of the user: ");
    scanf(" %[^\n]", newUser->data.name);
    printf("Enter the ID of the user: ");
    scanf("%d", &newUser->data.userID); 
    newUser->data.tasksAssigned = 0;
    newUser->data.tasksCompleted = 0; 
}
void printUsers( User *user) {
    User* temp = user;

    if (temp == NULL) {
        printf("No users found.\n");
        return;
    }

    printf("\n--- User user ---\n");
    while (temp != NULL) {
        printf("Name     : %s\n", temp->data.name);
        printf("User ID  : %d\n", temp->data.userID);
        printf("Task Assigned : %d\n", temp->data.tasksAssigned);
        printf("Task Completed: %d\n", temp->data.tasksCompleted);
        printf("---------------------\n");
        temp = temp->next;
    }
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
    return true;
}

// Load tasks from file
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

        if(*userHead == NULL)    /// The list will be empty the first time
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
    return true;

}


bool isUserListEmpty(User * userHead)
{
    return (userHead == NULL);
}
