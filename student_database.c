#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "list.h"
#include "subject.h"
#include "student.h"
#include <stdbool.h>
#include <ctype.h>
#include "sorting.h"

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

bool SmallestToLargest(int a, int b){
    if(a > b) return true;
    else return false;
}

bool LargestToSmallest(int a, int b){
    if(a < b) return true;
    else return false;
}

int ThisShitsWayTooLongBro(){
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


    Student saad = {
        .ID = 200,
        .firstName = "lina",
        .lastName = "kebach",
        .fullName = "linakebach",
        .overallGrade = 15,
        .subjects = ListCreate(sizeof(Subject))
    };

    Student lina = {
        .ID = 180,
        .firstName = "saad",
        .lastName = "kebach",
        .fullName = "saadkebach",
        .overallGrade = 20,
        .subjects = ListCreate(sizeof(Subject))
    };

    Student den = {
        .ID = 190,
        .firstName = "den",
        .lastName = "lille",
        .fullName = "denlille",
        .overallGrade = 20,
        .subjects = ListCreate(sizeof(Subject))
    };

    ListAdd(&database.students, &saad);
    ListAdd(&database.IDs, &saad.ID);
    ListAdd(&database.students, &lina);
    ListAdd(&database.IDs, &lina.ID);
    ListAdd(&database.students, &den);
    ListAdd(&database.IDs, &den.ID);


    do{
        printf("\n> ");
        size_t len = improved_getline(&command, &capacity);
        int choice = CommandToInt(command);

        switch (choice){
        case 0:
            //Listing students
            puts("");
            puts("Students: ");
            StudentSortID(&database.students, SmallestToLargest);
            if(!StudentsList(&database.students)){
                puts("No students in database.");
            }
            puts("Sort alphabetically? (Y/N)");
            char* line = NULL;
            len = improved_getline(&line, &capacity);
            if (len == 1 && (line[0] == 'Y' || line[0] == 'y')){
                puts("Students: ");
                StudentSortAlphabetical(&database.students, SmallestToLargest);
                StudentsList(&database.students);
                break;
            }else if(len == 1 && (line[0] == 'N' || line[0] == 'n')){
                break;
            }else{
                continue;
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
                    if (len == 1 && (line[0] == 'Y' || line[0] == 'y')){
                        ListRemoveAt(&database.students, studentIndex);   
                        ListRemove(&database.IDs, removedStudent->ID, int);
                        printf("Student with ID %d has been removed.\n", removedStudent->ID);
                        break;
                    }else if(len == 1 && (line[0] == 'N' || line[0] == 'n')){
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
                    float newGrade;
                    while(true){
                        size_t len;
                        newGrade = GetFloat(&len);
                        if((newGrade >= 0) && (newGrade <= 20)) break;
                        else puts("Please enter a valid number.");     
                    }
                    printf("Set grade to %.2f.\n", newGrade);
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
                        char* line = NULL;
                        int choiceEditGradeAdding;
                        do{
                            printf("%s %s's subjects: [", editedStudent->firstName, editedStudent->lastName);
                            for (int i = 0; i < editedStudent->subjects.count; ++i) {
                                const char* pointerName = GetSubjectName(*(int*)ListGet(&(editedStudent->subjects), i));
                                printf("%s%s", pointerName, 
                                    i == editedStudent->subjects.count - 1 ? "" : ", ");
                                   
                            }
                            puts("]");

                            size_t len = improved_getline(&line, &capacity);
                            if (len > 0) {
                                int items_read = sscanf(line, "%d", &choiceEditGradeAdding);
                    
                                if (items_read > 0) {
                                    Subject subjectToAdd = choiceEditGradeAdding - 1;
                                    if (subjectToAdd >= NUMBER_OF_SUBJECTS || subjectToAdd < 0) {
                    
                                        puts("Subject does not exist.");
                                        continue;
                                    }
                                    
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

                        char* line2 = NULL;
                        int choiceEditGradeRemoving;
                        do{
                            printf("%s %s's subjects: [", editedStudent->firstName, editedStudent->lastName);
                            for (int i = 0; i < editedStudent->subjects.count; ++i) {
                                const char* pointerName = GetSubjectName(*(int*)ListGet(&(editedStudent->subjects), i));
                                printf("%s%s", pointerName, 
                                    i == editedStudent->subjects.count - 1 ? "" : ", ");
                                   
                            }
                            puts("]");

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

}

int main(){
    puts("Starting program...");
    return ThisShitsWayTooLongBro();


    // int T[12] = {3,4,5,1,7,8,6,5,9,8,12,9};
    
    // SortSelection(T, 12);

    // printf("[");
    // for(int i = 0; i < 12; ++i){
    //     printf("%d%s", T[i], i == 11 ? "]\n" : ",");
    // }

    return 0;

}
