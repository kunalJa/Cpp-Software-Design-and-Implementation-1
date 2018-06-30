//
// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Kunal Jain
// ksj572
// Slip days used: 0
// Summer 2018
//

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "String.h"

#define SIGNATURE (~0xdeadbeef)

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Private function that finds the size of a string
 */
int strLen(const char* src) {
    int i = 0;
    while (src[i] != 0){
        i++;
    }
    return i;
}

/*
 * Private Function to add string signature
 */
void addSig(char* string, int startIndex){
    string[startIndex+3] = (char) (~0xde);
    string[startIndex+2] = (char) (~0xad);
    string[startIndex+1] = (char) (~0xbe);
    string[startIndex] = (char) (~0xef);
}

/*
 * Private Function
 * Copies a string to a heap allocated string
 * Adding the signature at the end
 */
void copyWithSIG(const char* src, char* heap) {
    int i = 0;
    while (src[i] != 0){
        heap[i] = src[i];
        i++;
    }
    heap[i] = '\0';
    addSig(heap, i + 1);
}

/* 
 * Allocate a utstring on the heap. 
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
	int srcLen = strLen(src);
	int totalCapacity = (srcLen * sizeof(char)) + 5;
	char* String = (char*) malloc(totalCapacity);
	copyWithSIG(src, String);

	UTString* utString = (UTString*) malloc(2 * sizeof(uint32_t) + sizeof(char*));
	utString->length = srcLen;
	utString->capacity = totalCapacity - 5; // Remove 1 byte for null termination and 4 bytes for signature
	utString->string = String;

    return utString;
}

/* 
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    assert(isOurs(s));
    return s->length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s. 
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));
    int suffixSize = strLen(suffix);
    int i = s->length;
    int j = 0;

    while (i < s->length + suffixSize && i < s->capacity) { // Check whether we reached end of suffix or overflowing
        s->string[i] = suffix[j];
        i++;
        j++;
    }

    s->length = i; // Updating the utStrings length
    s->string[i] = '\0';
    addSig(s->string, i + 1);

    return s;
}

/* 
 * Copy src into dst.
 *  dst must be a valid UTString. 
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst. 
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    int i = 0;

    while (src[i] != 0 && i < dst->capacity) {
        dst->string[i] = src[i];
        i++;
    }

    dst->length = i;
    dst->string[i] = '\0';
    addSig(dst->string, i + 1);

    return dst;
}

/*
 * Free all memory associated with the given UTString. 
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self->string);
    free(self);
}

/* 
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity, 
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata. 
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
	if (s->capacity >= new_capacity) {
	    return s;
	}

	char* oldString = s->string;
	char* newString = (char*) malloc(new_capacity * sizeof(char) + 5);
    s->capacity = new_capacity;
    s->string = newString;

    int i = 0;

    while (oldString[i] != 0 && i < s->capacity) {
        s->string[i] = oldString[i];
        i++;
    }

    s->length = i;
    s->string[i] = '\0';
    addSig(s->string, i + 1);
    free(oldString);

    return s;
}
