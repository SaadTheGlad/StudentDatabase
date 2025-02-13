#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int strcmpM(const char *string1, const char *string2)
{
    int i = 0;

    //We iterate over every character and stop when we hit the null terminator
    for(;string1[i] != 0; ++i)
    {
        //We compare the characters of the strings and see if they're equal
        if(string1[i] != string2[i])
        {
            //Equal letters, move on to the next iteration
            break;
        }
    }

    return string1[i] - string2[i];
}

bool isNumber(const char* string){

    for(int i = 0; string[i] != 0; ++i){
        printf("[%c]\n", string[i]);
        if(isdigit(string[i]) == 0){
            return false;
        }
    }

    return true;
}

char* mystrdup(char* str){
    
    int length = strlen(str);
    char* duplicatedString = malloc((length + 1) * sizeof(char));

    for(int i = 0; i < length; ++i){
        duplicatedString[i] = str[i];
    }
    duplicatedString[length] = 0;

    return duplicatedString;
}

char* getline()
{
    int currentMax = 12;
    char *string = malloc(currentMax * sizeof(char));
    int length = 0;

    char c;

    bool startedWithNewLine = false;

    char startingC = getchar();
    
    if(startingC == '\n'){
        string = NULL;
        return string;
    }

    if(startingC != '\n'){
        string[0] = startingC;
        length++;
    }

    do{
        //This optimisation is actually important as reallocating every time the string changes by 1
        //fragments the heap and is inefficient and makes the CPU do more work.
        if(length > currentMax - 1)
        {
            currentMax *= 2;
            string = realloc(string, (currentMax) * sizeof(char));

        }
        
        c = getchar();
        string[length] = c;
        length++;

    }while(c != '\n' && c != EOF);

    //We do minus 1 here and place the null terminator where the \n is
    string[length - 1] = 0;
    return string;

}

int GetInt(size_t* len){

    char* line = NULL;
    size_t capacity = 16;
    int num;

    do {
        *len = improved_getline(&line, &capacity);
        if (line) {
            int items_read = sscanf(line, "%d", &num);
            if (items_read > 0) {
                return num;
            }
            else{
                *len = 0;
                return -1;
            }
        }
    } while (true);

    
}

size_t improved_getline(char** linep, size_t* capacity){

    size_t length = 0;
    if(*linep == NULL){
        *capacity = 16;
        *linep = malloc(*capacity * sizeof(char*));
        if(*linep == NULL) return 0;
    }

    int c;
    while((c = getchar()) != EOF){
        if(c == '\n') break;

        if(length > *capacity - 1){
            *capacity *= 2;
            *linep = realloc(*linep, *capacity * sizeof(char*));
            if(*linep == NULL) return 0;
        }

        (*linep)[length++] = c;
    }

    (*linep)[length] = '\0';

    return length;

}


int WordCount(char* line)
{
    int numWords = 0;

    for(int letterIterator = 0; line[letterIterator] != 0; letterIterator++)
    {
          
        if(line[letterIterator] != ' ' && (line[letterIterator + 1] == ' ' || line[letterIterator + 1] == 0))
        {
            //We are at the end of a word so count it
            numWords++;
        }    
    
    }

    return numWords;
}

int myStrLen(const char *string)
{
    int length = 0;
    char c;

    do{
        c = string[length];
        length++;
    }while(c != 0);

    return length - 1;
}

double Factorial(int n)
{
    double total = 1;
    for(int i = 0; i < n; ++i)
    {
        total *= (n - i);
    }
    return total;
}
