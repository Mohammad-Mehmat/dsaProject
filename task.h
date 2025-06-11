#pragma once
#include "user.h"
#include "resource.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    BLOCKED
} TaskStatus;

typedef struct TaskData {
    int taskID;
    char name[100];
    int priority;           // 1-10 (10 = highest)
    char deadline[11];      // YYYY-MM-DD format
    int assignedUserID;     // -1 if unassigned
    int assignedResourceID; // -1 if no resource
    int dependencyTaskID;   // -1 if no dependency
    TaskStatus status;
} TaskData;

typedef struct Task {
    TaskData data;
    struct Task* next; 
} Task;

// Initialization
void initTask( Task* task);
void freeTask( Task* task);

// Core operations
void inputTaskData (Task* newTask);
void addTask( Task ** task);
//bool deleteTask(struct Task* task, int taskID);
void printTask( Task* task);
void viewTasks( Task* task);

// Assignment operations
int assignTaskToUser(Task *taskHead, User *userHead);
bool allocateResourceToTask( Task* task, Resource *resourceHead);

// // Utility functions
bool canAssignTask(const struct Task* task);
// bool isTaskComplete(const struct Task* task);
bool saveTasksToFile( Task* taskHead, FILE* fptr);
bool loadTasksFromFile(Task** taskHead, FILE* fptr);
bool isTaskListEmpty(Task * taskHead);
int setTaskDependency(Task *taskHead);

extern void setColor(int color);
bool TaskCompleted(Task* taskHead, Resource* resourceHead, User* userHead);