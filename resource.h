# pragma once
#include <stdbool.h>
#include <stdio.h>
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
bool saveResourcesToFile(Resource* resourceHead, FILE *fptr);
bool loadResourcesFromFile(Resource** resourceHead, FILE *fptr);
bool isResourceListEmpty(Resource *resourceHead);

extern void setColor(int color);