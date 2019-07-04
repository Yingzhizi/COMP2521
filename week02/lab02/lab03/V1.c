// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "DLList.h"

void testInsertBeforeAndDelete(DLList L);
void testInsertAfter(DLList L);
void deleteMessagePrintout(DLList L);

int main(int argc, char *argv[])
{
	DLList myList;
	myList = getDLList(stdin);
	putDLList(stdout,myList);
	assert(validDLList (myList));
	// TODO: more tests needed here
	testInsertBeforeAndDelete(myList);
	testInsertAfter(myList);
	return 0;
}

	//test function DLListBefore
void testInsertBeforeAndDelete(DLList L) {

	//original function
	assert(validDLList(L));
	printf("===Testing function DLLostBeforeAndDelete===\n");

	printf("The current text look like: \n");
	putDLList(stdout, L);
	printf("current item is: %s\n", DLListCurrent(L));
	printf("The nitems is: %d\n", DLListLength(L));
	int original_size = DLListLength(L);

	//current item is head
	//insert before head
	printf("***CASE1: Insert node before head***\n");
	DLListBefore(L, "insert before the first line");
	assert(validDLList(L));
	printf("The current text look like: \n");
	putDLList(stdout, L);
	printf(">Test the current position\n");
	printf(">The current item after insert: %s\n",DLListCurrent(L));
	printf(">Test the nitem after inserted: %d\n", DLListLength(L));
	assert(DLListLength(L) == original_size + 1);

	printf("\n");

	//delete the first item from a list
	printf("Now, delete the inserted item\n");
	DLListDelete(L);
	assert(validDLList(L));
	printf("The current text look like: \n");
	putDLList(stdout, L);
	deleteMessagePrintout(L);
	assert(DLListLength(L) == original_size);

	printf("\n");

	//current item move to middle
	printf("Move current position to 2ed node***\n");
	DLListMoveTo(L, 2);
	assert(validDLList(L));
	printf("The current item is: %s\n",DLListCurrent(L));
	printf("The nitems is: %d\n", DLListLength(L));

    printf("\n");

	printf("***CASE2: Insert node in the MIDDLE node***\n");
	DLListBefore(L, "insert in the middle.");
	assert(validDLList(L));
	printf("The current text look like: \n");
	putDLList(stdout, L);
	printf(">The current item is: %s\n",DLListCurrent(L));
	printf(">The nitems is: %d\n", DLListLength(L));
	assert(DLListLength(L) == original_size + 1);

    printf("\n");

	printf("Now, delete the inserted item\n");
	DLListDelete(L);
	assert(validDLList(L));
	printf("The current text look like: \n");
	putDLList(stdout, L);
	deleteMessagePrintout(L);
	assert(DLListLength(L) == original_size);

	printf("\n");

	printf(">Move current position to LAST node\n");
	DLListMoveTo(L, DLListLength(L));
	assert(validDLList(L));
	printf("The current item is: %s\n",DLListCurrent(L));
	printf("The nitems is: %d\n", DLListLength(L));

	printf("\n");

	printf("***CASE3: Insert node in the end***\n");
	DLListBefore(L, "insert before the last node.");
	assert(validDLList(L));
	printf("The current text look like: \n");
	putDLList(stdout, L);
	printf(">The current item is: %s\n",DLListCurrent(L));
	printf(">The nitems is: %d\n", DLListLength(L));
	assert(DLListLength(L) == original_size + 1);

	printf("\n");

	printf("Now, delete the inserted item\n");
	DLListDelete(L);
	assert(validDLList(L));
	printf("The current text look like: \n");
	putDLList(stdout, L);
	deleteMessagePrintout(L);
	assert(DLListLength(L) == original_size);

	printf("\n");

	printf("Now, the curr item is the last item\n");
	printf("Test delete the last item.\n");
	DLListDelete(L);
	assert(validDLList(L));
	printf("The current text look like: \n");
	putDLList(stdout, L);
	deleteMessagePrintout(L);
	assert(DLListLength(L) == original_size - 1);

}

	//test function DLListAfter
void testInsertAfter(DLList L) {
}

void deleteMessagePrintout(DLList L) {
	printf(">Test the current position\n");
	if (DLListLength(L) != 0) {
		printf(">The current item after delete: %s\n", DLListCurrent(L));
	}
	printf(">Test the nitem after delete: %d\n", DLListLength(L));
}
