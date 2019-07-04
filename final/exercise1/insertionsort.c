#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

void insertionSort1(int n, int arr_size, int* arr) {
    // Complete this function
    int insert = arr[n - 1];
    int i;
    for (i = n - 2; insert <= arr[i + 1]; i--) {
        if (arr[i] > insert) {
            arr[i + 1] = arr[i];
        } else {
            arr[i + 1] = insert;
        }
        int k;
        for (k = 0; k < arr_size; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
}

void insertionSort2(int n, int arr_size, int* arr) {
    // Complete this function
    int j;
    for (j = 1; j < n; j++) {
        int insert = arr[j];
        int i;
        for (i = j - 1; insert <= arr[i + 1]; i--) {
            if (arr[i] > insert) {
                arr[i + 1] = arr[i];
            } else {
                arr[i + 1] = insert;
            }
        }
        int k;
        for (k = 0; k < arr_size; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%i", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int arr_i = 0; arr_i < n; arr_i++) {
       scanf("%i",&arr[arr_i]);
    }
    insertionSort1(n, n, arr);
    return 0;
}
