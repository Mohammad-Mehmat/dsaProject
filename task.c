#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void inputTaskData(Task* task) {
    if (task == NULL) return;

    setColor(11);
    printf("\n+++ Enter Task Details +++\n");
    setColor(14);

    printf("ID: ");
    scanf("%d", &task->data.taskID);

    printf("Name: ");
    scanf(" %[^\n]", task->data.name);

    do {
        printf("Priority (1-10): ");
        scanf("%d", &task->data.priority);
        if (task->data.priority < 1 || task->data.priority > 10) {
            setColor(4);
            printf("Invalid priority. Please enter a value between 1 and 10.\n");
            setColor(14);
        }
    } while (task->data.priority < 1 || task->data.priority > 10);

    printf("Deadline: ");
    scanf(" %[^\n]", task->data.deadline);

    task->data.assignedUserID = -1;
    task->data.assignedResourceID = -1;
    task->data.dependencyTaskID = -1;
    task->data.status = PENDING;
}

void addTask(Task** taskHead) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (!newTask) {
        setColor(4);
        printf("Memory allocation failed!!!\n");
        setColor(14);
        return;
    }

    inputTaskData(newTask);
    

    Task* temp = *taskHead;
    while (temp != NULL) {
        if (temp->data.taskID == newTask->data.taskID) {
            setColor(4);
            printf("Error: Task ID %d already exists!\n", newTask->data.taskID);
            setColor(14);
            free(newTask);
            return;
        }
        temp = temp->next;
    }
    
    newTask->next = NULL;

    if (isTaskListEmpty(*taskHead)) {
        *taskHead = newTask;
    } else if ((newTask->data.priority >= (*taskHead)->data.priority)) {
        newTask->next = *taskHead;
        *taskHead = newTask;
    } else {
        Task* tempTask = *taskHead;
        while (tempTask->next != NULL && tempTask->next->data.priority >= newTask->data.priority)
            tempTask = tempTask->next;
        newTask->next = tempTask->next;
        tempTask->next = newTask;
    }
    
    setColor(10);
    printf("Task added successfully!\n");
    setColor(14);
}

bool isTaskListEmpty(Task* taskHead) {
    return (taskHead == NULL);
}

int setTaskDependency(Task* taskHead) {
    if (isTaskListEmpty(taskHead)) {
        setColor(4);
        printf("Error: Task list is empty.\n");
        setColor(14);
        return 0;
    }

    int taskID, dependencyID;
    printf("Enter Task ID of the Task that depends on the other Task: ");
    scanf("%d", &taskID);
    printf("Enter Dependency Task ID: ");
    scanf("%d", &dependencyID);
    

    if (taskID == dependencyID) {
        setColor(4);
        printf("Error: A task cannot depend on itself.\n");
        setColor(14);
        return 0;
    }
    
    Task* tempTask = taskHead;
    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }
    
    if (tempTask == NULL) {
        setColor(4);
        printf("Error: Task with ID %d not found.\n", taskID);
        setColor(14);
        return 0;
    }
    
    Task* dependencyTask = taskHead;
    while (dependencyTask != NULL && dependencyTask->data.taskID != dependencyID) {
        dependencyTask = dependencyTask->next;
    }
    
    if (dependencyTask == NULL) {
        setColor(4);
        printf("Error: Dependency task with ID %d not found.\n", dependencyID);
        setColor(14);
        return 0;
    }
    
   
    if (dependencyTask->data.status == COMPLETED) {
        tempTask->data.dependencyTaskID = dependencyID;
        setColor(10);
        printf("Dependency set successfully. Task %d depends on completed task %d.\n", taskID, dependencyID);
        setColor(14);
    } else {
        tempTask->data.dependencyTaskID = dependencyID;
        tempTask->data.status = BLOCKED;
        setColor(10);
        printf("Dependency set successfully. Task %d is now blocked until task %d is completed.\n", taskID, dependencyID);
        setColor(14);
    }

    return 1;
}

void printTask(Task* task) {
    if (task == NULL) 
        return;

    setColor(10); 
    printf("\nTask ID   : %d\nTask Name : %s\n", task->data.taskID, task->data.name);
    setColor(14);
    printf("Priority  : %d\n", task->data.priority);
    printf("Deadline  : %s\n", task->data.deadline);

    printf("Status    : ");
    if (task->data.status == PENDING) {
        printf("PENDING\n");
    } else if (task->data.status == IN_PROGRESS) {
        printf("IN_PROGRESS\n");
    } else if (task->data.status == COMPLETED) {
        printf("COMPLETED\n");
    } else {
        printf("BLOCKED\n");
    }
    
    printf("Assigned User     : %s\n", (task->data.assignedUserID == -1) ? "None" : "");
    if (task->data.assignedUserID != -1) {
        printf("%d\n", task->data.assignedUserID);
    }
    
    printf("Assigned Resource : %s\n", (task->data.assignedResourceID == -1) ? "None" : "");
    if (task->data.assignedResourceID != -1) {
        printf("%d\n", task->data.assignedResourceID);
    }
    
    printf("Depends On        : %s\n", (task->data.dependencyTaskID == -1) ? "None" : "");
    if (task->data.dependencyTaskID != -1) {
        printf("%d\n", task->data.dependencyTaskID);
    }
    
    printf("----------------------------------------\n");
}

void viewTasks(Task* task) {
    if (!task) {
        setColor(4);
        printf("No tasks available.\n");
        setColor(14);
        return;
    }

    setColor(11);
    printf("\n=== TASK LIST ===\n");
    setColor(14);
    while (task) {
        printTask(task);
        task = task->next;
    }
    setColor(7);
    printf("=== END OF LIST ===\n");
    setColor(14);
}

int assignTaskToUser(Task* taskHead, User* userHead) {
    if (taskHead == NULL) {
        setColor(4);
        printf("Error: Tasks do not exist.\n");
        setColor(14);
        return 0;
    }
    if (userHead == NULL) {
        setColor(4);
        printf("Error: Users do not exist.\n");
        setColor(14);
        return 0;
    }

    int taskID, userID;
    printf("Enter Task ID: ");
    scanf("%d", &taskID);
    printf("Enter User ID: ");
    scanf("%d", &userID);

    Task* tempTask = taskHead;
    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }
    if (tempTask == NULL) {
        setColor(4);
        printf("Error: Task with ID %d not found.\n", taskID);
        setColor(14);
        return 0;
    }

    User* tempUser = userHead;
    while (tempUser != NULL && tempUser->data.userID != userID) {
        tempUser = tempUser->next;
    }
    if (tempUser == NULL) {
        setColor(4);
        printf("Error: User with ID %d not found.\n", userID);
        setColor(14);
        return 0;
    }
    
    if (tempTask->data.assignedUserID == -1) {
        
        if (tempTask->data.status == BLOCKED) {
            setColor(4);
            printf("Error: Cannot assign blocked task %d to user %d.\n", taskID, userID);
            setColor(14);
            return 0;
        }
        
        tempTask->data.assignedUserID = userID;
        tempTask->data.status = IN_PROGRESS; 
        tempUser->data.tasksAssigned++;
        setColor(10);
        printf("User %d assigned to task %d successfully.\n", userID, taskID);
        setColor(14);
        return 1;
    } else {
        setColor(4);
        printf("Error: Task %d is already assigned to user %d.\n", taskID, tempTask->data.assignedUserID);
        setColor(14);
    }
    
    return 0;
}

bool allocateResourceToTask(Task* taskHead, Resource* resourceHead) {
    if (taskHead == NULL) {
        setColor(4);
        printf("Error: There are no tasks in the list.\n");
        setColor(14);
        return false;
    }
    if (resourceHead == NULL) {
        setColor(4);
        printf("Error: There are no resources in the list.\n");
        setColor(14);
        return false;
    }
    
    int resourceID, taskID;
    printf("Enter Resource ID: ");
    scanf("%d", &resourceID);
    printf("Enter Task ID to allocate: ");
    scanf("%d", &taskID);
    
    Task* tempTask = taskHead;
    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }
    if (tempTask == NULL) {
        setColor(4);
        printf("Error: Task with ID %d not found.\n", taskID);
        setColor(14);
        return false;
    }

    Resource* tempResource = resourceHead;
    while (tempResource != NULL && tempResource->data.resourceID != resourceID) {
        tempResource = tempResource->next;
    }
    if (tempResource == NULL) {
        setColor(4);
        printf("Error: Resource with ID %d not found.\n", resourceID);
        setColor(14);
        return false;
    }
    
    if (tempResource->data.assignedTaskID == -1) {
        tempTask->data.assignedResourceID = resourceID;
        tempResource->data.assignedTaskID = tempTask->data.taskID;
        setColor(10);
        printf("Resource %d allocated to task %d successfully.\n", resourceID, taskID);
        setColor(14);
    } else {
        setColor(4);
        printf("Resource Already Allocated to Task with ID %d\n", tempResource->data.assignedTaskID);
        setColor(14);
        return false;
    }
    
    return true;
}

bool saveTasksToFile(Task* taskHead, FILE* fptr) {
    if (taskHead == NULL || fptr == NULL) {
        setColor(4);
        printf("\nError: Null pointer\n");
        setColor(14);
        return false;
    }
    
    Task* current = taskHead;
    int count = 0;
    while (current != NULL) {
        if (fwrite(&(current->data), sizeof(TaskData), 1, fptr) != 1) {
            setColor(4);
            printf("Error: Failed to write task data to file.\n");
            setColor(14);
            return false;
        }
        current = current->next;
        count++;
    }
    
    setColor(10);
    printf("Successfully saved %d tasks to file.\n", count);
    setColor(14);
    return true;
}

bool loadTasksFromFile(Task** taskHead, FILE* fptr) {
    if (fptr == NULL || taskHead == NULL) {
        setColor(4);
        printf("Error: Pointer is Null\n");
        setColor(14);
        return false;
    }

    TaskData newData;
    Task* tempTask = *taskHead;
    int count = 0;

    while (fread(&newData, sizeof(TaskData), 1, fptr) == 1) {
        Task* newTask = (Task*)malloc(sizeof(Task));
        if (newTask == NULL) {
            setColor(4);
            printf("Error: Memory allocation failed while loading tasks.\n");
            setColor(14);
            return false;
        }

        newTask->data = newData;
        newTask->next = NULL;

        if (*taskHead == NULL) {
            *taskHead = newTask;
            tempTask = *taskHead;
        } else {
            tempTask->next = newTask;
            tempTask = tempTask->next;
        }
        count++;
    }
    
    if (count == 0) {
        setColor(4);
        printf("Error: No tasks loaded from file.\n");
        setColor(14);
        return false;
    }
    
    setColor(10);
    printf("Successfully loaded %d tasks from file.\n", count);
    setColor(14);
    return true;
}

bool TaskCompleted(Task* taskHead, Resource* resourceHead, User* userHead) {
    if (isTaskListEmpty(taskHead) || isResourceListEmpty(resourceHead) || isUserListEmpty(userHead)) {
        setColor(4);
        printf("Error: One of the lists is empty.\n");
        setColor(14);
        return false;
    }

    int taskID;
    printf("Enter Task ID to mark as completed: ");
    scanf("%d", &taskID);

    Task* tempTask = taskHead;
    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }

    if (tempTask == NULL) {
        setColor(4);
        printf("Error: Task with ID %d not found.\n", taskID);
        setColor(14);
        return false;
    }
    if (tempTask->data.assignedUserID == -1) {
        setColor(4);
        printf("Error: Task %d is not assigned to any user.\n", taskID);
        setColor(14);
        return false;
    }
    if (tempTask->data.status == COMPLETED) {
        setColor(4);
        printf("Error: Task %d is already completed.\n", taskID);
        setColor(14);
        return true;
    }
    if (tempTask->data.status == BLOCKED) {
        setColor(4);
        printf("Error: Task %d is blocked and cannot be marked as completed.\n", taskID);
        setColor(14);
        return false;
    }

    Resource* tempResource = resourceHead;
    while (tempResource != NULL && tempResource->data.assignedTaskID != taskID) {
        tempResource = tempResource->next;
    }

    if (tempResource == NULL) {
        setColor(4);
        printf("Error: Resource associated with Task ID %d not found.\n", taskID);
        setColor(14);
        return false;
    }

    User* tempUser = userHead;
    while (tempUser != NULL && tempUser->data.userID != tempTask->data.assignedUserID) {
        tempUser = tempUser->next;
    }

    if (tempUser == NULL) {
        setColor(4);
        printf("Error: User with ID %d not found.\n", tempTask->data.assignedUserID);
        setColor(14);
        return false;
    }

    tempTask->data.status = COMPLETED;
    tempResource->data.assignedTaskID = -1;
    tempUser->data.tasksCompleted++;

    setColor(2); 
    printf("Task %d marked as completed.\n", taskID);
    setColor(14);
    

    Task* current = taskHead;
    while (current != NULL) {
        if (current->data.dependencyTaskID == taskID && current->data.status == BLOCKED) {
            current->data.status = PENDING;
            setColor(10);
            printf("Task %d has been unblocked.\n", current->data.taskID);
            setColor(14);
        }
        current = current->next;
    }
    
    return true;
}