
#include "task.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void inputTaskData(Task* task) {
    if (!task) return;

    printf("Enter Task ID: ");
    scanf("%d", &task->data.taskID);

    printf("Enter Task Name: ");
    scanf(" %[^\n]", task->data.name);

    printf("Enter Task Priority (1-10): ");
    scanf("%d", &task->data.priority);

    printf("Enter Task Deadline: ");
    scanf(" %[^\n]", task->data.deadline);
    task->data.assignedUserID = -1;
    task->data.assignedResourceID = -1;
    task->data.dependencyTaskID = -1;
    task->data.status = PENDING;
    task->next = NULL;

}


void addTask(Task** taskHead) {
     Task * newTask = (Task *) malloc (sizeof ( Task)) ;
    if (!newTask) {
        printf("Memory allocation failed!!!");
        return;
    }

    inputTaskData(newTask);
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
}
bool isTaskListEmpty(Task * taskHead)
{
    return (taskHead == NULL);
}

int setTaskDependency(Task *taskHead)
{
    if (isTaskListEmpty(taskHead)) {
        printf("Error: Task list is empty.\n");
        return 0;
    }

    int taskID, dependencyID;
    printf("Enter Task ID of the Task that depends on the other Tassk: ");
    scanf("%d", &taskID);
    printf("Enter Dependency Task ID: ");
    scanf("%d", &dependencyID);
    
    Task *tempTask = taskHead;
    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }
    Task *dependencyTask = taskHead;
    while (dependencyTask != NULL && dependencyTask->data.taskID != dependencyID) {
        dependencyTask = dependencyTask->next;
    }
    if (dependencyTask == NULL) {
        printf("Error: Dependency task with ID %d not found.\n", dependencyID);
        return 0;
    }
    if (tempTask != NULL) {
        tempTask->data.dependencyTaskID = dependencyID;
        tempTask->data.status = BLOCKED; 
    } else {
        printf("Task not found.\n");
    }
    return 0;
}


void printTask( Task* task) {
    if (!task) return;

    
    printf("\nTask ID: %d\n", task->data.taskID);
    printf("Name: %s\n", task->data.name);
    printf("Priority: %d\n", task->data.priority);
    printf("Deadline: %s\n", task->data.deadline);
    if(task->data.status == PENDING) {
        printf("Status: PENDING\n");
    } else if(task->data.status == IN_PROGRESS) {
        printf("Status: IN_PROGRESS\n");
    } else if(task->data.status == COMPLETED) {
        printf("Status: COMPLETED\n");
    } else {
        printf("Status: BLOCKED\n");
    }
    printf("Assigned User: %d\n", task->data.assignedUserID);
    printf("Assigned Resource: %d\n", task->data.assignedResourceID);
    printf("Depends On: %d\n", task->data.dependencyTaskID);
}

void viewTasks(Task* task) {
    if (!task) return;

    printf("\n=== TASK LIST ===\n");
    while (task) {
        printTask(task);
        task = task->next;
    }
    printf("=== END OF LIST ===\n");
}


int assignTaskToUser(Task *taskHead, User *userHead) {
    Task *tempTask = taskHead;
    User *tempUser = userHead;

    if (tempTask == NULL) {
        printf("Error: Tasks do not exist.\n");
        return 0;
    }
    if (tempUser == NULL) {
        printf("Error: Users do not exist.\n");
        return 0;
    }

    int taskID, userID;
    printf("Enter Task ID: ");
    scanf("%d", &taskID);
    printf("Enter User ID: ");
    scanf("%d", &userID);


    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }
    if (tempTask == NULL) {
        printf("Error: Task with ID %d not found.\n", taskID);
        return 0;
    }

    while (tempUser != NULL && tempUser->data.userID != userID) {
        tempUser = tempUser->next;
    }
    if (tempUser == NULL) {
        printf("Error: User with ID %d not found.\n", userID);
        return 0;
    }
    if (tempTask->data.assignedUserID == -1) {
         tempTask->data.assignedUserID = userID;
        tempTask->data.status = IN_PROGRESS; 
        tempUser->data.tasksAssigned++;
        printf("User %d assigned to task %d successfully.\n", userID, taskID);
        return 1;
    } else {
       printf("Error: Task %d is already assigned to user %d.\n", taskID, tempTask->data.assignedUserID);
   }
   return 0;
}

bool allocateResourceToTask(Task* taskHead, Resource *resourceHead) {
    Task *tempTask = taskHead;
    Resource *tempRsource = resourceHead;
    int resourceID, taskID;
    printf("Enter Resource ID: ");
    scanf("%d", &resourceID);
    printf("Enter Task ID to allocate: ");
    scanf("%d", &taskID);
    if (taskHead==NULL){
        printf("Error: Ther are no tasks in the list");
        return false;
    }
    if (resourceHead==NULL){
        printf("Error: There are no resources in the list");
        return false;
    }
    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }
    if (tempTask == NULL) {
        printf("Error: Task with ID %d not found.\n", taskID);
        return false;
    }

    while (tempRsource != NULL && tempRsource->data.resourceID != resourceID) {
        tempRsource = tempRsource->next;
    }
    if (tempRsource == NULL) {
        printf("Error: Resource with ID %d not found.\n", resourceID);
        return false;
    }
    if (tempRsource->data.assignedTaskID == -1){
        tempTask->data.assignedResourceID = resourceID;
        tempRsource->data.assignedTaskID = tempTask->data.taskID;
        printf("Resource %d allocated to task %d successfully.\n", resourceID, taskID);
    } else {
        printf("Resource Already Allocated to Task with ID %d\n", tempRsource->data.assignedTaskID);
        return false;
    }
    
    return true;
}

bool saveTasksToFile(Task* taskHead, FILE* fptr) {
     if (taskHead ==NULL || fptr == NULL) {
        printf("\nError :  Null pointer");
        return false;
    }
    
    Task* current = taskHead ;
    while (current != NULL ) {
        
        fwrite(&(current->data), sizeof(TaskData), 1, fptr);
        current = current ->next;
    }
    fclose(fptr);
    return true;
}


bool loadTasksFromFile(Task** taskHead, FILE* fptr) {

    TaskData newData;
    Task * tempTask = *taskHead;

    if (fptr == NULL || taskHead == NULL) {
        printf("Error: Pointer is Null \n");
        return false;
    }

     while (fread (&newData, sizeof(TaskData), 1, fptr)) {
        Task * new_Task = (Task *) malloc(sizeof(Task));

        new_Task->data = newData;
        new_Task->next = NULL;

        if(*taskHead == NULL)    
        {
            *taskHead = new_Task;
            tempTask = *taskHead;
        }
        else
        {
            tempTask->next = new_Task;
            tempTask = tempTask->next;
        }

    }
    fclose(fptr);
    if (tempTask == NULL) {
        printf("Error: No tasks loaded from file.\n");
        return false;
    }
    return true;

}
