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

typedef struct word_t { // Struct to hold my found words for printing and comparing to the dictionary
    char* word_ptr;     // Pointer to where in the article the first letter of the word can be found
    int length;
} word;

int isALetter(char c);
int inDictionary(word w, char dictionary[]);
char toUpperCase(char c);


// Prints to console words that are not in the known (passed in) dictionary- these may be miss-spelled
void spellCheck(char article[], char dictionary[]) {
    int currentCharIndex = 0;
    int wordStart = 0;  // holds the index of the start of the potential word
    int wordFound = 0;  // a flag for when a potential word is being measured
    char currentChar = article[currentCharIndex];

    while(currentChar != 0){
        if(isALetter(currentChar) && wordFound == 0){ // current char is a letter = this may potentially be a word
            wordFound = 1;
            currentCharIndex++;
        }

        else if(isALetter(currentChar) && wordFound == 1){
            currentCharIndex++;
        }

        else if(!isALetter(currentChar) && wordFound == 0){
            currentCharIndex++;
            wordStart++;
        }

        else{
            int wordLength = currentCharIndex - wordStart;
            if (wordLength > 1){
                word current = {&(article[wordStart]), wordLength}; // placing our found word into the struct

                if (!inDictionary(current, dictionary)){
                    for(int i = 0; i < current.length; i++){
                        printf("%c", current.word_ptr[i]);
                    }
                    printf("\n");
                }
            }
            wordFound = 0;
            currentCharIndex++;
            wordStart = currentCharIndex;
        }
        currentChar = article[currentCharIndex];
    }

    if (wordFound == 1){ // i.e. a word was found but reached the end of the article before a non-letter character arrived
        int wordLength = currentCharIndex - wordStart;
        if (wordLength > 1){
            word current = {&(article[wordStart]), wordLength};
            if (!inDictionary(current, dictionary)){
                for(int i = 0; i < current.length; i++){
                    printf("%c", current.word_ptr[i]);
                }
                printf("\n");
            }
        }
    }
}

// Checks whether or not char c is a letter in the English alphabet
int isALetter(char c){
    return (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c<= 'z')));
}

// compares a known word to the words in the passed in dictionary
// returns 1 if it is found in the dictionary
// returns 0 otherwise
int inDictionary(word w, char dictionary[]){
    int dictInd = 0;
    int correctNumLetters = 0;
    char nextWord = '\n';
    while(dictionary[dictInd] != 0){
        for (int i = 0; i < w.length; i++){
            if(dictionary[dictInd] == nextWord || dictionary[dictInd] == 0){ // break if reached the end of the dictionary word
                break;
            }

            if(toUpperCase(w.word_ptr[i]) == toUpperCase(dictionary[dictInd])){
                correctNumLetters++;
            }
            dictInd++;
        }

        if (correctNumLetters == w.length && (dictionary[dictInd] == nextWord || dictionary[dictInd] == 0)){
            return 1;   // the words match only when they are the same length and have all the same letters
        }

        while(dictionary[dictInd] != nextWord){ // moves the pointer to the next word in the dictionary
            if(dictionary[dictInd] == 0){
                break;
            }
            dictInd++;
        }

        if(dictionary[dictInd] == nextWord){ // increments the dictionary index pointer to the beginning of the next word
            dictInd++;
        }

        correctNumLetters = 0;
    }
    return 0;
}

// Converts a character, if its a lowercase letter, to an uppercase letter and returns it
char toUpperCase(char c){
    if ((c >= 'a') && (c<= 'z')){
        return c + ('A' - 'a');
    }
    return c;
}
