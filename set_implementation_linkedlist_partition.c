#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Structures

typedef struct Element {
    int v;
} elt;

typedef struct Node {
    elt *value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Set {
    int size;
    Node *first;
    Node *last;
} Set;

typedef struct partition{
	struct partition *next;
	struct partition *prev;
	Node *head;
}Partition;

typedef struct SearchResult {
    elt *val;
    int found;
} SearchResult;

//------------  SET METHODS --------------

Set *buildSet(elt *e[], int n);
int len(Set *s);
int isEmpty(Set *s);

void put(elt *x, Set *s);
void rmv(elt *x, Set *s);

SearchResult search(elt *x, Set *s);
SearchResult next(elt *x, Set *s);
SearchResult prev(elt *x, Set *s);
SearchResult last(Set *s);
SearchResult first(Set *s);


// ---------------- INTERNAL METHODS -----------------

int cmp(elt *e1, elt *e2);


// Compare two elements
int cmp(elt *e1, elt *e2) {
    if (e1->v < e2->v) {
        return -1;
    } else if (e1->v > e2->v) {
        return 1;
    } else {
        return 0;
    }
}

// Create a new node
Node *createNode(elt *value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

Partition *createPartitionNode(elt *value) {
    Partition *pnode = (Partition*) malloc(sizeof(Partition));
    pnode->head = createNode(value);
    pnode->prev = NULL;
    pnode->next = NULL;
    return pnode;
}



// Create a new set
Set *buildSet(elt *e[], int n) {
    Set *s = (Set*) malloc(sizeof(Set));
    s->size = 0;
    s->first = NULL;
    s->last = NULL;
    for (int i = 0; i < n; i++) {
        put(e[i], s);
    }
    return s;
}

// Get the length of the set
int len(Set *s) {
    return s->size;
}

// Check if the set is empty
int isEmpty(Set *s) {
    return s->size == 0;
}

// Insert an element into the set
void put(elt *x, Set *s) {
    Node *node = createNode(x);
    if (isEmpty(s)) {
        s->first = node;
        s->last = node;
	Partition *p = createPartitionNode(x);
	Node *pcurrent = p->head;
    } 
    else {
	int k=1;    
        Node *current = s->first;
        while (current != NULL && cmp(current->value, x) < 0) {
            current = current->next;

        }
        if (current == NULL) {
            node->prev = s->last;
            s->last->next = node;
            s->last = node;
        }
       	else if (cmp(current->value, x) == 0) {
            free(node);
        }
       	else if (current->prev == NULL) {
            node->next = s->first;
            s->first->prev = node;
            s->first = node;
	} 
	else {
            node->prev = current->prev;
            node->next = current;
            current->prev->next = node;
            current->prev = node;
        }
    
    s->size++;
    }


}

// Remove an element from the set
void rmv(elt *x, Set *s) {
    if (!isEmpty(s)) {
        Node *current = s->first;
        while (current != NULL && cmp(current->value, x) < 0) {
            current = current->next;
        }
        if (current != NULL && cmp(current->value, x) == 0) {
            if (current->prev == NULL) {
                s->first = current->next;
            } else {
                current->prev->next = current->next;
            }
            if (current->next == NULL) {
                s->last = current->prev;
            } else {
                current->next->prev = current->prev;
            }
            free(current);
            s->size--;
        }
    }
}

// Search for an element in the Set
SearchResult search(elt *x, Set *s) {
    Node *n = s->first;
    while (n != NULL) {
        if (cmp(x, n->value) == 0) {
            SearchResult result = {n->value, 1};
            return result;
        } else if (cmp(x, n->value) < 0) {
            break;
        }
        n = n->next;
    }
    SearchResult result = {NULL, 0};
    return result;
}

// Return the element following a given element in the Set
SearchResult next(elt *x, Set *s) {
    Node *n = s->first;
    while (n != NULL) {
        if (cmp(x, n->value) < 0) {
            SearchResult result = {n->value, 1};
            return result;
        }
        n = n->next;
    }
    SearchResult result = {NULL, 0};
    return result;
}

// Return the element preceding a given element in the Set
SearchResult prev(elt *x, Set *s) {
    Node *n = s->last;
    while (n != NULL) {
        if (cmp(x, n->value) > 0) {
            SearchResult result = {n->value, 1};
            return result;
        }
        n = n->prev;
    }
    SearchResult result = {NULL, 0};
    return result;
}

// Return the last element in the Set
SearchResult last(Set *s) {
    if (s->last != NULL) {
        SearchResult result = {s->last->value, 1};
        return result;
    }
    SearchResult result = {NULL, 0};
    return result;
}

// Return the first element in the Set
SearchResult first(Set *s) {
    if (s->first != NULL) {
        SearchResult result = {s->first->value, 1};
        return result;
    }
    SearchResult result = {NULL, 0};
    return result;
}

int main(){

}
