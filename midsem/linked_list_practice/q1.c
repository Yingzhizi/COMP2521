/*
 * Question 1
 * ===============================================
 * Below is a simple linked list implementation
 * finish the "swap" function which takes in a
 * list L and a index i and swaps the node at i
 * with the node at index i+1
 *
 * 1->2->3->4 with i = 1
 * 1->3->2->4
 * ================================================
 * > You can assume i will always be valid
 * > the list will have at minimum 1 node
 * > if i is the last node do nothing
 * > do not swap the _values_ in the nodes, swap the
 *   nodes themselves.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Node
typedef struct _node {
  int value;
  struct _node *next;
} node;
typedef node *Node;

// List
typedef struct _list {
  Node head;
  Node tail;
} list;
typedef list *List;

// prototypes
List newList();
void freeNode(Node n);
Node makeNode(int num);
void addNode(List L, Node n);
void showList(List L);
void swap(List L, int i);

// main function
int main(int argc, char* argv[]) {
  int num;
  int i;
  int readIn;
  List L = newList();
  scanf("%d",&i);
  readIn = scanf("%d",&num);
  while(readIn > 0) {
    addNode(L,makeNode(num));
    readIn = scanf("%d",&num);
  }
  swap(L,i);
  showList(L);
  // i'm a good boy and free my memory
  Node curr = L->head;
  while(curr != NULL){
    Node next = curr->next;
    freeNode(curr);
    curr = next;
  }
  free(L);
  return EXIT_SUCCESS;
}

void freeNode(Node n) {
  free(n);
}

List newList(){
  List L = malloc(sizeof(list));
  L->head = NULL;
  L->tail = NULL;
  return L;
}

Node makeNode(int num){
  Node new = malloc(sizeof(node));
  new->value = num;
  new->next = NULL;
  return new;
}

void addNode(List L, Node n){
  if (L->head == NULL) {
    L->head = n;
    L->tail = n;
  }else{
    L->tail->next = n;
    L->tail = n;
  }
}

void showList(List L){
  Node curr = L->head;
  if (L->head != NULL)
    printf("(H:%d|T:%d) ",L->head->value,L->tail->value);
  else
    printf("(H:NULL|T:NULL) ");

  while(curr != NULL){
    printf("[%d]->",curr->value);
    curr = curr->next;
  }
  printf("NULL");
}

// =============================
// TODO: Complete this function
// =============================
// void swap(List L, int i) {
//   // find the ith node
//   Node prev = NULL;
//   Node curr = L->head;
//   int index = 0;
//   while(curr != NULL) {
//     if(index == i) {
//       break;
//     }
//     prev = curr;
//     curr = curr->next;
//     index++;
//   }
//   if (curr == NULL || curr->next == NULL) {
//     // i was invalid or i == end of list
//     return;
//   }
//   Node next = curr->next;
//   Node nextNext = next->next;
//   // make the i+1th node point to the ith node
//   next->next = curr;
//   // make the ith node point to the i+2th node
//   curr->next = nextNext;
//   // make the i-1th node point to the i+1th node
//   if(prev != NULL) prev->next = next;
//   else L->head = next;
// }
void swap(List L, int i) {
    //find the ith node
    Node prev = NULL;
    Node curr = L->head;
    int count = 0;
    while (curr != NULL) {
        if (count == i) {
            break;
        }
        prev = curr;
        curr = curr->next;
        count++;
    }
    if (curr == NULL || curr->next == NULL) {
        return;
    }
    Node next = curr->next;
    Node nextNext = next->next;
    next->next = curr;
    curr->next = nextNext;
    if (prev!= NULL) {
        prev->next = next;
    } else {
        L->head = next;
    }

}
