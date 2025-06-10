#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For colors and Sleep()

#include "task.h"
#include "user.h"
#include "resource.h"

// Set console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Simple loading animation
void loading() {
    printf("\nLoading");
    for (int i = 0; i < 5; i++) {
        Sleep(300);
        printf(".");
    }
    printf("\n");
    Sleep(500);
}

// Fancy menu display
void displayMenu() {
    
    setColor(11); // Cyan

    printf("\t\t\t\t ============================================\n");
    printf("    \t\t\t\t |    TASK & RESOURCE MANAGEMENT SYSTEM     |\n");
    printf("\t\t\t\t ============================================ \n");

    setColor(14); // Yellow
    printf("\t\t\t\t | 1. Add New Task                          |\n");
    printf("\t\t\t\t | 2. Add New User                          |\n");
    printf("\t\t\t\t | 3. Add New Resource                      |\n");
    printf("\t\t\t\t | 4. Assign Task to User                   |\n");
    printf("\t\t\t\t | 5. Set Task Dependency                   |\n");
    printf("\t\t\t\t | 6. Allocate Resource to Task             |\n");
    printf("\t\t\t\t | 7. View All Tasks                        |\n");
    printf("\t\t\t\t | 8. View All Users                        |\n");
    printf("\t\t\t\t | 9. View All Resources                    |\n");
    printf("\t\t\t\t | 10. Save Data to File                    |\n");
    printf("\t\t\t\t | 11. Load Data from File                  |\n");
    printf("\t\t\t\t | 12. Print and Save Task Table            |\n");
    printf("\t\t\t\t | 0. Exit                                  |\n");

    setColor(10); 
    printf("\nEnter your choice: ");
    setColor(7);
}
// void printAndSaveTaskTable(struct TaskList* taskList, struct UserList* userList, const char* filename) {
//     FILE* file = fopen(filename, "w");
//     if (!file) {
//         printf("Error opening file for writing.\n");
//         return;
//     }

//     struct Task* current = taskList->head;

//     printf("\n%-5s %-20s %-20s %-10s %-15s %-15s\n", "ID", "Task", "Assigned User", "Priority", "Resource", "Depends On");
//     printf("----------------------------------------------------------------------------------------\n");
//     fprintf(file, "%-5s %-20s %-20s %-10s %-15s %-15s\n", "ID", "Task", "Assigned User", "Priority", "Resource", "Depends On");
//     fprintf(file, "----------------------------------------------------------------------------------------\n");

//     while (current) {
//         char* userName = "Unassigned";
//         struct User* user = findUserByID(userList, current->assignedUserID);
//         if (user) {
//             userName = user->name;
//         }

//         char resourceStr[20];
//         if (current->assignedResourceID != -1)
//             sprintf(resourceStr, "%d", current->assignedResourceID);
//         else
//             strcpy(resourceStr, "None");

//         char dependencyStr[20];
//         if (current->dependencyTaskID != -1)
//             sprintf(dependencyStr, "%d", current->dependencyTaskID);
//         else
//             strcpy(dependencyStr, "None");

//         printf("%-5d %-20s %-20s %-10d %-15s %-15s\n",
//                current->taskID,
//                current->name,
//                userName,
//                current->priority,
//                resourceStr,
//                dependencyStr);

//         fprintf(file, "%-5d %-20s %-20s %-10d %-15s %-15s\n",
//                 current->taskID,
//                 current->name,
//                 userName,
//                 current->priority,
//                 resourceStr,
//                 dependencyStr);

//         current = current->next;
//     }

//     fclose(file);
//     printf("\nTask table saved to %s successfully.\n", filename);
// }


int main() {
    int choice;

    // Initialize your lists
    Task *taskHead = NULL;
    User *userHead = NULL;
    Resource *resourceHead = NULL;
    loading(); // Display loading animation once

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
    case 1: {
        addTask(&taskHead);
        break;
    }

    case 2:
        addUser(&userHead);
        break;

    case 3: {
        addResource(&resourceHead);
        break;
    }

    case 4: {
        if (assignTaskToUser(taskHead, userHead)) {
            printf("User assigned to task.\n");
        } else {
            printf("Failed to assign user.\n");
        }
        break;
    }

    case 5: {
        setTaskDependency(taskHead);
        break;
    }

    case 6: {

        allocateResourceToTask(taskHead,resourceHead);
        break;
    }

    case 7:
        viewTasks(taskHead);
         break;

    case 8:
        printUsers(userHead);
        break;

    case 9:
        viewResources(resourceHead);
        break;

    case 10: {
        FILE* fptrTask = fopen("tasks.txt", "wb");
        if (fptrTask == NULL) {
            printf("\nCannot open file for saving Tasks!!\n\n");
            break;
        }
        bool t = saveTasksToFile(taskHead, fptrTask);
        FILE* fptrUser = fopen("users.txt", "wb");
        if (fptrUser == NULL) {
            printf("\nCannot open file for saving Users!!\n\n");
            break;
        }
        bool u = saveUsersToFile(userHead, fptrUser);
        FILE* fptrResource = fopen("resources.txt", "wb");
        if (fptrResource == NULL) {
            printf("\nCannot open file for saving Resources!!\n\n");
            break;
        }
        bool r = saveResourcesToFile(resourceHead, fptrResource);

        if (t && u && r)
            printf("All data saved successfully.\n");
        else
            printf("Some data failed to save.\n");
        break;
    }

    case 11: {

        FILE* fptrTask = fopen("tasks.txt", "rb");
        if (fptrTask == NULL)
            {
                printf("\nCannot open file for loading Tasks!!\n\n");
                break;
            }
        bool t = loadTasksFromFile(&taskHead, fptrTask);

        FILE * fptrUser = fopen("users.txt", "rb");
        if (fptrUser == NULL)
            {
                printf("\nCannot open file for loading Users!!\n\n");
                break;
            }
       bool u = loadUsersFromFile(&userHead, fptrUser);

        FILE *fptrResource = fopen("resources.txt", "rb");
        if (fptrResource == NULL)
            {
                printf("\nCannot open file for loading Resources!!\n\n");
                break;
            }
        bool r = loadResourcesFromFile(&resourceHead, fptrResource);

         if (t /*&& u && r*/)
            printf("All data loaded successfully.\n");
        else
            printf("Some data failed to load.\n");
        break;
    }
    // case 12: {
    //     printAndSaveTaskTable(&taskHead, &userHead, "task_table.txt");
    //     break;
    // }

    case 0:
        setColor(10);
        printf("\n\t\t\t\tExiting... Thank you!\n");
        setColor(7);
        break;

    default:
        setColor(12);
        printf("\t\t\t\tInvalid choice! Please try again.\n");
        setColor(7);
        Sleep(1000);
}

    } while (choice != 0);

    return 0;
}
