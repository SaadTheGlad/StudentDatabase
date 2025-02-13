#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "list.h"
#include "subject.h"
#include "student.h"
#include <stdbool.h>
#include <ctype.h>

int main(){
    puts("Starting program...");

    List students = ListCreate(sizeof(Student));

    int studentNum;
    do{
        puts("How many students do you want to register?");
        size_t len;
        studentNum = GetInt(&len);
        if((studentNum > 0) && len != 0) break;
    }while(true);
    puts("#####################################");

    for(int i = 0; i < studentNum; ++i){
        Student student = StudentPromptAndCreate();
        ListAdd(&students, &student);
    }
    
    puts("#####################################");
    puts("***Debugging Students***");
    for(int i = 0; i < students.count; i++){
        StudentDebug(ListGet(&students, i));
    }

    StudentsDestroy(&students);

    return 0;
}
