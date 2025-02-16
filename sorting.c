#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "sorting.h"

bool SortSelection(int* T, int size){
    for(int i = 0; i < size; ++i){
        for(int j = i; j < size; ++j){
            if(T[i] > T[j]){
                int temp = T[i];
                T[i] = T[j];
                T[j] = temp;
            }
        }
    }
}
