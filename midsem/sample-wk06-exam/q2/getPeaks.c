// getPeaks.c
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/*
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for
    detailed specification and description of your task.

    - DO NOT modify code in the file DLList.h .
    - You can add helper functions in this file.
    - DO NOT add "main" function in this file.

*/

void addNode(DLList L, DLListNode *added);

DLList getPeaks(DLList L){
	DLList peaksL = newDLList();
	if (L->nitems > 2) {
		DLListNode *curr = L->first->next;
		while (curr->next != NULL) {
			if (curr->value > curr->prev->value && curr->value > curr->next->value) {
				addNode(peaksL, curr->value);
			}
			curr = curr->next;
		}
	}
	return peaksL;

}

//addNode to the end of the list
void addNode(DLList L, int val) {
	DLListNode *new = newDLListNode(val);
	assert(L != NULL);
	if (L->nitems == 0) {
		L->first = L->curr = L->last = new;
	} else {
		new->prev = L->last;
		L->last->next = new;
		L->last = new;
	}
	L->nitems++;
}

//addNode in the sorted order(increasing)
void addSorted(DLList L, int val) {
	DLListNode *new = newDLListNode(val);
	assert(L != NULL);
	//insert to an empty
	if (L->nitems == 0) {
		L->first = L->last = L->curr = new;
	} //insert before the first
	 else if (val <= L->first->value) {
	 	new->next = L->first;
		L->first->prev = new;
		L->first = new;
	} else if (val >= L->last->value) {
		L->last->next = new;
		new->prev = L->last;
		L->last = new;
	} else {
		Node curr = L->first;
		while (curr->value < value) {
			curr = curr->next;
		}
		new->next = curr;
		new->prev = curr->prev;
		curr->prev->next = new;
		curr->prev = new;
	}
}

//addNode in the sorted order(decreasing)
//same as the decreasing

//reverse the doubly linked List
void reverseList(DLList L) {

}
