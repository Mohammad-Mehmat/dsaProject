#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include <string.h>

void addUser(struct UserList *list )
{    
    struct User * newUser = (struct User *) malloc (sizeof (struct User)) ;
    if (!newUser){
        printf("Memory allocation failed!!!");
        return;
    }
    inputUserData(newUser);
    if (list->head == NULL) {
        list->head = newUser;
        return ;
    }
    else {
        struct User* temp = list->head;
        while (temp->next!=NULL)
            temp=temp->next;
         temp->next = newUser;
        
    }
   

}

void viewUsers(struct UserList *list) {
    struct User* temp = list->head;

    if (temp == NULL) {
        printf("No users found.\n");
        return;
    }

    printf("\n--- User List ---\n");
    while (temp != NULL) {
        printf("Name     : %s\n", temp->name);
        printf("User ID  : %d\n", temp->userID);
        printf("Assigned : %d\n", temp->tasksAssigned);
        printf("Completed: %d\n", temp->tasksCompleted);
        printf("---------------------\n");
        temp = temp->next;
    }
}


void inputUserData(struct User *newUser) {
    printf("Enter the name of the user: ");
    getchar(); // Consume leftover newline if needed
    fgets(newUser->name, sizeof(newUser->name), stdin);
    newUser->name[strcspn(newUser->name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the ID of the user: ");
    scanf("%d", &newUser->userID);
}
struct User* findUserByID(struct UserList* list, int userID) {
    struct User* current = list->head;
    while (current != NULL) {
        if (current->userID == userID) {
            return current; 
        }
        current = current->next;
    }
    return NULL; 
}