#include <stdio.h>

void printMultTableInt(int n);
void printMultTableFrac(int n);

int main(void){

    // You can change this to test your code
    int size = 10;

    printMultTableInt(size);
    printMultTableFrac(size);

    return 0;

}

// Prints multiplication table of integers from 1 to n
void printMultTableInt(int n){

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            printf("%d ", i*j);
        }
        printf("\n");
    }

}

// Prints multiplication table for fractions from 1, 1/2, 1/3 to 1/n
void printMultTableFrac(int n){

    for (float i = 1; i <= n; i++){
        for (float j = 1; j <= n; j++){
            printf("%0.2f ", 1/(i*j));
        }
        printf("\n");
    }

}
