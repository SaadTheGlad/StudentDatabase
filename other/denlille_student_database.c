#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helperfunctions.h" // everyone would name this "util.h" or something
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    ANALYSIS_1,
    ALGEBRA_1,
    DIGITAL_ELECTRONICS,
    GAME_DESIGN,
    NUMBER_OF_SUBJECTS
} Subject;

typedef struct {
    int ID;
    char* firstName;
    char* lastName;
    int overallGrade;
    Subject *subjects; // Keep your '*' placement consistent
    int subjectCount;
} Student;

const char* GetSubjectName(Subject subject) {
    switch (subject) {
    case ANALYSIS_1: return "Analysis 1";
    case ALGEBRA_1: return "Algebra 1";
    case DIGITAL_ELECTRONICS: return "Digital Electronics";
    case GAME_DESIGN: return "Game Design";
    default: return "ERROR";
    }
}

Student CreateStudent(int ID, const char* firstName, const char* lastName,
                      int overallGrade, const Subject *subjects, int subjectCount) {
    Student student;
    student.ID = ID;

    student.firstName = strdup(firstName);
    student.lastName = strdup(lastName);

    student.overallGrade = overallGrade;
    student.subjectCount = subjectCount;

    student.subjects = malloc(subjectCount * sizeof(Subject));
    student.subjects = memcpy(student.subjects, subjects,
                              subjectCount * sizeof(Subject));

    return student;
}

void DestroyStudent(Student *student) // { on new line or not? Pick one
{
    free(student->firstName);
    free(student->lastName);
    free(student->subjects);
}

void DebugStudent(const Student* student) // Beware copying vs referencing
{
    puts("******************************");
    printf(">Student ID: %d\n>First name: %s\n>Last name: %s\n>Overall grade: %d\n",
           student->ID, student->firstName, student->lastName, student->overallGrade);

    printf(">Number of subjects: %d\n", student->subjectCount);

    for(int i = 0; i < student->subjectCount; i++){ // Pick between ++i and i++
        printf("->%s\n", GetSubjectName(student->subjects[i]));
    }
    puts("");
}

// You might end up dealing with lots of dynamic lists. Consider
// making some kind of struct along with functions to abstract that stuff
// Macros might help
void AddSubject(Student *student, Subject subject)
{
    if (subject >= NUMBER_OF_SUBJECTS || subject < 0) {
        // I/O user feedback is typically decoupled from application logic
        // i.e. the parts where you communicate with the user are grouped together
        // Here there's an unnecessary interdependency between I/O and app logic
        // What if you wanted to plug this database logic into a GUI/API?
        puts("Subject does not exist.");
        return;
    }

    for (int i = 0; i < student->subjectCount; ++i) {
        if (student->subjects[i] == subject) {
            puts("Subject already added.");
            return;
        }
    }

    // Here you are freeing & allocating every time you add a subject
    // The processes underlying malloc/realloc look something like this:
    // Function call -> iterate through free linked list (O(n)) for suitable block
    // -> if no block found, switch control to the kernel to map in a new page
    // -> wait for kernel to give CPU time back to the application
    // -> check that no error occurred
    // -> update linked lists
    // -> copy the contents of the old buffer to the new one (O(n))
    // -> free the old block (requires another linked list update)
    // -> potentially do some kind of defragmentation process
    // -> these reallocations may also place your buffer in an uncached area of memory
    // Ask yourself if you really want to do this every single time
    student->subjects[student->subjectCount] = subject;
    student->subjectCount++;
    student->subjects = realloc(student->subjects,
                                (student->subjectCount + 1) * sizeof(Subject));
    printf("Added %s.\n", GetSubjectName(subject));
}

void SubjectsPrompt()
{
    // Why the random new lines before puts?
    puts("\nAdd one of the following subjects, or enter N for none/stop: ");
    for(int i = 0; i < NUMBER_OF_SUBJECTS; ++i){
        printf("Enter %d for %s: \n", i + 1, GetSubjectName(i));
    }
}

// As an exercise, try delete this function and rewrite it from scratch.
// Your goal is to use allocated buffers as economically as possible
size_t improved_getline(char** linep, size_t* capacity)
{
    size_t length = 0;
    if (*linep == NULL) {
        *capacity = 16;
        *linep = malloc(*capacity * sizeof(char));
        if (*linep == NULL) return 0;
    }

    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n') break;
        if (length >= *capacity + 1) {
            *capacity *= 2;
            *linep = realloc(*linep, *capacity * sizeof(char));
            if (*linep == NULL) return 0;
        }

        (*linep)[length++] = c;
    }

    (*linep)[length] = '\0';

    return length;
}

Student PromptAndCreateStudent()
{
    Student student;
    // N.B. effective communication with both the computer and other humans
    // I marked this const so its purpose is easily understood
    // I'd probably use another naming convention like ID_LENGTH for constants
    const int IDlength = 3;

    char* line = NULL;
    size_t capacity = 0;

    do {
        printf("Enter the ID (must be %d digits long): \n", IDlength);
        size_t len = improved_getline(&line, &capacity);
        if (line && (len == IDlength)) {
            int items_read = sscanf(line, "%d", &student.ID);
            if (items_read > 0) break;
        }
    } while (true);

    do {
        puts("Enter the first name: ");
        if (improved_getline(&line, &capacity) > 0) break;
    } while (true);

    student.firstName = strdup(line);

    do {
        puts("Enter the last name: ");
        if (improved_getline(&student.lastName, &capacity) > 0) break;
    } while (true);

    student.lastName = strdup(line);

    // Try come up with a nice function to simplify/generalise getting ints
    // from stdin
    do {
        puts("Enter the overall grade (between 0 and 20): ");
        size_t len = improved_getline(&line, &capacity);
        if (line) {
            int items_read = sscanf(line, "%d", &student.overallGrade);
            if (items_read > 0
                && student.overallGrade >= 0 && student.overallGrade <= 20) break;
        }
    } while (true);

    student.subjects = malloc(sizeof(Subject));
    student.subjectCount = 0;

    SubjectsPrompt();
    do {
        printf("Subjects: [");
        for (int i = 0; i < student.subjectCount; ++i) {
            printf("%s%s", GetSubjectName(student.subjects[i]),
                   i == student.subjectCount - 1 ? "" : ", ");
        }
        puts("]");

        size_t len = improved_getline(&line, &capacity);
        int choice;
        if (len > 0) {
            int items_read = sscanf(line, "%d", &choice);
            if (items_read > 0) {
                AddSubject(&student, (Subject) choice - 1);
            } else {
                if (line[0] == 'n' || line[0] == 'N') {
                    break;
                }
            }
        } else continue;
    } while (true);

    return student;
}

void StudentsDestroy(Student *students, int numberOfStudents) { // student_count
    for (int i = 0; i < numberOfStudents; ++i) {
        DestroyStudent(&students[i]);
    }
}

int main()
{
    puts("Starting program...");
    Student saad = PromptAndCreateStudent();

    // Some notes on the functions in `helperfunctions.h`:
    // Do some research on the EOF macro and see if you understand why getchar()
    // returns an int
    // Delete getCharDeluxe
    // Variable names... myStrLen returns "numC"... why not "length"?
    // Whitespace in myStrLen()
    // isNumber() iterates through the string twice

    DebugStudent(&saad);
    DestroyStudent(&saad);

    return 0;
}
