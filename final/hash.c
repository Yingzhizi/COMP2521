#include "List.h"

/************************************
 *
 List approach
 *
*************************************/
typedef struct HashTabRep {
    List *lists;
    int nslots;
    int nitems;
} HashTabRep;

typedef struct HashTabRep *HashTable;
static int hash(Key k, int N) {
    int h = ...
    return h % N;
}

//create a empty HashTable
HashTable newHashTable(int N) {
    HashTable new = malloc(sizeof(HashTable));
    assert(new != NULL);
    new->lists = malloc(N * sizeof(List));
    assert(new->lists != NULL);
    int i;
    for (i = 0; i < N; i++) {
        new->lists[i] = newList();
    }
    new->nslots = 0;
    new->nitems = N;
}

//free memory associated with hashTable
void dropHashTable(HashTable ht) {
    free(ht->lists);
    free(ht);
}

//insert new value into a hashTable
void hashTableInsert(HashTable ht, Item it) {
    Key insert = key(it);
    int i = hash(insert, ht->nslots);
    ListInsert(ht->lists[i], it);
}

void hashTableDelete(HashTable ht, Key k) {
    int i = hash(k, ht->nslots);
    ListDelete(ht->lists[i], k);
}

Item *hashTableSearch(HashTable ht, Key k) {
    int i = hash(k, ht->nslots);
    return ListSearch(ht->lists[i], k);
}


/************************************
 *
 Linear Probling
 *
*************************************/
void insert(HashTable ht, Item it) {
    assert (ht->nslots < ht->nitems);
    int N = ht->nslots;
    Item *a = ht->items;
    // get the key of the item need to be inserted
    Key new = key(it);
    int i, j, h = hash(new, N);
    for (j = 0; j < N; j++) {
        // make sure the index not greater than N, search something before
        i = (j + h) % N;
        // find a postition to insert it
        if (a[i] == noItem) break;
        // is already in the hashTable
        if (eq(new, key(a[i]))) break;
    }
    if (a[i] == noItem) {
        // insert one more
        ht->nitems++;
    }
    a[i] = it;
}

Item *search(HashTable ht, Key k) {
    int N = ht->nslots;
    Item *a = ht->items;
    int i, j, h = hash(k, N);
    for (j = 0; j < N; j++) {
        i = (h + j) % N;
        // cannot find the corresponding key
        if (a[i] == noItem) return NULL;
        // find the key, return the value we found
        if (eq(k, key(a[i]))) return &(a[i]);
    }
    return NULL;
}
