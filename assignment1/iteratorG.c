/* iteratorG.c
   Generic Iterator implementation, using doubly linked list

   Written by: Yingzhi Zhou
   Date: 2018/4/19

    You need to submit ONLY this file....

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "iteratorG.h"

// typedef struct IteratorGRep *IteratorG;
//
// typedef int   (*ElmCompareFp)(void const *e1, void const *e2);
// typedef void *(*ElmNewFp)(void const *e1);
// typedef void  (*ElmFreeFp)(void *e1);

typedef struct Node {
    //the value stored in the node
    void *value;
    //point to previous node in the interator
    struct Node *prev;
    //point to next node in the inrerator
    struct Node *next;
} Node;

typedef struct IteratorGRep {
    int size;
    Node *first;
    Node *last;
    //the cursor is in between prevCur and nextCur
    //the node before the cursor ---> prevCur
    //the node after the cursor ---> nextCur
    Node *prevCur;
    Node *nextCur;
    ElmCompareFp cmpElm;
    ElmNewFp newElm;
    ElmFreeFp freeElm;
} IteratorGRep;


//creates a new generic list iterator with given functions to handle elements
IteratorG newIterator(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp) {
    struct IteratorGRep *L;
    L = malloc(sizeof(struct IteratorGRep));
    assert(L != NULL);
    L->size = 0;
    L->first = NULL;
    L->last = NULL;
    L->prevCur = NULL;
    L->nextCur= NULL;
    L->cmpElm = cmpFp;
    L->newElm = newFp;
    L->freeElm = freeFp;
    return L;
}

/*
Let's say 'it' is  [ ^ ]
add(it, 12) will result in the following, and return 1
    [ ^ 12 ]
add(it, 7) will result in the following, and return 1
    [ ^ 7  12 ]
add(it, 15) will result in the following, and return 1
    [ ^ 15  7  12 ]
*/
int add(IteratorG it, void *vp) {
    //create a new node need to be inserted
    assert(it != NULL);
    Node *insert;
    insert = malloc(sizeof(Node));
    insert->value = it->newElm(vp);
    insert->prev = NULL;
    insert->next = NULL;

    //if the list is empty
    if (it->first == NULL) {
        it->first = it->last = insert;
        it->nextCur = insert;
        it->prevCur = NULL;

    //if the ^ is in the head
    } else if (it->prevCur == NULL) {
        insert->next = it->first;
        it->first->prev = insert;
        it->first = insert;
        it->nextCur = insert;

    //if the ^ in the tail
    } else if (it->nextCur == NULL) {
        it->last->next = insert;
        insert->prev = it->last;
        it->last = insert;
        it->nextCur = insert;

    //if the ^ in the middle
    /*
    [2 4 ^ 8 9]
    add(it, 6)
    [2 4 ^ 6 8 9]
    */
    } else {
        insert->next = it->nextCur;
        it->nextCur->prev = insert;
        insert->prev = it->prevCur;
        it->prevCur->next = insert;
        it->nextCur = insert;
    }

    //after add each node, the size of the iteratorG increase by 1
    it->size += 1;
    return 1;
}

//Returns 1 if the given list iterator has more elements when traversing the list in the forward direction
//returns 0 otherwise.
int hasNext(IteratorG it) {
    assert (it != NULL);
    if (it->nextCur == NULL) return 0;
    //else
    return 1;
}

//Returns 1 if the given list iterator has more elements when traversing the list in the reverse direction
//returns 0 otherwise.
int hasPrevious(IteratorG it) {
    assert(it != NULL);
    if (it->prevCur == NULL) return 0;
    //else
    return 1;
}

void *next(IteratorG it) {
    assert(it != NULL);
    //if it has no next value, return NULL
    if (!hasNext(it)) return NULL;

    //if the next node of cursor is the last node of iteratorG
    //next node of cursor point to NULL
    if (distanceToEnd(it) == 1) {
        it->prevCur = it->nextCur;
        it->nextCur = NULL;

    //advance the cursor position
    } else {
        it->prevCur = it->nextCur;
        it->nextCur = it->nextCur->next;
    }

    //returns the pointer to the next element in the given list iterator
    return it->prevCur->value;
}

void *previous(IteratorG it){
    assert(it != NULL);
    //if it has no previous value, return NULL
    if (!hasPrevious(it)) return NULL;

    //if the previous node of cursor is the first node of iteratorG
    if (distanceFromStart(it) == 1) {
        it->nextCur = it->prevCur;
        it->prevCur = NULL;

    //moves the cursor position backwards
    } else {
	    it->nextCur = it->prevCur;
        it->prevCur = it->prevCur->prev;
    }

    //returns the pointer to the previous element in the given list iterator
    return it->nextCur->value;
}

/*
Let's say 'it' is  [ 20 12 ^ 15 5 14 ]
del(it) will result in the following, and return 1
    [ 20 ^ 15 5 14 ]
del(it) will result in the following, and return 1
    [ ^ 15 5 14 ]
del(it) will result in the following, and return 0
    [ ^ 15 5 14 ]
*/
int del(IteratorG it){
	if (!hasPrevious(it)) return 0;

    Node *delete = it->prevCur;
    if (it->size == 1) {
        it->first = it->last = it->prevCur = it->nextCur = NULL;
    //if the node before ^ is head
    } else if (it->prevCur == it->first) {
        it->prevCur = NULL;
        it->nextCur->prev = NULL;
        it->first = it->nextCur;
    //if the node before ^ is tail
    } else if (it->nextCur == NULL) {
        it->prevCur = delete->prev;
        it->last = delete->prev;
        it->last->next = NULL;
    //the other case
    } else {
        delete->prev->next = delete->next;
        delete->next->prev = delete->prev;
        it->prevCur = delete->prev;
    }
    it->freeElm(delete->value);
    free(delete);
    it->size--;
    return 1;
}

/*
Replaces the 'previous' element with the specified element (*vp), if any.
Returns 1 if successful, 0 otherwise (for example, no previous element).
For example:
Let's say 'it' is  [ 20 74 ^ 32 55 5 14 89 ]
    int newVal = 50;
    set(it, &newVal) will result in the following, and return 1
    'it' is changed to [ 20 50 ^ 32 55 5 14 89 ]
*/
int set(IteratorG it, void *vp){
	assert(it != NULL);
    //if there has no privious element before ^, return 0
	if (!hasPrevious(it)) return 0;

    //need to reset the value of node before ^
    Node *reset = it->prevCur;

    //if the node need to be reseted is the first node
    if (reset == it->first) {
        it->first->value = it->newElm(vp);

    //if the node need to be reseted is the last node
    } else if (it->nextCur == NULL) {
        it->last->value = it->newElm(vp);
    }

    //reset the value
    reset->value = it->newElm(vp);
    return 1;
}

/*
If advancement by 'n' elements is not possible
the function returns 'null' and the cursor position is not changed.
*/
IteratorG advance(IteratorG it, int n){
    IteratorG newIt = newIterator(it->cmpElm, it->newElm, it->freeElm);
    Node *curr = NULL;
    //if n > 0, move forward
    if (n > 0) {
        //check if advancement by 'n' elements is possible or not
        if (distanceToEnd(it) < n) return NULL;
        curr = it->nextCur;
        int index = 0;
        while(curr != NULL) {
            if (index == n) break;
            add(newIt, curr->value);
            curr = curr->next;
            index++;
        }
        if (curr != NULL) {
            it->nextCur = curr;
            it->prevCur = curr->prev;
        } else {
            it->nextCur = curr;
            it->prevCur = it->last;
        }
    //if n < 0, move backward
    } else if (n < 0) {
        //check if advancement by 'n' elements is possible or not
        if (distanceFromStart(it) < abs(n)) return NULL;
        curr = it->prevCur;
        int index = 0;
        while(curr != NULL) {
            if (index == abs(n)) break;
            add(newIt, curr->value);
            curr = curr->prev;
            index++;
        }
        if (curr != NULL) {
            it->prevCur = curr;
            it->nextCur = curr->next;
        } else {
            it->prevCur = curr;
            it->nextCur = it->first;
        }
    }
	return newIt;
}

void reverse(IteratorG it){
    assert (it != NULL);
    if (it->size == 0) return;
	Node *curr = it->first;
    Node *tmp = NULL;
    while (curr != NULL) {
        tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = tmp;
        curr = tmp;
    }
    tmp = it->first;
    it->first = it->last;
    it->last = tmp;

    Node *tmpPrev = it->prevCur;
    it->prevCur = it->nextCur;
    it->nextCur = tmpPrev;

}

/*
All such elements are inserted into a new iterator
and this new iterator is returned.
The elements are considered in sequence
from the current cursor position to the end of the iterator.
The new iterator uses the same functions as used by 'it' to handle elements
The original iterator 'it' is unchnaged
and it's cursor position is unchanged.
*/
IteratorG find(IteratorG it, int (*fp) (void *vp) ){
	IteratorG newIt = newIterator(it->cmpElm, it->newElm, it->freeElm);
    Node *curr = it->nextCur;
    while (curr != NULL) {
        if (fp(curr->value)) {
            add(newIt, curr->value);
        }
        curr = curr->next;
    }
	return newIt;
}

/*
Calculates the number of elements before the cursor, and returns the value
For example
========================================================
Let's say 'it' is  [ 15 5 ^ 14 10 5 9 3 ]
distanceFromStart(it) will return 2.

Let's say 'it' is  [ ^ 7 1 8 9 4 ]
distanceFromStart(it) will return 0.

Let's say 'it' is  [ 7 1 8 9 4 ^ ]
distanceFromStart(it) will return 5.
========================================================
*/
int distanceFromStart(IteratorG it){
	if (it->prevCur == NULL) return 0;
	Node *curr = it->prevCur;
    int count = 0;
    while (curr != NULL) {
        curr = curr->prev;
        count++;
    }
    return count;
}

/*
Calculates the number of elements after the cursor, and returns the value
For example
========================================================
Let's say 'it' is  [ 20 12 15 5 ^ 14 10 ]
distanceToEnd(it) will return 2.

Let's say 'it' is  [ ^ 7 1 8 9 4 ]
distanceToEnd(it) will return 5.

Let's say 'it' is  [ 7 1 8 9 4 ^ ]
distanceToEnd(it) will return 0.
========================================================
*/
int distanceToEnd(IteratorG it){
	if(it->nextCur == NULL) return 0;
    Node *curr = it->nextCur;
    int count = 0;
    while (curr != NULL) {
        curr = curr->next;
        count++;
    }
    return count;
}

//Resets 'it' to the start of the list.
void reset(IteratorG it){
	assert(it != NULL);
    it->prevCur = NULL;
    it->nextCur = it->first;
}

//Removes all the nodes in 'it' and frees associated memory.
void freeIt(IteratorG it){
	assert(it != NULL);
    Node *curr = it->first;
    //go though evey node in 'it'
    //free associated memory stored in node and then free the node
    while (curr != NULL) {
        Node *next = curr->next;
        it->freeElm(curr->value);
        free(curr);
        curr = next;
    }
    free(it);
}


// --------------------------------------
