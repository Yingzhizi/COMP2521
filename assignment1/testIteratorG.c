/*
  testIteratorG.c
  Client to test Generic Iterator

  Written by: ....
  Date: ....
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "iteratorG.h"
#include "positiveIntType.h"
#include "stringType.h"

#define MAXARRAY 5

int main(int argc, char *argv[])
{

  /* The following code, inside the comments, may or may not be correct!

     It's provided in case you find it difficult to understand
     how to create a generic iterator, and use it's functions.

     Please study SetG example we discussed in the lecture in detail.

     The code below only tests basic operations, however
     make sure that you do test all the required functions properly in
     your test file.

  */

  /* =======================================
     --------- positiveIntType List Iterator ----------
  */


  IteratorG it1 = newIterator(positiveIntCompare, positiveIntNew, positiveIntFree);
  printf("Test delete from empty set\n");
  printf("expected returned value: 0\n");
  printf("actual returned value: %d\n", del(it1));
  int a[MAXARRAY] = { 25, 12, 6, 82 , 11};

  int i;
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]);
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }


	/*
	The above loop should print ...
		Inserting 25: Success
		Inserting 12: Success
		Inserting 6: Success
		Inserting 82: Success
		Inserting 11: Success
	*/
  //
  // [11 82 6 12 25 ^]
  assert(advance(it1, -2) == NULL);
  reset(it1);
  advance(it1, 1);
  reset(it1);
  advance(it1, 2);
  reset(it1);
  advance(it1, 3);
  reset(it1);
  advance(it1, 4);
  reset(it1);
  advance(it1, 5);
  reset(it1);
  assert(advance(it1, 6) == NULL);


  // //[ 11 82 ^]
  // previous(it1);
  // //[11 ^ 82]
  // printf("should print(1)%d\n", del(it1));
  // // [ ^ 82]
  // assert((int *) previous(it1) == NULL);
  // int *v3 = (int *)next(it1);
  // printf("Next value is(82): %d \n", *v3 );
  // int newVal = 11;
  // add(it1, &newVal);
  // next(it1);

  //======================================================
  // printf("should print(1)%d\n", del(it1));
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(1): %d \n", d_start); //should print 0
  // printf("Distance to end(0): %d \n", d_end); //should print 5
  // int *v1 = (int *) previous(it1);
  // printf("Next previous value is(11): %d \n", *v1 );
  //
  // //[ ^ 11]
  // printf("should print(0)%d\n", del(it1));
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(0): %d \n", d_start); //should print 0
  // printf("Distance to end(1): %d \n", d_end); //should print 5
  //
  // //[ ^ ]
  // printf("should print(0)%d\n", del(it1));
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(0): %d \n", d_start); //should print 0
  // printf("Distance to end(1): %d \n", d_end); //should print 5
  // assert((int *) previous(it1) == NULL);
  //
  // printf("should print(0)%d\n", del(it1));
  //
  //
  //
  // next(it1);
  // //[11 ^]
  // printf("should print(1)%d\n", del(it1));
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(0): %d \n", d_start); //should print 0
  // printf("Distance to end(0): %d \n", d_end); //should print 5
  //

  // int d_start = distanceFromStart(it1);
  // int d_end = distanceToEnd(it1);
  // printf("Distance from start(0): %d \n", d_start); //should print 0
  // printf("Distance to end(5): %d \n", d_end); //should print 5
  // int *v1 = (int *) next(it1);
  // //[11 ^ 82 6 12 25]
  // printf("Next value is(11): %d \n", *v1 );  // should print "Next value is: 11"
  //
  // int *v2 = (int *) next(it1);
  // //[11  82 ^ 6 12 25]
  // printf("Next value is(82): %d \n", *v2 );  // should print "Next value is: 82"
  //
  // int *v3 = (int *) previous(it1);
  // //[11 ^ 82 6 12 25]
  // printf("Previous value is(82): %d \n", *v3 );     // should print "Previous value is: 82"
  //
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(1): %d \n", d_start); //should print 1
  // printf("Distance to end(4): %d \n", d_end); //should print 4
  //
  // //test Reset
  // //[^11 82 6 12 25]
  // printf("RESET\n");
  // reset (it1);
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(0): %d \n", d_start); //should print 0
  // printf("Distance to end(5): %d \n", d_end); //should print 5
  // printf("%d\n", del(it1)); //should print 0
  // int *v7 = (int *) next(it1);
  // printf("Next value is(11): %d \n", *v7 );  // should print "Next value is: 11"
  // //[11 ^ 82 6 12 25]
  // printf("%d\n", del(it1)); //should print 1
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // //[^ 82 6 12 25]
  // printf("Distance from start(0): %d \n", d_start); //should print 0
  // printf("Distance to end(4): %d \n", d_end); //should print 4
  // reverse(it1);
  // //[25 12 6 82 ^]
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(4): %d \n", d_start); //should print 4
  // printf("Distance to end(0): %d \n", d_end); //should print 0
  // //set 82 to 11
  // //[25 12 6 11 ^]
  // int newVal = 50;
  // printf("%d\n", set(it1, &newVal)); //should printf ;
  // int *v8 = (int *) previous(it1);
  // printf("Previous value is(50): %d \n", *v8 );  // should print "Previous value is: 50"
  // //[25 12 6 ^ 50]
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(3): %d \n", d_start); //should print 4
  // printf("Distance to end(1): %d \n", d_end); //should print 0
  // reverse(it1);
  // //[50 ^ 6 12 25]
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(1): %d \n", d_start); //should print 4
  // printf("Distance to end(3): %d \n", d_end); //should print 0
  // previous(it1);
  // //[^ 50 6 12 25]
  // IteratorG new = advance(it1, -3);
  // assert(new == NULL);
  // new = advance(it1, 5);
  // assert(new == NULL);
  // new = advance(it1, 4);
  // assert(new != NULL);
  // //[50 6 12 25 ^]
  // d_start = distanceFromStart(it1);
  // d_end = distanceToEnd(it1);
  // printf("Distance from start(4): %d \n", d_start); //should print 4
  // printf("Distance to end(0): %d \n", d_end); //should print 0
  // //return: new = [^ 50 60 12 25]
  // d_start = distanceFromStart(new);
  // d_end = distanceToEnd(new);
  // printf("Distance from start(0): %d \n", d_start); //should print 4
  // printf("Distance to end(4): %d \n", d_end); //should print 0
  //


  /* =======================================
     --------- stringType List Iterator ----------
  */
  IteratorG it2 = newIterator(stringCompare, stringNew, stringFree);

  char *strA[MAXARRAY];
  strA[0] = strdup("john");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby");

  int j;
  for(j=0; j<4; j++){
    int result = add(it2 , strA[j]);
    printf("Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }
  //
	// /*
	// The above loop should print ...
	// 	Inserting john: Success
	// 	Inserting rita: Success
	// 	Inserting john: Success
	// 	Inserting abby: Success
	// */
  //
  char *c = (char *)previous(it2);
  printf("%s\n", c);
  printf("%d\n", del(it2));
  char *v4 = (char *) next(it2);
  printf("Next value is: %s \n", v4 );  // should print: "Next value is: abby"

  char *v5 = (char *) next(it2);
  printf("Next value is: %s \n", v5 );  // should print: "Next value is: john"

  char *v6 = (char *) previous(it2);
  printf("Previous value is: %s \n", v6 );      // should print: "Previous value is: john"

  return EXIT_SUCCESS;

}
