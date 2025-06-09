
#include "task.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Initialize task list
// void initTaskList(struct TaskList* list) {
//     list->head = list->tail = NULL;
//     list->count = 0;
// }

// // Free all tasks in list
// void freeTaskList(struct TaskList* list) {
//     struct Task* current = list->head;
//     while (current) {
//         struct Task* next = current->next;
//         free(current);
//         current = next;
//     }
//     list->head = list->tail = NULL;
//     list->count = 0;
// }

// Create new task
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

// Add task to list (O(1) operation)
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
    } else {
        Task* temp = *taskHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newTask;
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
    if (tempTask != NULL) {
        tempTask->data.dependencyTaskID = dependencyID;
        printf("Dependency set.\n");
    } else {
        printf("Task not found.\n");
    }
    return 0;
}

// Delete task from list
// bool deleteTask(struct TaskList* list, int taskID) {
//     if (!list || !list->head) return false;

//     struct Task *current = list->head, *prev = NULL;
    
//     // Find task to delete
//     while (current && current->taskID != taskID) {
//         prev = current;
//         current = current->next;
//     }

//     if (!current) return false; // Not found

//     // Update list pointers
//     if (current == list->head) list->head = current->next;
//     if (current == list->tail) list->tail = prev;
//     if (prev) prev->next = current->next;

//     free(current);
//     list->count--;
//     return true;
// }

// Print task details
void printTask( Task* task) {
    if (!task) return;

    const char* statusStr[] = {"Pending", "In Progress", "Completed", "Blocked"};
    
    printf("\nTask ID: %d\n", task->data.taskID);
    printf("Name: %s\n", task->data.name);
    printf("Priority: %d\n", task->data.priority);
    printf("Deadline: %s\n", task->data.deadline);
    printf("Status: %s\n", statusStr[task->data.status]);
    printf("Assigned User: %d\n", task->data.assignedUserID);
    printf("Assigned Resource: %d\n", task->data.assignedResourceID);
    printf("Depends On: %d\n", task->data.dependencyTaskID);
}

// Print all tasks
void viewTasks(Task* task) {
    if (!task) return;

    printf("\n=== TASK LIST ===\n");
    while (task) {
        printTask(task);
        task = task->next;
    }
    printf("=== END OF LIST ===\n");
}

// Assign user to task
int assignTaskToUser(Task *taskHead, User *userHead) {
    Task *tempTask = taskHead;
    User *tempUser = userHead;
    // Checking if task and user lists exist
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

    // Find the task
    while (tempTask != NULL && tempTask->data.taskID != taskID) {
        tempTask = tempTask->next;
    }
    if (tempTask == NULL) {
        printf("Error: Task with ID %d not found.\n", taskID);
        return 0;
    }
    // Find the user
    while (tempUser != NULL && tempUser->data.userID != userID) {
        tempUser = tempUser->next;
    }
    if (tempUser == NULL) {
        printf("Error: User with ID %d not found.\n", userID);
        return 0;
    }
    
    tempTask->data.assignedUserID = userID;
    tempTask->data.status = IN_PROGRESS; 
    tempUser->data.tasksAssigned++;
    printf("User %d assigned to task %d successfully.\n", userID, taskID);
    return 1;
}


// Assign resource to task
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
    if (tempRsource->data.assignedTaskID==-1){
        tempTask->data.assignedResourceID = resourceID;
        tempRsource->data.assignedTaskID = tempTask->data.taskID;
        printf("Resource %d allocated to task %d successfully.\n", resourceID, taskID);
    } else {
        printf("Resource Already Allocated to Task with ID %d/n", resourceHead->data.assignedTaskID);
        return false;
    }
    
    return true;
}



// // Check if task can be assigned
// bool canAssignTask(Task* task) {
//     return task && 
//            task->data.assignedResourceID != -1 && 
//            task->data.dependencyTaskID == -1;
// }

// // Check if task is complete
// bool isTaskComplete(const struct Task* task) {
//     return task && task->status == COMPLETED;
// }

// // Save tasks to file
// bool saveTasksToFile(const struct TaskList* list, const char* filename) {
//     if (!list || !filename) return false;

//     FILE* file = fopen(filename, "w");
//     if (!file) return false;

//     struct Task* current = list->head;
//     while (current) {
//         fprintf(file, "%d,%s,%d,%s,%d,%d,%d,%d\n",
//                 current->taskID,
//                 current->name,
//                 current->priority,
//                 current->deadline,
//                 current->assignedUserID,
//                 current->assignedResourceID,
//                 current->dependencyTaskID,
//                 current->status);
//         current = current->next;
//     }

//     fclose(file);
//     return true;
// }

// // Load tasks from file
// bool loadTasksFromFile(struct TaskList* list, const char* filename) {
//     if (!list || !filename) return false;

//     FILE* file = fopen(filename, "r");
//     if (!file) return false;

//     char line[256];
//     while (fgets(line, sizeof(line), file)) {
//         struct Task task;
//         int status;
//         if (sscanf(line, "%d,%99[^,],%d,%10[^,],%d,%d,%d,%d",
//                    &task.taskID,
//                    task.name,
//                    &task.priority,
//                    task.deadline,
//                    &task.assignedUserID,
//                    &task.assignedResourceID,
//                    &task.dependencyTaskID,
//                    &status) == 8) {
//             task.status = (TaskStatus)status;
//             struct Task* newTask = createTask(task.taskID, task.name, task.priority, task.deadline);
//             if (newTask) {
//                 newTask->assignedUserID = task.assignedUserID;
//                 newTask->assignedResourceID = task.assignedResourceID;
//                 newTask->dependencyTaskID = task.dependencyTaskID;
//                 newTask->status = task.status;
//                 addTask(list, newTask);
//             }
//         }
//     }

//     fclose(file);
//     return true;
// }

// int setTaskDependency(struct Task* taskHead, int taskID, int dependencyID) {
//     struct Task* task = taskHead;
//     while (task != NULL && task->taskID != taskID)
//         task = task->next;

//     if (task == NULL)
//         return 0; // Task not found

//     struct Task* dependency = taskHead;
//     while (dependency != NULL && dependency->taskID != dependencyID)
//         dependency = dependency->next;

//     if (dependency == NULL)
//         return 0; // Dependency task not found

//     task->dependencyTaskID = dependency;
//     return 1; // Success
// }
