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


// struct User* findUserByID(struct User* user, int userID) {
//     struct User* current = user->next;
//     while (current != NULL) {
//         if (current->userID == userID) {
//             return current; 
//         }
//         current = current->next;
//     }
//     return NULL; 
// }



// int saveUsersToFile(struct User* user, const char* filename) {
//     FILE* file = fopen(filename, "w");
//     if (!file) {
//         printf("Error opening file for writing.\n");
//         return 0;
//     }

//     struct User* current = user->next;
//     while (current != NULL) {
//         fprintf(file, "%d,%s,%d,%d\n", current->userID, current->name, current->tasksAssigned, current->tasksCompleted);
//         current = current->next;
//     }

//     fclose(file);
//     return 1;
// }


// int loadUsersFromFile(struct User* user, const char* filename) {
//     FILE* file = fopen(filename, "r");
//     if (!file) {
//         printf("Error opening file for reading.\n");
//         return 0;
//     }

//     // Clear existing user
//     user->next = NULL;

//     while (!feof(file)) {
//         struct User* newUser = (struct User*)malloc(sizeof(struct User));
//         if (fscanf(file, "%d,%99[^,],%d,%d\n", &newUser->userID, newUser->name, &newUser->tasksAssigned, &newUser->tasksCompleted) == 4) {
//             newUser->next = user->next;
//             user->next = newUser;
//         } else {
//             free(newUser); // clean up if the line is malformed
//         }
//     }

//     fclose(file);
//     return 1;
// }

bool isUserListEmpty(User * userHead)
{
    return (userHead == NULL);
}