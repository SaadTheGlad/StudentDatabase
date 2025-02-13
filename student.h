#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "structs.h"
#include "subject.h"

Student StudentCreate(int ID, const char* firstName, const char* lastName,
    int overallGrade, const Subject *subjects, int subjectCount);

void StudentDestroy(Student *student);

void StudentDebug(const Student* student);

Student StudentPromptAndCreate();

void StudentsDestroy(List* students);
