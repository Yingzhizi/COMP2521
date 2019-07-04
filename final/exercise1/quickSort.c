#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int* quickSort(int arr_size, int* arr, int *result_size) {
    // Complete this function
    int pivot = arr[0];
    int i = 0;
    int index = 0;
    while(i < arr_size) {
        if (arr[i] < pivot) {
            result_size[index] = arr[i];
            index = index + 1;
        }
        i++;
    }

    result_size[index] = pivot;
    index = index + 1;
    int k = 0;
    while (k < arr_size) {
        if (arr[k] > pivot) {
            result_size[index] = arr[k];
            index = index + 1;
        }
        k++;
    }

    //result_size[index] = '\0';

    return result_size;
}

int main() {
    int n;
    scanf("%i", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int arr_i = 0; arr_i < n; arr_i++) {
       scanf("%i",&arr[arr_i]);
    }
    int result_size;
    int* result = quickSort(n, arr, &result_size);
    for(int result_i = 0; result_i < result_size; result_i++) {
        if(result_i) {
            printf(" ");
        }
        printf("%d", result[result_i]);
    }
    puts("");


    return 0;
}
