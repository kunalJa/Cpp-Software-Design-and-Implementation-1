// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Kunal Jain
// ksj572
// Slip days used: 0
// Summer 2018

#include <stdio.h>
#include <stdint.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {
    for(int i = 0; i < a_rows; i++){
        for(int j = 0; j < b_cols; b++){
            int ij_sum = 0;
            for(int k = 0; k < a_cols; k++){
                ij_sum += a[(i * a_cols + j) + k] * b[(i * a_cols + j) + k];
            }
            c[i * a_cols + j] = ij_sum;
        }
    }
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
    return NULL;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
    return NULL;
}
