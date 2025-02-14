#ifndef HELPER   /* Include guard */
#define HELPER
#include <stdbool.h>

//Returns 0 if equal, returns >1 if string 1 bigger than string 2 and <1 otherwise
int strcmpM(const char *string1, const char *string2);

char* getline();

size_t improved_getline(char** linep, size_t* capacity);

int GetInt(size_t* len);

bool isNumber(const char* string);

char getCharDeluxe();

int WordCount(char* line);

int myStrLen(const char* string);

double Factorial(int n);

#endif // HELPER