// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Kunal Jain
// ksj572
// Slip days used: 0
// Summer 2018

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

// Multiplies two matrices together
// Each matrix is an array of doubles
void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {
    for(uint32_t i = 0; i < a_rows; i++){
        for(uint32_t j = 0; j < b_cols; j++){
            double ij_sum = 0;
            for(uint32_t k = 0; k < a_cols; k++){
                double AVAL = a[(i * a_cols) + k]; // Cycle through A by row
                double BVAL = b[(k * b_cols) + j]; // Cycle through B by column
                ij_sum += AVAL * BVAL;
            }
            c[i * b_cols + j] = ij_sum; // Row major ordering
        }
    }
}

// Multiplies two matrices together
// Each matrix is an array of arrays of doubles
// Requires freeing from the heap by client
double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
    double** c = (double**)malloc(a_rows* sizeof(double*)); // Allocate a new matrix on the heap
    for(uint32_t i = 0; i < a_rows; i++){
        *(c + i) = (double*)malloc(b_cols * sizeof(double));
    }

    for(uint32_t i = 0; i < a_rows; i++){
        for(uint32_t j = 0; j < b_cols; j++){
            double ij_sum = 0;
            for(uint32_t k = 0; k < a_cols; k++){
                double AVAL = *(*(a + i) + k); // Cycle through A by row = a[i][k]
                double BVAL = *(*(b + k) + j); // Cycle through B by column = b[k][j]
                ij_sum += AVAL * BVAL;
            }
            *(*(c + i) + j) = ij_sum; // = c[i][j]
        }
    }
    return c;
}

// Flips a matrix over main its diagonal, that is it switches the row and column indices of the matrix
// producing another matrix denoted as A^T
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
    double** c = (double**)malloc(a_cols* sizeof(double*)); // Allocate a matrix of reverse dimensions on heap
    for(uint32_t i = 0; i < a_cols; i++){
        *(c + i) = (double*)malloc(a_rows * sizeof(double));
    }

    for(uint32_t i = 0; i < a_rows; i++){
        for(uint32_t j = 0; j < a_cols; j++){
            *(*(c + j) + i) = *(*(a + i) + j); // c[j][i] = a[i][j]
        }
    }
    return c;
}
