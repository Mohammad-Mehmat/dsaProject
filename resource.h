# pragma once
#include <stdbool.h>

typedef struct ResourceData {
  int resourceID;
  char name[100];
  int assignedTaskID;
  struct Resource* next;
}ResourceData ;

 typedef struct Resource {
  ResourceData data;
   struct Resource* next;
}Resource;

// Resource-related function prototypes
void inputResourceData(Resource* newResource);
void addResource(Resource** resourceHead);
void viewResources(Resource *resource);
bool saveResourcesToFile(Resource* resource, const char* filename);
bool loadResourcesFromFile(Resource* resource, const char* filename);
bool isResourceListEmpty(Resource *resourceHead);
