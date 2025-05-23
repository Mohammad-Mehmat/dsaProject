# pragma once
#include <stdbool.h>
struct Resource {
    int resourceID;
    char name[100];
    int assignedTaskID;
    struct Resource* next;
} ;

 struct ResourceList {
   struct Resource* head;
};

// Resource-related function prototypes
struct Resource* createResource(int resourceID, char name[]);
void addResource(struct ResourceList* list, struct Resource* newResource);
void allocateResourceToTask(struct ResourceList* list, int resourceID, int taskID);
void viewResources(struct ResourceList list);
bool saveResourcesToFile(struct ResourceList* list, const char* filename);
bool loadResourcesFromFile(struct ResourceList* list, const char* filename);