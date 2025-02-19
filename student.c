#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include "subject.h"
#include "util.h"
#include <string.h>
#include <ctype.h>
#include "sorting.h"

Student StudentCreate(int ID, const char* firstName, const char* lastName,
    float overallGrade, const Subject* subjects, int subjectCount) {
    Student student;
    student.ID = ID;

    student.firstName = strdup(firstName);
    student.lastName = strdup(lastName);

    student.overallGrade = overallGrade;
    student.subjects = ListCreate(sizeof(Subject));

    return student;
}

void StudentDestroy(Student* student){
    free(student->firstName);
    free(student->lastName);
    free(student->fullName);
    ListDestroy(&student->subjects);
}

bool StudentsList(const List* list){
    if(list->count == 0){
        return false;
    }

    for(int i = 0; i < list->count; ++i){
        Student student = *(Student*)ListGet(list, i);
        printf("%d) ID: %d. Name: %s %s.\n", i + 1, student.ID, student.firstName, student.lastName);
    }

    return true;
}

Student* StudentGet(List* students, int ID, int* index){
    for(int i = 0; i < students->count; ++i){
        Student *student = (Student*)ListGet(students, i);
        if(student->ID == ID){
           *index = i; 
           return student;
        }
    }

    return NULL;
}

bool StudentDebug(const Student* student){

    printf(">Student ID: %d\n>First name: %s\n>Last name: %s\n>Overall grade: %.2f\n",
           student->ID, student->firstName, student->lastName, student->overallGrade);

    printf(">Number of subjects: %d\n", student->subjects.count);

    for(int i = 0; i < student->subjects.count; ++i){
        void* subjectP = ListGet(&(student->subjects), i);
        if(subjectP == NULL){
            break;
        }
        Subject subject = *(Subject*)subjectP;
        printf("->%s\n", GetSubjectName(subject));
    }
}

Student StudentPromptAndCreate(List* IDList){
    List subjects = ListCreate(sizeof(Subject));
    Student student;
    student.subjects = subjects;

    const int ID_LENGTH = 3;

    char* line = NULL;
    size_t capacity = 0;

    do{
        printf("Enter the ID (must be %d digits long): \n", ID_LENGTH);

        size_t len;
        student.ID = GetInt(&len);

        void* element = NULL;
        ListFind(IDList, element, int, student.ID);
        if(element != NULL){
            puts("ID already exists.");
            continue;
        }

        if(len == ID_LENGTH){
            ListAdd(IDList, &student.ID);
            break;
        }        
    }while(true);

    do {
        puts("Enter the first name: ");
        if (improved_getline(&line, &capacity) > 0) break;
    } while (true);

    student.firstName = strdup(line);
    for(int i = 0; i < strlen(student.firstName); ++i){
        student.firstName[i] = tolower(student.firstName[i]);
    }

    do {
        puts("Enter the last name: ");
        if (improved_getline(&line, &capacity) > 0) break;
    } while (true);

    student.lastName = strdup(line);
    for(int i = 0; i < strlen(student.lastName); ++i){
        student.lastName[i] = tolower(student.lastName[i]);
    }

    int totalNameLen = strlen(student.firstName) + strlen(student.lastName);
    student.fullName = malloc((totalNameLen + 1) * sizeof(char));
    memcpy(student.fullName, student.firstName, strlen(student.firstName) * sizeof(char));
    memcpy(student.fullName + strlen(student.firstName), student.lastName, strlen(student.lastName) * sizeof(char));
    student.fullName[totalNameLen] = 0;

    do{
        puts("Enter the overall grade (between 0 and 20): ");
        size_t len;
        student.overallGrade = GetFloat(&len);
        if((student.overallGrade >= 0 && student.overallGrade <= 20) && len != 0) break;
    }while(true);

    SubjectsPrompt();
    do {
        printf("Subjects: [");
        for (int i = 0; i < student.subjects.count; ++i) {
            const char* pointerName = GetSubjectName(*(int*)ListGet(&(student.subjects), i));
            printf("%s%s", pointerName, 
                i == student.subjects.count - 1 ? "" : ", ");
               
        }
        puts("]");

        size_t len = improved_getline(&line, &capacity);
        int choice;
        if (len > 0) {
            int items_read = sscanf(line, "%d", &choice);
            Subject subjectToAdd = choice - 1;

            if (items_read > 0) {
                if (subjectToAdd >= NUMBER_OF_SUBJECTS || subjectToAdd < 0) {

                    puts("Subject does not exist.");
                    continue;
                }
                
                if(SubjectAdd(&student, &subjectToAdd) == 0)
                {
                    puts("Subject already added");
                }else{
                    printf("Added %s.\n", GetSubjectName(choice - 1));
                }
                
            } else {
                if (line[0] == 'n' || line[0] == 'N') {
                    break;
                }
            }
        } else continue;
    } while (true);

    return student;
}

bool StudentEditGrade(Student* student, float newGrade){
    if(!student) return false;

    if(newGrade < 0 || newGrade > 20) return false;
    
    student->overallGrade = newGrade;
    return true;
}

void StudentsDestroy(List* students) {
    for (int i = 0; i < students->count; ++i) {
        StudentDestroy(ListGet(students, i));
    }
}

void StudentSortID(List* students, PredicateInt predicate){
    for(int i = 0; i < (students)->count; ++i){ 
        for(int j = i; j < (students)->count; ++j){ 
            int a = *(int*)ListGet(students, i);
            int b = *(int*)ListGet(students, j);
            if(predicate(a, b)){ 
                Student temp = *(Student*)ListGet(students, i);\
                *(Student*)ListGet(students, i) = *(Student*)ListGet(students, j); 
                *(Student*)ListGet(students, j) = temp; 
            } 
        } 
    } 
}

void StudentSortAlphabetical(List* students, PredicateInt predicate){
    for(int i = 0; i < (students)->count; ++i){ 
        for(int j = i; j < (students)->count; ++j){ 
            
            Student a = *(Student*)ListGet(students, i);
            Student b = *(Student*)ListGet(students, j);

            if(predicate(strcmp(a.fullName, b.fullName), 0)){ 
                Student temp = *(Student*)ListGet(students, i);\
                *(Student*)ListGet(students, i) = *(Student*)ListGet(students, j); 
                *(Student*)ListGet(students, j) = temp; 
            } 
        } 
    } 
}