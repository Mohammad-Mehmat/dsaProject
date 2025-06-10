#pragma once
# include <stdbool.h>
#include <stdio.h>
typedef struct UserData{
    int userID;
    char name[100];
    int tasksAssigned;
    int tasksCompleted;

} UserData;

typedef struct User{
    UserData data;
    struct User * next;
} User;

// User-related function prototypes
void addUser(User** user);
void printUsers(User* user);
void inputUserData(User* newUser);
struct User* findUserByID(User* user, int userID);
bool saveUsersToFile(User* userHead, FILE* fptr);
bool loadUsersFromFile(User** userHead, FILE* fptr);
bool isUserListEmpty(User * userHead);
