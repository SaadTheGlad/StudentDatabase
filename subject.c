#include <stdlib.h>
#include <stdio.h>
#include "subject.h"
#include "student.h"

const char* GetSubjectName(Subject subject) 
{
    switch (subject) {
    case ANALYSIS_1: return "Analysis 1";
    case ALGEBRA_1: return "Algebra 1";
    case DIGITAL_ELECTRONICS: return "Digital Electronics";
    case GAME_DESIGN: return "Game Design";
    default: return "ERROR";
    }
}

//Returns 0 if the subject has already been added
int SubjectAdd(Student* student, Subject* subject){
    for(int i = 0; i < student->subjects.count; ++i){
        int item = *(int*)ListGet(&student->subjects, i);
        if(item == *subject){
            return 0;
        }
    }

    ListAdd(&student->subjects, subject);
    return 1;
}

void SubjectsPrompt()
{
    puts("Add one of the following subjects, or enter N for none/stop: ");
    for(int i = 0; i < NUMBER_OF_SUBJECTS; ++i){
        printf("Enter %d for %s: \n", i + 1, GetSubjectName(i));
    }
}

