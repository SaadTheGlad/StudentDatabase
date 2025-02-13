#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include "subject.h"
#include "util.h"
#include <string.h>

Student StudentCreate(int ID, const char* firstName, const char* lastName,
    int overallGrade, const Subject* subjects, int subjectCount) {
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
    ListDestroy(&student->subjects);
}

void StudentDebug(const Student* student){
    puts("******************************");
    printf(">Student ID: %d\n>First name: %s\n>Last name: %s\n>Overall grade: %d\n",
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
    puts("");
}

Student StudentPromptAndCreate(){
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
        if(len == ID_LENGTH){
            break;
        }        
    }while(true);

    do {
        puts("Enter the first name: ");
        if (improved_getline(&line, &capacity) > 0) break;
    } while (true);

    student.firstName = strdup(line);

    do {
        puts("Enter the last name: ");
        if (improved_getline(&line, &capacity) > 0) break;
    } while (true);

    student.lastName = strdup(line);

    do{
        puts("Enter the overall grade (between 0 and 20): ");
        size_t len;
        student.overallGrade = GetInt(&len);
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

            if (items_read > 0) {
                if (choice > NUMBER_OF_SUBJECTS || choice < 0) {

                    puts("Subject does not exist.");
                    continue;
                }
                
                Subject subjectToAdd = choice - 1;
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

void StudentsDestroy(List* students) {
    for (int i = 0; i < students->count; ++i) {
        StudentDestroy(ListGet(students, i));
    }
}


