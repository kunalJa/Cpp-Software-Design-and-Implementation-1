/*
 * Project1.cpp
 * 
 * Name: Kunal Jain
 * EE312 Summer 2018
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include "header.c"

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

#define NULL 0

typedef struct word_t {
    char* word_ptr;
    int length;
} word;

int isALetter(char c);
int inDictionary(word w, char dictionary[]);

void spellCheck(char article[], char dictionary[]) {
    int articleCharIndex = 0;
    int wordStart = 0;
    char currentChar = article[articleCharIndex];

    while(currentChar != NULL){
        printf("%c", currentChar);
        currentChar++;
    }
}

int isALetter(char c){
    return (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c<= 'z')));
}