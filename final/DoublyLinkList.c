void removeValue(DLList L, int value){
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

void swap(List L, int i) {
    Node curr = L->first;
    int index = 0;
    while (curr != NULL) {
        if (index == i) {
            break;
        }
        curr = curr->next;
        index++;
    }
    //now curr is the ith node
    //swap the ith node with the (i+1)th node
    if (curr->next == NULL) break;

    Node next = curr->next;
    Node nextNext = next->next;
    next->next = curr;
    curr->prev = next;
    curr->next = nextNext;
    if (curr == L->first) {
        L->first = next;
        next->prev = NULL;
        nextNext->prev = curr;
    } else if (curr->next->next == NULL) {
        L->last = curr;
    } else {
        curr->prev->next = next;
        next->prev = curr->prev;
        nextNext->prev = curr;
    }
}
//return 1 if has duplicate
//return 0 if do not have duplicate
int hasDuplicate(List L) {
    Node curr = L->first;
    while (curr != NULL) {
        Node tmp = curr->next;
        while (tmp != NULL) {
             if (curr->value == tmp->value) {
                 return 1;
             }
             tmp = tmp->next;
        }
        curr = curr->next;
    }
    return 0;
}

void deleteDuplicate(List L) {
    Node curr = L->first;
    while (curr != NULL) {
        Node tmp = curr->next;
        while (tmp != NULL) {
             if (curr->value == tmp->value) {
                 if (tmp->next == NULL) {
                     curr->next = NULL;
                     L->last = curr;
                 } else {
                     curr->next = tmp->next;
                     tmp->next->prev = curr;
                 }
                 Node newCurr = tmp->next;
                 free(tmp);
                 tmp = newCurr;
                 L->nitems--;
             } else {
                 tmp = tmp->next;
             }
        }
        curr = curr->next;
    }
}

void insert(List L, int val, int i) {
    Node curr = L->first;
    int index = 0;
    while (curr != NULL) {
        if (index == 1) {
            break;
        }
        curr = curr->next;
        index++;
    }
    //now, curr is the ith node
    //insert before/insert after both become quite simple
    Node new = newNode(val);
    if (curr == L->first) {
        new->next = curr;
        curr->prev = new;
        L->first = new;
    } else {
        new->next = curr;
        new->prev = curr->prev;
        curr->prev->next = new;
        curr->prev = new;
    }
    //insert after ith node
    if (curr->next == NULL) {
        L->last->next = new;
        new->prev = L->last;
        L->last = new;
        new->next = NULL;
    } else {
        new->next = curr->next;
        new->prev = curr;
        curr->next->prev = new;
        curr->next = new;
    }
}

void reverseSingly(List L) {
    Node curr = L->first;
    Node prev= NULL;
    Node temp = NULL;
    while (curr != NULL) {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    temp = L->first;
    L->first = L->last;
    L->last = temp;
}

// ListReverse ... reverse a List
void ListReverse(List L)
{
	Link curr = L->first;
	Link tmp = NULL;
	while (curr != NULL) {
		tmp = curr->next;
		curr->next = curr->prev;
		curr->prev = tmp;
		curr = tmp;
	}
	tmp = L->first;
	L->first = L->last;
	L->last = tmp;
}
