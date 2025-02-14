#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    void* elements;
    size_t elementSize;
    size_t count;
    size_t capacity;
}List;

List ListCreate(size_t elementSize);

bool ListAdd(List* list, void* element);

bool ListRemoveAt(List* list, int i);

#define ListRemove(list, elementVal, type){ \
    for(int i = 0; i < (list)->count; ++i){ \
        type elementToTest = *(type*)(ListGet((list), i)); \
        if(elementToTest == elementVal){ \
            ListRemoveAt(list, i); \
        } \
    } \
     \
}

void* ListGet(const List* list, int i);

void ListDestroy(List* list);

#define ListDebug(list, type, formatSpecifier)\
{\
    char fullMessage[100]; \
    strcpy(fullMessage, "Element %d is "); \
    strcat(fullMessage, formatSpecifier); \
    strcat(fullMessage, ".\n");\
    \
    for(int i = 0; i < (list)->count; ++i){ \
        size_t increment = i * (list)->elementSize; \
        printf(fullMessage, i, *(type*)((list)->elements + increment)); \
        printf("Pointer: %p.\n", (list)->elements + increment); \
        \
    } \
} 

#define ListFind(list, element, type, elementVal){ \
    bool hasFound = false; \
    for(int i = 0; i < (list)->count; ++i){ \
        element = ListGet((list), i); \
        type elementToTest = *(type*)(element); \
        if(elementToTest == elementVal){ \
            hasFound = true; \
            break; \
        } \
    } \
    if(!hasFound) element = NULL; \
}



