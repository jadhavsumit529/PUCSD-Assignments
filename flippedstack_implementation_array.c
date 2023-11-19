#include<stdlib.h>
#include<stddef.h>

typedef struct list{
	void **es;
	int first;
	int last;
	int size;
	int capacity;
	int flipped;
}list;


typedef struct searchresult{
	int found;
	void *val;
}SearchResult;


//-------------------------------Methods Declaration-------------------------

int len(list *l);
void insert_last(list *l, void *x);
void delete_last(list *l);
void flip_list(list *l);
SearchResult find(list *l,int i);
SearchResult first(list *l);
SearchResult last(list *l);
void grow(list *l);
void shrink(list *l);

//-----------------------------Methods Building---------------------------

list *buildlist(){
	list *l = (list *)malloc(sizeof(list));// use mymalloc in lab
	l->es = (void **)malloc(sizeof(void *)*10);
	l->first = 5;
	l->last = 5;
	l->size = 0;
	l->capacity = 10;
	l->flipped = 0;
	return l;
}


int len(list *l){
	return l->size;
}


void insert_last(list *l,void *x){
	if(l->first == 0  && l->last != l->capacity-1 || l->last == l->capacity-1 && l->first != 0 ){
		shrink(l);
	}

	if(l->size == 0 || l->size == l->capacity){
		grow(l);
	}

	if(l->flipped == 0 && l->last < l->capacity){
		l->es[l->last+1] = x;
		l->last = l->last + 1;
	}
	else{
		l->es[l->first-1] = x;
		l->first = l->first - 1;
	}
	l->size = l->size + 1;
	return;
}


void delete_last(list *l){
	if(l->flipped == 0){
		l->es[l->last] = NULL;
		l->last = l->last - 1;
	}
	else{
		l->es[l->first] = NULL;
		l->first = l->first + 1;
	}
	l->size = l->size - 1;
	return;
}


void flip_list(list *l){
	int temp = l->first;
	l->first = l->last;
	l->last = temp;
	
	if(l->flipped == 0){
		l->flipped = 1;
	}
	else{
		l->flipped = 0;
	}
	return;
}

SearchResult find(list *l, int i){
	SearchResult r;
	r.found =0;
	if(i <= l->size){
		r.val = l->es[l->first+i-1];
		r.found = 1;
	}
	return r;
}


SearchResult first(list *l){
	SearchResult r;
	r.found = 0;
	if(l->size != 0){
		r.val = l->es[l->first];
		r.found = 1;
	}
	return r;
}


SearchResult last(list *l){
	SearchResult r;
	r.found = 0;
	if(l->size != 0){
		r.val = l->es[l->last];
		r.found = 1;
	}
	return r;
}

void shrink(list *l){
	if(l->last == l->capacity && l->flipped == 0  && l->first != 0 ){
		int current = l->first;
		for(int j=0;j<l->size;j++){
			l->es[current - l->first] = l->es[current];
			current = current + 1;
		}
		l->first = 0;
		l->last = l->size;
	}
 	if(l->first == l->capacity && l->flipped == 1 && l->last != 0){
		int current = l->last;
		for(int j=0;j<l->size;j++){
			l->es[current - l->last] = l->es[current];
			current = current + 1;
		}
		l->last = 0;
		l->first = l->size;
	}
	void **array = (void **)realloc(l->es,sizeof(l->size));
	l->capacity = l->size;
	l->es = array;
}

void grow(list *l){
	void **array = (void **)realloc(l->es,2*sizeof(l->capacity));
	l->capacity = 2*l->size;
	int current = l->last;
	int value = l->capacity/4;
	for(int j=0;j<l->size;j++){
		l->es[current + value] = l->es[current];
		current = current -1; 
	}
	l->first = l->first + value;
	l->last = l->last + value;
	l->es = array;
	
	return ;		
}
