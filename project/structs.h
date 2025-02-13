#pragma once
#include "list.h"

typedef struct {
    int ID;
    char* firstName;
    char* lastName;
    int overallGrade;
    List subjects;
} Student;

typedef enum {
    ANALYSIS_1,
    ALGEBRA_1,
    DIGITAL_ELECTRONICS,
    GAME_DESIGN,
    NUMBER_OF_SUBJECTS
} Subject;
