#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "list.h"
#include "subject.h"
#include "student.h"
#include <stdbool.h>
#include <ctype.h>

// int studentNum;
// do{
//     puts("How many students do you want to register?");
//     size_t len;
//     studentNum = GetInt(&len);
//     if((studentNum > 0) && len != 0) break;
// }while(true);
// puts("#####################################");
// for(int i = 0; i < studentNum; ++i){
//     Student student = StudentPromptAndCreate(&database.IDs);
//     ListAdd(&database.students, &student);
// }

// puts("#####################################");
// puts("***Debugging Students***");
// for(int i = 0; i < database.students.count; ++i){
//     StudentDebug(ListGet(&database.students, i));
// }
// StudentsDestroy(&database.students);

DataBase DataBaseCreate(){
    DataBase database;
    database.students = ListCreate(sizeof(Student));
    database.IDs = ListCreate(sizeof(int));
    return database;
}

int CommandToInt(const char* command){
    if(strcmp(command, "list") == 0){
        return 0;
    }else if(strcmp(command, "get") == 0){
        return 1;
    }else if(strcmp(command, "add") == 0){
        return 2;
    }else if(strcmp(command, "delete") == 0){
        return 3;
    }else if(strcmp(command, "edit") == 0){
        return 4;
    }else if(strcmp(command, "quit") == 0){
        return 5;
    }else{
        return -1;
    }
}

int main(){
    puts("Starting program...");

    DataBase database = DataBaseCreate();

    char* command = NULL;
    size_t capacity;
    puts("Please enter a command: ");
    puts("->list");
    puts("->get");
    puts("->add");
    puts("->delete");
    puts("->edit");
    puts("->quit");

    do{
        printf("\n> ");
        size_t len = improved_getline(&command, &capacity);
        int choice = CommandToInt(command);

        switch (choice){
        case 0:
            if(!StudentsList(&database.students)){
                puts("No students in database.");
            }
            break;
        case 1:
            int enteredID = 0;
            do{
                puts("Enter the student's ID: ");
                size_t len;
                enteredID = GetInt(&len);
                if((enteredID > 0) && len == 3) break;
            }while(true);    
            int gottenIndex = -1;
            Student *gottenStudent = StudentGet(&database.students, enteredID, &gottenIndex);
            if(!gottenStudent){
                printf("Student with ID %d does not exist.\n", gottenStudent);
            }else{
                puts("");
                StudentDebug(gottenStudent);
            }
            break;
        case 2:
            puts("");
            Student addedStudent = StudentPromptAndCreate(&database.IDs);
            ListAdd(&database.students, &addedStudent);
            break;
        case 3:
            puts("");
            do{
                puts("Enter the student's ID: ");
                size_t len;
                enteredID = GetInt(&len);
                if((enteredID > 0) && len == 3) break;
            }while(true);
            int removedIndex = -1;    
            Student* removedStudent = StudentGet(&database.students, enteredID, &removedIndex);
            if(!removedStudent){
                printf("Student with ID %d does not exist.\n", enteredID);
            }else{

                size_t len;
                char* line = NULL;
                do {
                    puts("Are you sure? (Y/N)");
                    len = improved_getline(&line, &capacity);
                    if (len == 1 && line[0] == 'Y'){
                        ListRemoveAt(&database.students, removedIndex);   
                        printf("Student with ID %d has been removed.\n", removedStudent->ID);
                        break;
                    }else if(len == 1 && line[0] == 'N'){
                        break;
                    }else{
                        continue;
                    }
                } while (true); 
            }
            break;
        case 4:
            break;
        case 5:
            puts("Quitting...");
            return 0;
        default:
            puts("Please enter a valid command.");
            break;
        }
    }while(true);

    return 1;
}
