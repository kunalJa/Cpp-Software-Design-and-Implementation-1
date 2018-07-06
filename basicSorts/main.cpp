#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int indexOne, int indexTwo) {
    int temp = arr[indexOne];
    arr[indexOne] = arr[indexTwo];
    arr[indexTwo] = temp;
}

void printArray(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort (int arr[], int len) {
    printf("Insertion Sort: \n");

    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr, j-1, j);
            }
        }
    }
}

void selectionSort (int arr[], int len) {
    printf("Selection Sort: \n");

    int minI = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            arr[j] < arr[minI] ? minI = j : minI = minI;
        }

        swap(arr, i, minI++);
    }
}

void sort(int arr[], int len, void (*sortType) (int arr[], int len)) {
    printf("The unsorted array: \n");
    printArray(arr, len);

    sortType(arr, len);

    printf("The sorted array: \n");
    printArray(arr, len);
}


int main() {
    int arr[] = {1, 3, 2, 9, 8, 2, 16, 18, 4, 5};
    sort(arr, 10, &insertionSort);

    printf("\n");

    int arr2[] = {1, 3, 2, 9, 8, 2, 99, 18, 4, 5};
    sort(arr2, 10, &selectionSort);

    return 0;
}
