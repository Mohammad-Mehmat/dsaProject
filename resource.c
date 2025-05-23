#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"

// Create a new resource
struct Resource* createResource(int resourceID, char name[]) {
    struct Resource* newResource = (struct Resource*)malloc(sizeof(struct Resource));
    if (newResource == NULL) return NULL;

    newResource->resourceID = resourceID;
    strcpy(newResource->name, name);
    newResource->assignedTaskID = -1; // -1 means not assigned
    newResource->next = NULL;

    return newResource;
}

// Add a resource to the list
void addResource(struct ResourceList* list, struct Resource* newResource) {
    if (list->head == NULL) {
        list->head = newResource;
    } else {
        struct Resource* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newResource;
    }
    printf("Resource added successfully.\n");
}

// Allocate resource to a task
void allocateResourceToTask(struct ResourceList* list, int resourceID, int taskID) {
    struct Resource* temp = list->head;
    while (temp != NULL) {
        if (temp->resourceID == resourceID) {
            temp->assignedTaskID = taskID;
            printf("Resource allocated to Task ID %d successfully.\n", taskID);
            return;
        }
        temp = temp->next;
    }
    printf("Resource with ID %d not found.\n", resourceID);
}

// View all resources
void viewResources(struct ResourceList list) {
    struct Resource* temp = list.head;
    if (temp == NULL) {
        printf("No resources available.\n");
        return;
    }

    printf("\nAvailable Resources:\n");
    while (temp != NULL) {
        printf("Resource ID: %d\n", temp->resourceID);
        printf("Name: %s\n", temp->name);
        printf("Assigned Task ID: %d\n", temp->assignedTaskID);
        printf("--------------------------\n");
        temp = temp->next;
    }
}

bool loadResourcesFromFile(struct ResourceList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file for loading.\n");
        return false;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int resourceID, assignedTaskID;
        char name[100];

        if (sscanf(line, "%d,%99[^,],%d", &resourceID, name, &assignedTaskID) == 3) {
            struct Resource* res = createResource(resourceID, name);
            if (res != NULL) {
                res->assignedTaskID = assignedTaskID;
                addResource(list, res);
            }
        }
    }

    fclose(file);
    printf("Resources loaded from file successfully.\n");
    return true;
}


bool saveResourcesToFile(struct ResourceList* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for saving.\n");
        return false;
    }

    struct Resource* current = list->head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%d\n", current->resourceID, current->name, current->assignedTaskID);
        current = current->next;
    }

    fclose(file);
    printf("Resources saved to file successfully.\n");
    return true;
}
