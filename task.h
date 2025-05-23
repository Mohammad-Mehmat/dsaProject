#pragma once

#include <stdbool.h>

typedef enum {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    BLOCKED
} TaskStatus;

struct Task {
    int taskID;
    char name[100];
    int priority;           // 1-10 (10 = highest)
    char deadline[11];      // YYYY-MM-DD format
    int assignedUserID;     // -1 if unassigned
    int assignedResourceID; // -1 if no resource
    int dependencyTaskID;   // -1 if no dependency
    TaskStatus status;
    struct Task* next;
};

struct TaskList {
    struct Task* head;
    struct Task* tail;
    int count;
};

// Initialization
void initTaskList(struct TaskList* list);
void freeTaskList(struct TaskList* list);

// Core operations
struct Task* createTask(int id, const char* name, int priority, const char* deadline);
bool addTask(struct TaskList* list, struct Task* task);
bool deleteTask(struct TaskList* list, int taskID);
void printTask(const struct Task* task);
void printAllTasks(const struct TaskList* list);

// Assignment operations
bool assignUserToTask(struct TaskList* list, int taskID, int userID);
bool assignResourceToTask(struct TaskList* list, int taskID, int resourceID);

// Utility functions
struct Task* findTask(const struct TaskList* list, int taskID);
bool canAssignTask(const struct Task* task);
bool isTaskComplete(const struct Task* task);
bool saveTasksToFile(const struct TaskList* list, const char* filename);
bool loadTasksFromFile(struct TaskList* list, const char* filename);

