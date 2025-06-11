#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"

void inputResourceData(Resource* newResource) {
    
    setColor(11);
    printf("\n+++ New Resource +++\n");
    setColor( 14);

    printf("ID: ");
    scanf("%d", &newResource->data.resourceID);

    printf("Name: ");
    scanf(" %[^\n]", newResource->data.name);
    newResource->data.assignedTaskID = -1;
}

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


void viewResources(  Resource * resourceHead) {
      Resource* tempResource = resourceHead;
    if (tempResource == NULL) {
         setColor(12);
        printf("No resources available.\n");
        setColor( 14);
        return;
    }
    setColor(10);
    printf("\n=== RESOURCES LIST ===\n");
    setColor( 14);
    printf("----------------------------------------\n");

    while (tempResource != NULL) {
        printf("Resource Name: %s\n", tempResource->data.name);
        printf("Resource ID : %d\n", tempResource->data.resourceID);
        printf("Assigned Task ID: %d\n", tempResource->data.assignedTaskID);
        printf("----------------------------------------\n");
        tempResource = tempResource->next;
    }
     
}
bool saveResourcesToFile(Resource* resourceHead, FILE* fptr) {
     if (resourceHead ==NULL || fptr == NULL) {
        printf("\nError :  Null pointer");
        return false;
    }
    
    Resource* current = resourceHead ;
    while (current != NULL ) {
        
        fwrite(&(current->data), sizeof(ResourceData), 1, fptr);
        current = current ->next;
    }
    
    fclose(fptr);
     
    return true;
}
bool loadResourcesFromFile(Resource** resourceHead, FILE* fptr) {

    ResourceData newData;
    Resource * tempResource = *resourceHead;

    if (fptr == NULL || resourceHead == NULL) {
        printf("Error: Pointer is Null \n");
        return false;
    }

    while (fread (&newData, sizeof(ResourceData), 1, fptr)) {
        Resource * new_Resource = (Resource *) malloc(sizeof(Resource));

        new_Resource->data = newData;
        new_Resource->next = NULL;

        if(*resourceHead == NULL)    /// The list will be empty the first time
        {
            *resourceHead = new_Resource;
            tempResource = *resourceHead;
        }
        else
        {
            tempResource->next = new_Resource;
            tempResource = tempResource->next;
        }

    }
    fclose(fptr);
    if (tempResource == NULL) {
        printf("Error: No tasks loaded from file.\n");
        return false;
    }
     
    return true;

}

bool isResourceListEmpty(Resource *resourceHead)
{
    return (resourceHead == NULL);
}