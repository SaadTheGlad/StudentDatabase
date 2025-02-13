#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <string.h>
#include <stdbool.h>

List ListCreate(size_t elementSize){
    List list;

    list.capacity = 16;
    list.elementSize = elementSize;
    list.elements = malloc(list.capacity * elementSize);  
    list.count = 0;

    return list;
}

//Returns a void pointer to that element and null if it doesn't exist
void* ListGet(const List* list, int i){
    if(i > (list->count - 1) || i < 0) return NULL;

    size_t increment = i * list->elementSize;
    return list->elements + increment;
}

bool ListRemoveAt(List* list, int index){
    if(ListGet(list, index) == NULL){
        return false;
    }

    size_t size = ((list->count) - (index + 1)) * list->elementSize;
    void* destinationP = ListGet(list, index);
    void* sourceP = ListGet(list, index + 1);
    memmove(destinationP, sourceP, size);

    (list->count)--;
    return true;
}

bool ListAdd(List* list, void* element){
    if(list->elements == NULL){
        return false;
    }

    if(list->count > list->capacity - 1){
        list->capacity *= 2;
        list->elements = realloc(list->elements, list->capacity * list->elementSize);
        if(list->elements == NULL) return false;
    }

    size_t increment = list->count++ * list->elementSize;
    memcpy(list->elements + increment, element, list->elementSize);
    return true;
}

void ListDestroy(List* list){
    free(list->elements);
}