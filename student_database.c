#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "list.h"
#include "subject.h"
#include "student.h"
#include <stdbool.h>
#include <ctype.h>

DataBase DataBaseCreate(){
    DataBase database;
    database.students = ListCreate(sizeof(Student));
    database.IDs = ListCreate(sizeof(int));
    return database;
}

int main(){
    puts("Starting program...");

    DataBase database = DataBaseCreate();

    int studentNum;
    do{
        puts("How many students do you want to register?");
        size_t len;
        studentNum = GetInt(&len);
        if((studentNum > 0) && len != 0) break;
    }while(true);
    puts("#####################################");

    for(int i = 0; i < studentNum; ++i){
        Student student = StudentPromptAndCreate(&database.IDs);
        ListAdd(&database.students, &student);
    }
    
    puts("#####################################");
    puts("***Debugging Students***");
    for(int i = 0; i < database.students.count; ++i){
        StudentDebug(ListGet(&database.students, i));
    }

    StudentsDestroy(&database.students);

    return 0;
}
