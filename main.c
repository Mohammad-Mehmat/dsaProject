#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 

#include "task.h"
#include "user.h"
#include "resource.h"

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void ClearScreen(){
    system("cls");
}
void loading() {
    printf("\nLoading");
    for (int i = 0; i < 5; i++) {
        Sleep(300);
        printf(".");
    }
    printf("\n");
    Sleep(500);
}

void displayMenu() {
    
    setColor(11); 

    printf("\t\t\t\t ============================================\n");
    printf("    \t\t\t\t |    TASK & RESOURCE MANAGEMENT SYSTEM     |\n");
    printf("\t\t\t\t ============================================ \n");

    setColor(14); 
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
    printf("\t\t\t\t | 12. Mark Task as Completed               |\n");
    printf("\t\t\t\t | 13. Clear All Previous Outputs           |\n");
    printf("\t\t\t\t | 0. Exit                                  |\n");

    setColor(10); 
    printf("\nEnter your choice: ");
    setColor(7);
}

int main() {
    int choice;

    Task *taskHead = NULL;
    User *userHead = NULL;
    Resource *resourceHead = NULL;
    loading(); 

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

         if (t && u && r)
            printf("All data loaded successfully.\n");
        else
            printf("Some data failed to load.\n");
        break;
    }
    case 12: {
        TaskCompleted(taskHead, resourceHead, userHead);
        break;
    }
    case 13:
        ClearScreen();
        break;
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
