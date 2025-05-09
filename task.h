#pragma once

struct Task {
    int taskID;
    char name[100];
    int priority;
    char deadline[20];
    int assignedUserID;
    int dependencyTaskID;
    char status[20];
    struct Task* next;
} ;

struct TaskList {
    struct Task* head;
} ;

// Task-related function prototypes
struct Task* createTask(int taskID, char name[], int priority, char deadline[]);
void addTask(struct TaskList* list);
void deleteTask(struct TaskList* list, int taskID);
void assignTaskToUser(struct TaskList* list, int taskID, int userID);
void setTaskDependency(struct TaskList* list, int taskID, int dependencyID);
void viewTasks(struct TaskList* list);
