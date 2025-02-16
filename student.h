#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "structs.h"
#include "subject.h"
#include "sorting.h"

Student StudentCreate(int ID, const char* firstName, const char* lastName,
    float overallGrade, const Subject *subjects, int subjectCount);

void StudentDestroy(Student* student);

Student* StudentGet(List* students, int ID, int* index);

bool StudentsList(const List* list);

bool StudentEditGrade(Student* student, float newGrade);

bool StudentDebug(const Student* student);

Student StudentPromptAndCreate(List* IDList);

void StudentSortID(List* students, PredicateInt predicate);

void StudentSortAlphabetical(List* students, PredicateInt predicate);

void StudentsDestroy(List* students);
