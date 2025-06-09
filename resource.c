#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"

// Create a new resource
void inputResourceData(Resource* newResource) {

    printf("Enter Resource ID: ");
    scanf("%d", &newResource->data.resourceID);
    printf("Enter Resource Name: ");
    scanf(" %[^\n]", newResource->data.name);
    newResource->data.assignedTaskID = -1; // -1 means not assigned
   
}

// Add a resource to the list
void addResource( Resource** resourceHead) {
    Resource* newResource = (Resource*)malloc(sizeof(Resource));
    if (newResource == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    inputResourceData(newResource);
    newResource->next = NULL;

    if (isResourceListEmpty(*resourceHead)) {
        *resourceHead = newResource;
    } else {
        Resource* tempResource = *resourceHead;
        while (tempResource->next != NULL)
            tempResource = tempResource->next;
        tempResource->next = newResource;
    }
}


//View all resources
void viewResources(  Resource * resourceHead) {
      Resource* tempResource = resourceHead;
    if (tempResource == NULL) {
        printf("No resources available.\n");
        return;
    }

    printf("\nAvailable Resources:\n");
    while (tempResource != NULL) {
        printf("Resource ID: %d\n", tempResource->data.resourceID);
        printf("Name: %s\n", tempResource->data.name);
        printf("Assigned Task ID: %d\n", tempResource->data.assignedTaskID);
        printf("--------------------------\n");
        tempResource = tempResource->next;
    }
}

// bool loadResourcesFromFile(  Resource* list, const char* filename) {
//     FILE* file = fopen(filename, "r");
//     if (file == NULL) {
//         printf("Failed to open file for loading.\n");
//         return false;
//     }

//     char line[256];
//     while (fgets(line, sizeof(line), file)) {
//         int resourceID, assignedTaskID;
//         char name[100];

//         if (sscanf(line, "%d,%99[^,],%d", &resourceID, name, &assignedTaskID) == 3) {
//               Resource* res = createResource(resourceID, name);
//             if (res != NULL) {
//                 res->assignedTaskID = assignedTaskID;
//                 addResource(list, res);
//             }
//         }
//     }

//     fclose(file);
//     printf("Resources loaded from file successfully.\n");
//     return true;
// }


// bool saveResourcesToFile(  Resource* list, const char* filename) {
//     FILE* file = fopen(filename, "w");
//     if (file == NULL) {
//         printf("Failed to open file for saving.\n");
//         return false;
//     }

//       Resource* current = list->head;
//     while (current != NULL) {
//         fprintf(file, "%d,%s,%d\n", current->resourceID, current->name, current->assignedTaskID);
//         current = current->next;
//     }

//     fclose(file);
//     printf("Resources saved to file successfully.\n");
//     return true;
// }

bool isResourceListEmpty(Resource *resourceHead)
{
    return (resourceHead == NULL);
}