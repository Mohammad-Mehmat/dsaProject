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
    printf("\t\t\t\t | 0. Exit                                  |\n");

    setColor(10); 
    printf("\nEnter your choice: ");
    setColor(7);
}

int main() {
    int choice;

    // Initialize your lists
    struct TaskList taskList = {NULL};
    struct UserList userList = {NULL};
    struct ResourceList resourceList = {NULL};

    loading(); // Display loading animation once

    do {
        displayMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                // addTask(&taskList);
                break;
            case 2:
                 addUser(&userList);
                break;
            case 3:
                // addResource(&resourceList);
                break;
            case 4:
                // assignTaskToUser(&taskList, &userList);
                break;
            case 5:
                // setTaskDependency(&taskList);
                break;
            case 6:
                // allocateResourceToTask(&taskList, &resourceList);
                break;
            case 7:
                // viewAllTasks(&taskList);
                break;
            case 8:
                viewUsers(&userList);
                break;
            case 9:
                // viewAllResources(&resourceList);
                break;
            case 10:
                // saveDataToFile(&taskList, &userList, &resourceList);
                break;
            case 11:
                // loadDataFromFile(&taskList, &userList, &resourceList);
                break;
            case 0:
                setColor(10);
                printf("\n\t\t\t\tExiting... Thank you!\n");
                setColor(7);
                break;
            default:
                setColor(12); // Red
                printf("\t\t\t\tInvalid choice! Please try again.\n");
                setColor(7);
                Sleep(1000);
        }
    } while (choice != 0);

    return 0;
}
