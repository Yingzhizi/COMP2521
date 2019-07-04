#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BTree.h"

int isHeap(BTree t){
    if (t == NULL) return 1;

    int checkLeft = isHeap(left(t));
    int checkRight = isHeap(right(t));

    int flag = 1;

    if (left(t) != NULL) {
        if (data(t) < data(left(t))) {
            flag = 0;
        }
    }

    if (right(t) != NULL) {
        if (data(t) < data(right(t))) {
            flag = 0;
        }
    }

    if (flag == 1 && checkLeft && checkRight) return 1;

    return 0;
}

int isHeap(BTree t){
    if (t == NULL) return 1;
    if (left(t) != NULL) {
        if (data(t) > data(left(t))) {
            return isHeap(left(t));
        }
    }
    if (right(t) != NULL) {
        if (data(t) > data(right(t))) {
            return isHeap(right(t));
        }
    }
}
