// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "DLList.h"

void testInsertBefore (DLList L);
void testInsertAfter (DLList L);
void testDLListDelete (DLList L);
void testInsertToEmptyList(DLList L);
void printUpdateMessage (DLList L);

int main(int argc, char *argv[])
{
	DLList myList;
	myList = getDLList(stdin);
	putDLList(stdout,myList);
	assert(validDLList (myList));
	// TODO: more tests needed here
    testInsertBefore (myList);
    testInsertAfter (myList);
    testDLListDelete (myList);
    testInsertToEmptyList(myList);
	return 0;
}

void testInsertBefore (DLList L)
{
    assert(validDLList(L));
	printf("=====Testing function DLListBefore=====\n");

	printf("The current text look like: \n");
	putDLList(stdout, L);
    printf("\n");
	printf("current item is: %s\n", DLListCurrent(L));
	printf("The nitems is: %d\n", DLListLength(L));
	int original_size = DLListLength(L);

    printf("\n");
    //current item is head
	//insert before head
	printf("[CASE1: Insert node before head]\n");
	DLListBefore(L, "insert before the first line");
	assert(validDLList(L));
	printUpdateMessage (L);
	assert(DLListLength(L) == original_size + 1);
	printf("\n");

    //current item move to middle
    printf("[Move current position to 2ed line]\n");
    DLListMoveTo(L, 2);
    assert(validDLList(L));
    printf("The current item is: %s\n",DLListCurrent(L));
    printf("The nitems is: %d\n", DLListLength(L));
    printf("\n");

    printf("[CASE2: Insert node before the MIDDLE line]\n");
	DLListBefore(L, "insert in the middle.");
	assert(validDLList(L));
	printUpdateMessage (L);
	assert(DLListLength(L) == original_size + 2);
    printf("\n");

    printf("[Move current position to LAST node]\n");
	DLListMoveTo(L, DLListLength(L));
    assert(DLListMoveTo(L, DLListLength(L)) == 1);
	assert(validDLList(L));
	printf("The current item is: %s\n",DLListCurrent(L));
	printf("The nitems is: %d\n", DLListLength(L));
	printf("\n");

    printf("[CASE3: Insert node in the end]\n");
	DLListBefore(L, "insert before the last node.");
	assert(validDLList(L));
	printUpdateMessage (L);
	assert(DLListLength(L) == original_size + 3);
	printf("\n");
}

void testInsertAfter (DLList L)
{
    assert(validDLList(L));
    int original_size = DLListLength(L);
	printf("=====Testing function DLListAfter=====\n");
    printf("[Move current position to the last]\n");
    DLListMoveTo(L, DLListLength(L));
    assert(validDLList(L));
    assert(DLListMoveTo(L, DLListLength(L)) == 1);
    printf("The current item is: %s\n",DLListCurrent(L));
    printf("\n");

    printf("[CASE1: Insert node after the last line]\n");
    DLListAfter(L, "insert after the last line");
    assert(validDLList(L));
    printUpdateMessage (L);
    assert(DLListLength(L) == original_size + 1);
    printf("\n");

    printf("[Move current position to the head]\n");
    DLListMoveTo(L, 1);
    assert(validDLList(L));
    printf("The current item is: %s\n",DLListCurrent(L));
    printf("\n");

    printf("[CASE2: Insert node after the middle/first line]\n");
    DLListAfter(L, "insert after the first line");
    assert(validDLList(L));
    printUpdateMessage(L);
    assert(DLListLength(L) == original_size + 2);
    printf("\n");
}

void testDLListDelete (DLList L) {
    assert(validDLList(L));
    int original_size = DLListLength(L);
	printf("=====Testing function DLListDelete=====\n");
    printf("[Move current position to the last]\n");
    DLListMoveTo(L, DLListLength(L));
    assert(validDLList(L));
    assert(DLListMoveTo(L, DLListLength(L)) == 1);
    printf("The current item is: %s\n",DLListCurrent(L));
    printf("\n");

    printf("[Case 1: delete the last line]\n");
    DLListDelete(L);
    assert(validDLList(L));
    printUpdateMessage(L);
    assert(DLListLength(L) == original_size - 1);
    printf("\n");

    printf("[Move current position to the first line]\n");
    DLListMoveTo(L, 1);
    assert(validDLList(L));
    printf("The current item is: %s\n",DLListCurrent(L));
    printf("\n");

    printf("[Case 2: delete the first line]\n");
    DLListDelete(L);
    assert(validDLList(L));
    printUpdateMessage(L);
    assert(DLListLength(L) == original_size - 2);
    printf("\n");

    printf("[Delete unitl one line left]\n");
    int i = 0;
    while (DLListLength(L) > 1) {
        DLListDelete(L);
        assert(validDLList(L));
        assert(DLListLength(L) == original_size - 3 - i);
        i++;
    }
    printUpdateMessage(L);
    assert(DLListLength(L) == 1);
    printf("\n");

    printf("[Case 3: delete node from the list contain only one node]\n");
    DLListDelete(L);
    assert(validDLList(L));
    //printf("The current item is: %s\n",DLListCurrent(L));
    printf("The nitems is: %d\n", DLListLength(L));
    assert(DLListLength(L) == 0);
    assert(DLListIsEmpty(L) == 1);
    printf("\n");

    printf("[Case 4: delete node from the empty list]\n");
    DLListDelete(L);
    assert(validDLList(L));
    printf("The nitems is: %d\n", DLListLength(L));
    assert(DLListLength(L) == 0);
    assert(DLListIsEmpty(L) == 1);
}

void testInsertToEmptyList(DLList L) {
    printf("=====Testing insert node to empty list=====\n");
    assert(validDLList(L));
    assert(DLListLength(L) == 0);
    printf("[Test insert before]\n");
    DLListBefore(L, "Before");
    assert(validDLList(L));
    printUpdateMessage(L);
    assert(DLListLength(L) == 1);
    printf("\n");

    printf("[Delete the node]\n");
    DLListDelete(L);
    assert(validDLList(L));
    assert(DLListLength(L) == 0);
    assert(DLListIsEmpty(L) == 1);
    printf("\n");

    printf("[Test insert after]\n");
    DLListBefore(L, "After");
    assert(validDLList(L));
    printUpdateMessage(L);
    assert(DLListLength(L) == 1);
    printf("\n");
}

void printUpdateMessage (DLList L) {
    printf("The current text look like: \n");
	putDLList(stdout, L);
    printf("\n");
	printf("The current item after insert: %s\n",DLListCurrent(L));
	printf("Test the nitem after inserted: %d\n", DLListLength(L));
}
