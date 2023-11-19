#include <stdlib.h>

typedef struct element {
    int v;
} elt;

typedef struct Node {
    elt *val;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Set {
    Node *head;
    Node *tail;
    int size;
} Set;

typedef struct SearchResult {
    elt *val;
    int found;
} SearchResult;
//---------------SET METHODS---------------//
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

// compare two elements
int cmp(elt *e1, elt *e2) {
    return e1->v - e2->v;
}

// create a new node with the given element
Node *createNode(elt *e) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->val = e;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

// create a new set with the given elements
Set *buildSet(elt *e[], int n) {
    Set *s = (Set *)malloc(sizeof(Set));
    s->head = NULL;
    s->tail = NULL;
    s->size = 0;
    for (int i = 0; i < n; i++) {
        put(e[i], s);
    }
    return s;
}

// return the number of elements in the set
int len(Set *s) {
    return s->size;
}

// return 1 if the set is empty, 0 otherwise
int isEmpty(Set *s) {
    return s->size == 0;
}

// add an element to the set
void put(elt *x, Set *s) {
    Node *n = createNode(x);
    if (isEmpty(s)) {
        s->head = n;
        s->tail = n;
    } else {
        Node *cur = s->head;
        while (cur != NULL && cmp(cur->val, x) < 0) {
            cur = cur->next;
        }
        if (cur == NULL) {
            // insert at the end
            n->prev = s->tail;
            s->tail->next = n;
            s->tail = n;
        } else {
            // insert before cur
            n->prev = cur->prev;
            n->next = cur;
            if (cur->prev != NULL) {
                cur->prev->next = n;
            } else {
                s->head = n;
            }
            cur->prev = n;
        }
    }
    s->size++;
}

// remove an element from the set
void rmv(elt *x, Set *s) {
    Node *cur = s->head;
    while (cur != NULL && cmp(cur->val, x) < 0) {
        cur = cur->next;
    }
    if (cur != NULL && cmp(cur->val, x) == 0) {
        if (cur->prev != NULL) {
            cur->prev->next = cur->next;
        } else {
            s->head = cur->next;
        }
        if (cur->next != NULL) {
            cur->next->prev = cur->prev;
        } else {
            s->tail = cur->prev;
        }
        free(cur);
        s->size--;
    }
}

// search for an element in the set
SearchResult search(elt *x, Set *s) {
    SearchResult res;
    res.found = 0;
    res.val = NULL;

    Node *curr = s->head;
    while (curr != NULL && cmp(curr->val, x) < 0) {
        curr = curr->next;
    }
    if (curr != NULL && cmp(curr->val, x) == 0) {
        res.found = 1;
        res.val = curr->val;
    }
    return res;
}// find the element in the set that is greater than x, if any
SearchResult next(elt *x, Set *s) {
SearchResult res = {NULL, 0};
Node *cur = s->head;
while (cur != NULL && cmp(cur->val, x) <= 0) {
cur = cur->next;
}
if (cur != NULL) {
res.val = cur->val;
res.found = 1;
}
return res;
}

// find the element in the set that is less than x, if any
SearchResult prev(elt *x, Set *s) {
SearchResult res = {NULL, 0};
Node *cur = s->tail;
while (cur != NULL && cmp(cur->val, x) >= 0) {
cur = cur->prev;
}
if (cur != NULL) {
res.val = cur->val;
res.found = 1;
}
return res;
}

// find the last element in the set
SearchResult last(Set *s) {
SearchResult res = {NULL, 0};
if (!isEmpty(s)) {
res.val = s->tail->val;
res.found = 1;
}
return res;
}

// find the first element in the set
SearchResult first(Set *s) {
SearchResult res = {NULL, 0};
if (!isEmpty(s)) {
res.val = s->head->val;
res.found = 1;
}
return res;
}
