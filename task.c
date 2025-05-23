
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Initialize task list
void initTaskList(struct TaskList* list) {
    list->head = list->tail = NULL;
    list->count = 0;
}

// Free all tasks in list
void freeTaskList(struct TaskList* list) {
    struct Task* current = list->head;
    while (current) {
        struct Task* next = current->next;
        free(current);
        current = next;
    }
    list->head = list->tail = NULL;
    list->count = 0;
}

// Create new task
struct Task* createTask(int id, const char* name, int priority, const char* deadline) {
    // Validate inputs
    if (id < 0 || !name || !deadline) return NULL;
    if (priority < 1 || priority > 10) return NULL;
    
    struct Task* task = (struct Task*)malloc(sizeof(struct Task));
    if (!task) return NULL;

    task->taskID = id;
    strncpy(task->name, name, sizeof(task->name));
    task->priority = priority;
    strncpy(task->deadline, deadline, sizeof(task->deadline));
    task->assignedUserID = -1;
    task->assignedResourceID = -1;
    task->dependencyTaskID = -1;
    task->status = PENDING;
    task->next = NULL;

    return task;
}

// Add task to list (O(1) operation)
bool addTask(struct TaskList* list, struct Task* task) {
    if (!list || !task) return false;

    if (!list->head) {
        list->head = task;
    } else {
        list->tail->next = task;
    }
    list->tail = task;
    list->count++;
    return true;
}

// Delete task from list
bool deleteTask(struct TaskList* list, int taskID) {
    if (!list || !list->head) return false;

    struct Task *current = list->head, *prev = NULL;
    
    // Find task to delete
    while (current && current->taskID != taskID) {
        prev = current;
        current = current->next;
    }

    if (!current) return false; // Not found

    // Update list pointers
    if (current == list->head) list->head = current->next;
    if (current == list->tail) list->tail = prev;
    if (prev) prev->next = current->next;

    free(current);
    list->count--;
    return true;
}

// Print task details
void printTask(const struct Task* task) {
    if (!task) return;

    const char* statusStr[] = {"Pending", "In Progress", "Completed", "Blocked"};
    
    printf("\nTask ID: %d\n", task->taskID);
    printf("Name: %s\n", task->name);
    printf("Priority: %d\n", task->priority);
    printf("Deadline: %s\n", task->deadline);
    printf("Status: %s\n", statusStr[task->status]);
    printf("Assigned User: %d\n", task->assignedUserID);
    printf("Assigned Resource: %d\n", task->assignedResourceID);
    printf("Depends On: %d\n", task->dependencyTaskID);
}

// Print all tasks
void printAllTasks(const struct TaskList* list) {
    if (!list) return;

    printf("\n=== TASK LIST (%d tasks) ===\n", list->count);
    struct Task* current = list->head;
    while (current) {
        printTask(current);
        current = current->next;
    }
    printf("=== END OF LIST ===\n");
}

// Assign user to task
bool assignUserToTask(struct TaskList* list, int taskID, int userID) {
    struct Task* task = findTask(list, taskID);
    if (!task || !canAssignTask(task) || userID < 0) return false;

    task->assignedUserID = userID;
    task->status = (task->status == PENDING) ? IN_PROGRESS : task->status;
    return true;
}

// Assign resource to task
bool assignResourceToTask(struct TaskList* list, int taskID, int resourceID) {
    struct Task* task = findTask(list, taskID);
    if (!task || resourceID < 0) return false;

    task->assignedResourceID = resourceID;
    return true;
}

// Find task by ID
struct Task* findTask(const struct TaskList* list, int taskID) {
    if (!list) return NULL;

    struct Task* current = list->head;
    while (current) {
        if (current->taskID == taskID) return current;
        current = current->next;
    }
    return NULL;
}

// Check if task can be assigned
bool canAssignTask(const struct Task* task) {
    return task && 
           task->status != COMPLETED && 
           task->dependencyTaskID == -1;
}

// Check if task is complete
bool isTaskComplete(const struct Task* task) {
    return task && task->status == COMPLETED;
}

// Save tasks to file
bool saveTasksToFile(const struct TaskList* list, const char* filename) {
    if (!list || !filename) return false;

    FILE* file = fopen(filename, "w");
    if (!file) return false;

    struct Task* current = list->head;
    while (current) {
        fprintf(file, "%d,%s,%d,%s,%d,%d,%d,%d\n",
                current->taskID,
                current->name,
                current->priority,
                current->deadline,
                current->assignedUserID,
                current->assignedResourceID,
                current->dependencyTaskID,
                current->status);
        current = current->next;
    }

    fclose(file);
    return true;
}

// Load tasks from file
bool loadTasksFromFile(struct TaskList* list, const char* filename) {
    if (!list || !filename) return false;

    FILE* file = fopen(filename, "r");
    if (!file) return false;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        struct Task task;
        int status;
        if (sscanf(line, "%d,%99[^,],%d,%10[^,],%d,%d,%d,%d",
                   &task.taskID,
                   task.name,
                   &task.priority,
                   task.deadline,
                   &task.assignedUserID,
                   &task.assignedResourceID,
                   &task.dependencyTaskID,
                   &status) == 8) {
            task.status = (TaskStatus)status;
            struct Task* newTask = createTask(task.taskID, task.name, task.priority, task.deadline);
            if (newTask) {
                newTask->assignedUserID = task.assignedUserID;
                newTask->assignedResourceID = task.assignedResourceID;
                newTask->dependencyTaskID = task.dependencyTaskID;
                newTask->status = task.status;
                addTask(list, newTask);
            }
        }
    }

    fclose(file);
    return true;
}