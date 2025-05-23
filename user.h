#pragma once

struct User {
    int userID;
    char name[100];
    int tasksAssigned;
    int tasksCompleted;
    struct User* next;
} ;

struct UserList {

    struct User * head;
} ;

// User-related function prototypes
void addUser(struct UserList* list);
void viewUsers(struct UserList* list);
void inputUserData(struct User* newUser);
struct User* findUserByID(struct UserList* list, int userID);
int saveUsersToFile(struct UserList* list, const char* filename);
int loadUsersFromFile(struct UserList* list, const char* filename);
