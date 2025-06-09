#pragma once
# include <stdbool.h>
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
int saveUsersToFile(User* user, const char* filename);
int loadUsersFromFile(User* user, const char* filename);
bool isUserListEmpty(User * userHead);
