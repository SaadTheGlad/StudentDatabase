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

int GetID(){
    int enteredID;
    do{
        puts("Enter the student's ID: ");
        size_t len;
        enteredID = GetInt(&len);
        if((enteredID > 0) && len == 3) break;
    }while(true);
    return enteredID;
}

int main(){
    puts("Starting program...");

    DataBase database = DataBaseCreate();

    char* command = NULL;
    size_t capacity;
    int enteredID = 0;
    int studentIndex = -1;
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
            //Listing students
            puts("");
            if(!StudentsList(&database.students)){
                puts("No students in database.");
            }
            break;
        case 1:
            //Getting student
            puts("");
            enteredID = GetID();    
            Student *gottenStudent = StudentGet(&database.students, enteredID, &studentIndex);
            if(!gottenStudent){
                printf("Student with ID %d does not exist.\n", enteredID);
            }else{
                puts("");
                StudentDebug(gottenStudent);
            }
            break;
        case 2:
            //Debugging student
            puts("");
            Student addedStudent = StudentPromptAndCreate(&database.IDs);
            ListAdd(&database.students, &addedStudent);
            break;
        case 3:
            //Removing student
            puts("");
            enteredID = GetID(); 
            Student* removedStudent = StudentGet(&database.students, enteredID, &studentIndex);
            if(!removedStudent){
                printf("Student with ID %d does not exist.\n", enteredID);
            }else{

                size_t len;
                char* line = NULL;
                do {
                    puts("Are you sure? (Y/N)");
                    len = improved_getline(&line, &capacity);
                    if (len == 1 && line[0] == 'Y'){
                        ListRemoveAt(&database.students, studentIndex);   
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
            //Editing student
            puts("");
            enteredID = GetID(); 
            Student *editedStudent = StudentGet(&database.students, enteredID, &studentIndex);
            if(!editedStudent){
                printf("Student with ID %d does not exist.\n", enteredID);
            }else{
                puts("What would you like to edit?");
                puts("Enter 1 for editing the overall grade");
                puts("Enter 2 for editing the subjects");
                int choiceEdit;
                while(true){
                    size_t len;
                    choiceEdit = GetInt(&len);
                    if((choiceEdit > 0) && (choiceEdit < 3)) break;
                    else puts("Please enter a valid number.");     
                }

                switch(choiceEdit){
                    case 1:
                    //editing
                    puts("");
                    puts("Enter new grade (must be between 0 and 20): ");
                    int newGrade;
                    while(true){
                        size_t len;
                        newGrade = GetInt(&len);
                        if((newGrade >= 0) && (newGrade <= 20)) break;
                        else puts("Please enter a valid number.");     
                    }
                    printf("Set grade to %d.\n", newGrade);
                    StudentEditGrade(editedStudent, newGrade);
                    break;
                    case 2:
                    puts("");
                    puts("What would you like to edit?");
                    puts("Enter 1 for adding a subject");
                    puts("Enter 2 for removing a subject");
                    int choiceEditGrade;
                    while(true){
                        size_t len;
                        choiceEditGrade = GetInt(&len);
                        if((choiceEditGrade > 0) && (choiceEditGrade < 3)) break;
                        else puts("Please enter a valid number.");     
                    }

                    switch(choiceEditGrade){
                        case 1:
                        //adding subject
                        SubjectsPrompt();
                        printf("%s %s's subjects: [", editedStudent->firstName, editedStudent->lastName);
                        for (int i = 0; i < editedStudent->subjects.count; ++i) {
                            const char* pointerName = GetSubjectName(*(int*)ListGet(&(editedStudent->subjects), i));
                            printf("%s%s", pointerName, 
                                i == editedStudent->subjects.count - 1 ? "" : ", ");
                               
                        }
                        puts("]");
                
                        char* line = NULL;
                        int choiceEditGradeAdding;
                        do{
                            size_t len = improved_getline(&line, &capacity);
                            if (len > 0) {
                                int items_read = sscanf(line, "%d", &choiceEditGradeAdding);
                    
                                if (items_read > 0) {
                                    if (choiceEditGradeAdding >= NUMBER_OF_SUBJECTS || choiceEditGradeAdding < 0) {
                    
                                        puts("Subject does not exist.");
                                        continue;
                                    }
                                    
                                    Subject subjectToAdd = choiceEditGradeAdding - 1;
                                    if(SubjectAdd(editedStudent, &subjectToAdd) == 0)
                                    {
                                        puts("Subject already added");
                                        continue;
                                    }else{
                                        printf("Added %s.\n", GetSubjectName(choiceEditGradeAdding - 1));
                                        continue;
                                    }
                                    
                                } else {
                                    if (line[0] == 'n' || line[0] == 'N') {
                                        break;
                                    }
                                    else{
                                        puts("Please enter a valid number");
                                    }
                                }

                            }else puts("Please enter a valid number");
                        }while(true);
                        break;
                        
                        case 2:
                        SubjectsPrompt();
                        //removing subject
                        printf("%s %s's subjects: [", editedStudent->firstName, editedStudent->lastName);
                        for (int i = 0; i < editedStudent->subjects.count; ++i) {
                            const char* pointerName = GetSubjectName(*(int*)ListGet(&(editedStudent->subjects), i));
                            printf("%s%s", pointerName, 
                                i == editedStudent->subjects.count - 1 ? "" : ", ");
                               
                        }
                        puts("]");
                
                        char* line2 = NULL;
                        int choiceEditGradeRemoving;
                        do{
                            size_t len = improved_getline(&line2, &capacity);
                            if (len > 0) {
                                int items_read = sscanf(line2, "%d", &choiceEditGradeRemoving);
                                Subject subjectToRemove = choiceEditGradeRemoving - 1;
                    
                                if (items_read > 0) {
                                    void* subject = NULL;
                                    ListFind(&editedStudent->subjects, subject, Subject, subjectToRemove);

                                    if (subjectToRemove >= NUMBER_OF_SUBJECTS || subjectToRemove < 0 || 
                                        subject == NULL) {
                    
                                        puts("Subject does not exist.");
                                        continue;
                                    }
                                    
                                    ListRemove(&editedStudent->subjects, subjectToRemove, Subject);
                                    printf("Removed %s.\n", GetSubjectName(choiceEditGradeRemoving - 1));
                                    continue;

                                } else {
                                    if (line2[0] == 'n' || line2[0] == 'N') {
                                        break;
                                    }
                                    else{
                                        puts("Please enter a valid number");
                                    }
                                }

                            }else puts("Please enter a valid number");
                        }while(true);
                        break;

                        default:
                        puts("ERROR");
                        break;
                    }
    
                    break;
                    default:
                    puts("ERROR");
                    break;
                }

            }
            break;
        case 5:
            //Quitting
            puts("Quitting...");
            return 0;
        default:
            puts("Please enter a valid command.");
            break;
        }
    }while(true);

    return 1;
}
