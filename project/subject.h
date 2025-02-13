#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "student.h"

const char* GetSubjectName(Subject subject);

int SubjectAdd(Student *student, Subject* subject);

void SubjectsPrompt();
