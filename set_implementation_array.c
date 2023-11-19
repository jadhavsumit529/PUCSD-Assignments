/*
 *    This is implementation of set where elements
 *    are kept in array. Not following any particular order.
 */

#include<stdio.h>

// ---------------- Set Structures ---------------------

typedef struct set {
    int size;
    int a[100000];
}Set;

typedef struct searchResult {
    int found;
    int val;
}SearchResult;


// ----------------- Set Methods ----------------------
Set buildSet(int a[], int n);
int len(Set s);

Set put(int x, Set S);
Set rmv(int x, Set S);

int isEmpty(Set s);
SearchResult search(int x, Set S);

SearchResult prev(int x, Set s);
SearchResult next(int x, Set s);
SearchResult first(Set s);
SearchResult last(Set s);


// -------------- Internal Structures -----------------

typedef struct _searchIndex {
    int found;
    int index;
}_SearchIndex;

// ---------------- INTERNAL METHODS -----------------
Set _buildEmptySet();
_SearchIndex _searchIndex(int x, Set s);

//---------------------------------------------------


// precondition : n >= 0
// output : set s with all items of array a in it.
// postcondition : for all i, 0<=i<n, a[i] in s 
Set buildSet(int a[], int n) {
    Set s = _buildEmptySet();
    int i = 0;
    while(n-i != 0) {
        s = put(a[i],s);
        i = i + 1;
    }
    return s;
}

// output : size of the set s
int len(Set s) {
    return s.size;
}

// output : set after putting element in s
// postcondition : search(x,s) should return found as 1
Set put(int x, Set s) {
    SearchResult r = search(x,s);
    if(r.found == 0) {
        s.a[len(s)] = x;
        s.size = s.size + 1;
    }
    return s;
}

// output : set after remeoval of x from s
// postcondition : search(x,s) should return found as 0
Set rmv(int x, Set s) {
    _SearchIndex r = _searchIndex(x,s);
    if(r.found == 1) {
        // index of value x in array a
        int i = r.index + 1;
        while(len(s)-i != 0) {
            s.a[i-1] = s.a[i];
            i = i + 1;
        }
        s.size = s.size - 1;
    }
    return s;
}

// output : 1 if set is empty otherwise 0
int isEmpty(Set s) {
    int k = 1;
    if(len(s) == 0) 
        k = 0;
    return k;
}

// output : r, r.found == 1 if element is there in set
//         otherwise 0
SearchResult search(int x, Set s) {
    SearchResult r;
    r.found = 0;
    _SearchIndex idx = _searchIndex(x,s);
    if(idx.found == 1) {
        r.found = 1;
        r.val = x;
    }
    return r;
}

// This method should return next element of x 
// as if all elements of set are put in non-decreasing order
// output : r, r.found will be 1 if x exists and has next element
//          otherwise 0
SearchResult next(int x, Set s) {
    SearchResult r;
    r.found = 0;
    SearchResult xser = search(x,s);
    if(xser.found == 1) {
        int i = 0;
        // Initialize i to first index where a[i] > x is found
        while(i < len(s) && s.a[i] < x)
            i = i + 1;
        if(i < len(s)) {
            r.found = 1;
            r.val = s.a[i];
        }

        // Invariant : r.val is next in a[0,i)
        while(i < len(s)) {
            if(r.val > s.a[i] && x < s.a[i])
                r.val = s.a[i];
            i = i + 1;
        }
    }
    return r;

}

// This method should return previous element of x 
// as if all elements of set are put in non-decreasing order
// output : r, r.found will be 1 if x exists and has previous element
//          otherwise 0
SearchResult prev(int x, Set s) {
    SearchResult r;
    r.found = 0;
    SearchResult xser = search(x,s);
    if(xser.found == 1) {

        int i = 0;
        // Initialize i to first index where a[i] < x is found
        while(i < len(s) && s.a[i] > x)
            i = i + 1;
        if(i < len(s)) {
            // in a[0,i], a[i] is previous value
            r.found = 1;
            r.val = s.a[i];
        }

        // Invariant : r.val is previous in a[0,i)
        while(i < len(s)) {
            if(r.val < s.a[i] && x > s.a[i])
                r.val = s.a[i];
            i = i + 1;
        }
    }
    return r;
}


// first element of s as if all elements of s are put in order
// output : r.found will be 1 if minimum is there otherwise 0
SearchResult first(Set s) {
    SearchResult r;
    r.found = 0;
    if(len(s) > 0) {
        r.found = 1;
        r.val = s.a[0];
    }
    int i = 0;
    while(i < len(s)) {
        if(r.val > s.a[i])
            r.val = s.a[i];
        i = i + 1;
    }
    return r;
}


// last element of s as if all elements of s are put in order
// output : r.found will be 1 if maximum is there otherwise 0
SearchResult last(Set s) {
    SearchResult r;
    r.found = 0;
    if(len(s) > 0) {
        r.found = 1;
        r.val = s.a[0];
    }
    int i = 0;
    while(i < len(s)) {
        if(r.val > s.a[i])
            r.val = s.a[i];
        i = i + 1;
    }
    return r;
}


//END of Set Methods
//---------------------------------------------------

// output : set with no items in it
// postcondition : len(s) == 0
Set _buildEmptySet() {
    Set s;
    s.size = 0;
    return s;
}

// precondition : s.size >= 0
// output : r
// postcondition : if x is in s then r.found == 1 
//                 and r.val = index of x in array
//                 otherwise r.found == 0
_SearchIndex _searchIndex(int x, Set s) {
    _SearchIndex r;
    r.found = 0;

    int i = 0;
    while((r.found-1)*(s.size-i) != 0) {
        if(s.a[i] == x) {
            r.found = 1;
            r.index = i;
        }
        i = i + 1;
    }
    return r;
}

//END of Internal methods
//---------------------------------------------------


int main(void) {
}
