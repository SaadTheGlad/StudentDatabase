#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helperfunctions.h"
#include <stdbool.h>
#include <ctype.h>

typedef enum{

    ANALYSIS_1,
    ALGEBRA_1,
    DIGITAL_ELECTRONICS,
    GAME_DESIGN,
    NUMBER_OF_SUBJECTS,

}Subject;

typedef struct{

    char* ID;
    char* firstName;
    char* lastName;
    int overallGrade;
    Subject *subjects;
    int subjectCount;

}Student;

char* GetSubjectName(int ID){

    switch(ID){

        case 0:
        return "Analysis 1";
        break;
        case 1:
        return "Algebra 1";
        case 2:
        return "Digital Electronics";
        case 3:
        return "Game Design";
        default:
        return "ERROR";
    }
}

Student CreateStudent(char* ID, char* firstName, char* lastName, int overallGrade, 
Subject *subjects, int subjectCount){

    Student student;
    student.ID = ID;

    student.firstName = strdup(firstName);
    student.lastName = strdup(lastName);

    student.overallGrade = overallGrade;
    student.subjectCount = subjectCount;

    student.subjects = malloc(subjectCount * sizeof(Subject));
    student.subjects = memcpy(student.subjects, subjects, subjectCount * sizeof(Subject));

    return student;
}

void DestroyStudent(Student *student){

    free(student->ID);
    free(student->firstName);
    free(student->lastName);
    free(student->subjects);
}

void DebugStudent(Student student){

    puts("******************************");
    printf(">Student ID: %s\n>First name: %s\n>Last name: %s\n>Overall grade: %d\n", student.ID, 
    student.firstName, student.lastName, student.overallGrade);
    
    printf(">Number of subjects: %d\n", student.subjectCount);

    for(int i = 0; i < student.subjectCount; i++){
        printf("->%s\n", GetSubjectName(student.subjects[i]));
    }
    puts("");
}

void AddSubject(Student *student, Subject subject){

    if(subject >= NUMBER_OF_SUBJECTS || subject < 0){
        puts("Subject does not exist.");
        return;
    }

    for(int i = 0; i < student->subjectCount; ++i){
        if(student->subjects[i] == subject){
            puts("Subject already added.");
            return;
        }
    }

    student->subjects[student->subjectCount] = subject;
    student->subjectCount++;
    student->subjects = realloc(student->subjects, (student->subjectCount + 1) * sizeof(Subject));
    printf("Added %s.\n", GetSubjectName(subject));
}

void PromptSubjects()
{
    puts("\nAdd one of the following subjects, or enter N for none/stop: ");
    for(int i = 0; i < NUMBER_OF_SUBJECTS; ++i){
        printf("Enter %d for %s: \n", i + 1, GetSubjectName(i));
    }

}

Student PromptAndCreateStudent(){

    Student student;
    int IDlength = 3;

    do{
        printf("Enter the ID (must be %d digits long): \n", IDlength);
        student.ID = getline();

        if(student.ID != NULL && (student.ID) && strlen(student.ID) == IDlength){
            break;
        }
        else{
            free(student.ID);
        }

    }while(true);

    do{

        puts("Enter the first name: ");
        student.firstName = getline();

        if(student.firstName != NULL){
            break;
        }

    }while(true);

    do{

        puts("Enter the last name: ");
        student.lastName = getline();

        if(student.lastName != NULL){
            break;
        }

    }while(true);


    do{
        
        puts("Enter the overall grade (between 0 and 20): ");
        scanf("%d", &student.overallGrade);
        //fix this looping forever if you enter a character

    }while(student.overallGrade < 0 || student.overallGrade > 20);

    student.subjects = malloc(sizeof(Subject));
    student.subjectCount = 0;

    bool isFinished = false;
    bool isFirstPrompt = true;

    do{
        if(!isFirstPrompt)
            PromptSubjects();

        char* line;

        if(!isFirstPrompt){
        do{

            line = getline();
            if(line != NULL){
                break;
            }

            }while(true);
        }

        // int len = 0;
        // char c = getCharDeluxe(&len);
        // //this system means we can only have theoretically 10 subjects max (0-9), should fix 
        // if(len != 1 && !isFirstPrompt){
        //     puts("Please enter a valid command.");
        //     continue;
        // }

        // char* line = getline();
        // int len = strlen(line);
        // if(!isNumber(line)){
        //     puts("Please enter a valid command.");
        //     continue;
        // }
        
        char c;

        if(isFirstPrompt){
            c = -1;
        }else{
            char c = line[0];
        }

        if(isdigit(c)){

            int x = c - '0';
            AddSubject(&student, x - 1);
            isFirstPrompt = false;
        }else if(c == 'N'){

            isFinished = true;       
        }else if(c == EOF){
            //hacky flag solution but I'm losing my mind so Idgaf anymore
            isFirstPrompt = false;

        }else{
            puts("Please enter a valid command.");
            isFirstPrompt = false;
        }

    }while(!isFinished);

    return student;

}

void DestroyStudents(Student *students, int numberOfStudents){

    for(int i = 0; i < numberOfStudents; ++i){
        DestroyStudent(&students[i]);
    }
}

int main()
{
    puts("\nStarting program...");
    Student saad = PromptAndCreateStudent();

    DebugStudent(saad);
    DestroyStudent(&saad);

    return 0;
}