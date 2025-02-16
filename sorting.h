#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool SortSelection(int* T, int size);

typedef bool (*PredicateInt)(int, int);
