// removeValue.c
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/*
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for
    detailed specification and description of your task.

    - DO NOT modify code in the file DLList.h .
    - You can add helper functions in this file.
    - DO NOT add "main" function in this file.

*/



void removeValue(DLList L, int value){
	//
	// if (L->nitems == 0) {
	// 	return;
	// } else if (L->nitems == 1) {
	// 	if (L->first->value == value) {
	// 		L->first = L->last = L->curr = NULL;
	// 		L->nitems = 0;
	// 	}
	// 	return;
	// }
	//
	// DLListNode *temp = NULL;
	//
	// while (L->first->value == value) {
	// 	if (L->first->next == NULL) {
	// 		L->first = L->last = L->curr = NULL;
	// 		L->nitems = 0;
	// 		return;
	// 	}
	// 	temp = L->first;
	// 	L->first = L->first->next;
	// 	L->first->prev = NULL;
	// 	// free(temp->value);
	// 	free(temp);
	// 	L->curr = L->first;
	// 	L->nitems--;
	// }
	//
	// DLListNode *curr = L->first;
	//
	// while (curr->next != NULL) {
	// 	if (curr->value == value) {
	// 		temp = curr;
	// 		curr->prev->next = curr->next;
	// 		curr->next->prev = curr->prev;
	// 		// free(temp->value);
	// 		free(temp);
	// 		L->curr = L->first;
	// 		L->nitems--;
	// 	}
	// 	curr = curr->next;
	// }
	//
	// // the last node
	// if (curr->value == value) {
	// 	temp = curr;
	// 	L->last = curr->prev;
	// 	L->last->next = NULL;
	// 	// free(temp->value);
	// 	free(temp);
	// 	L->curr = L->first;
	// 	L->nitems--;
	// }
	if (L->nitems == 0) {
	return;
	}
	DLListNode *curr = L->first;
	while (curr != NULL) {
		if (curr->value == value) {
			//if the node we need to remove is head
			if (curr == L->first) {
				if (L->nitems == 1) {
					L->first = L->last= L->curr = NULL;
					L->nitems--;
					return;
				}
				L->first = L->curr = curr->next;

			} else if (curr->next == NULL) {
				curr->prev->next = NULL;
				L->last = curr->prev;

			} else {
				curr->prev->next = curr->next;
				curr->next->prev= curr->prev;
				L->curr = L->first;
			}
			
			DLListNode *tmp = curr->next;
			free(curr);
			curr = tmp;
			L->nitems--;
		} else {
			curr = curr->next;
		}
	}
}
