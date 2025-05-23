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

        switch (choice) {
    case 1: {
        int id, priority;
        char name[100], deadline[11];
        printf("Enter Task ID: ");
        scanf("%d", &id);
        printf("Enter Task Name: ");
        scanf(" %[^\n]", name);
        printf("Enter Priority (1-10): ");
        scanf("%d", &priority);
        printf("Enter Deadline (YYYY-MM-DD): ");
        scanf("%s", deadline);
        struct Task* newTask = createTask(id, name, priority, deadline);
        if (addTask(&taskList, newTask)) {
            printf("Task added successfully.\n");
        } else {
            printf("Failed to add task.\n");
        }
        break;
    }

    case 2:
        addUser(&userList);
        break;

    case 3: {
        int resourceID;
        char name[100];
        printf("Enter Resource ID: ");
        scanf("%d", &resourceID);
        printf("Enter Resource Name: ");
        scanf(" %[^\n]", name);

        struct Resource* newResource = createResource(resourceID, name);
        if (newResource != NULL) {
            addResource(&resourceList, newResource);
            printf("Resource added successfully.\n");
        } else {
            printf("Failed to create resource.\n");
        }
        break;
    }

    case 4: {
        int taskID, userID;
        printf("Enter Task ID: ");
        scanf("%d", &taskID);
        printf("Enter User ID: ");
        scanf("%d", &userID);
        if (assignUserToTask(&taskList, taskID, userID)) {
            printf("User assigned to task.\n");
        } else {
            printf("Failed to assign user.\n");
        }
        break;
    }

    case 5: {
        int taskID, dependencyID;
        printf("Enter Task ID: ");
        scanf("%d", &taskID);
        printf("Enter Dependency Task ID: ");
        scanf("%d", &dependencyID);
        struct Task* task = findTask(&taskList, taskID);
        if (task != NULL) {
            task->dependencyTaskID = dependencyID;
            printf("Dependency set.\n");
        } else {
            printf("Task not found.\n");
        }
        break;
    }

    case 6: {
        int resourceID, taskID;
        printf("Enter Resource ID: ");
        scanf("%d", &resourceID);
        printf("Enter Task ID to allocate: ");
        scanf("%d", &taskID);
        allocateResourceToTask(&resourceList, resourceID, taskID);
        break;
    }

    case 7:
        printAllTasks(&taskList);
        break;

    case 8:
        viewUsers(&userList);
        break;

    case 9:
        viewResources(resourceList);
        break;

    case 10: {
        bool t = saveTasksToFile(&taskList, "tasks.txt");
        bool u = saveUsersToFile(&userList, "users.txt");
        bool r = saveResourcesToFile(&resourceList, "resources.txt");

        if (t && u && r)
            printf("All data saved successfully.\n");
        else
            printf("Some data failed to save.\n");
        break;
    }

    case 11: {
        bool t = loadTasksFromFile(&taskList, "tasks.txt");
        bool u = loadUsersFromFile(&userList, "users.txt");
        bool r = loadResourcesFromFile(&resourceList, "resources.txt");

        if (t && u && r)
            printf("All data loaded successfully.\n");
        else
            printf("Some data failed to load.\n");
        break;
    }

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
