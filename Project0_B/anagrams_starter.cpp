#include <stdio.h>
#include <assert.h>

#define SIZE 26

int are_anagrams(char[], char[]);
int length(char[]);

int main() {

    printf("running test 'iceman' and 'cinema'...\n");
    char iceman[] = "iceman";
    char cinema[] = "cinema";

    assert(are_anagrams(iceman, cinema));
    printf("passed!\n");

    printf("running test 'raganam' and 'anagram'...\n");
    char raganam[] = "raganam";
    char anagram[] = "anagram";

    assert(are_anagrams(raganam, anagram));
    printf("passed!\n");
    
    printf("running test 'listen' and 'silent'...\n");
    char listen[] = "listen";
    char silent[] = "silent";

    assert(are_anagrams(listen, silent));
    printf("passed!\n");

    printf("running test 'mole' and 'meal'...\n");
    char mole[] = "mole";
    char meal[] = "meal";

    assert(!are_anagrams(mole, meal));
    printf("passed!\n");

    printf("running test 'happy' and 'sad'...\n");
    char happy[] = "happy";
    char sad[] = "sad";

    assert(!are_anagrams(happy, sad));
    printf("passed!\n");
}

int length(char arr[]){
    char *ptr = &arr[0];
    int count = 0;
    while(*ptr != 0){
        ptr++;
        count++;
    }

    return count;
}

int are_anagrams(char first_word[], char second_word[]) {
    int alphabet1[SIZE] = {0};
    int alphabet2[SIZE] = {0};
    int lenFirst = length(first_word);
    int lenSecond = length(second_word);

    for (int i = 0; i < lenFirst; i++){
        alphabet1[first_word[i] - 'a'] ++;
    }

    for (int j = 0; j < lenSecond; j++){
        alphabet2[second_word[j] - 'a'] ++;
    }

    for (int k = 0; k < SIZE; k++){
        if (alphabet1[k] != alphabet2[k]){
            return 0;
        }
    }

    return 1;
}
