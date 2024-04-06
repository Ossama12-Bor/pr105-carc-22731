#include "liste.h"
struct set{
	struct case_t *t;
	size_t capacity;
	size_t size;
};
 void shift_left(struct case_t s[],size_t begin,size_t end){
    for(size_t i=begin-1;i<end;i++){
        s[i]=s[i+1];
    }
 }

// Return a struct set representing the empty set
struct set * set__empty(){
	struct set*empty=malloc(sizeof(struct set*));
	empt->t=malloc(sizeof(*(empty->t)));
	empty->capacity=0;
	empty->size=0;
	return empty;
}

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se){
	return se->size==0;
}

// Returns non-zero if c belongs to se, 0 otherwise
//int set__find(const struct set *se, void *c);

// Returns the number of elements in se
size_t set__size(const struct set *se){
	return se->size;
}

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
void set__add(struct set *se, struct case_t case_){
	if(se->capacity==se->size){
		se->t=realloc(se->capacity*2);
		se->capacity*=2;
	}
	se->t[se->size]=case_;
	se->size+=1;
}

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
void set__remove(struct set *se, int n){
	shift_left(se->t,n+1,se->size);
	se->size-=1;
	if((se->capacity/2)<=se->size){
		se->capacity/=2;
	}
}

// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se){
	free(se->t);
	free(se);
	}

//helper function for debugging : display all elements in se
//void set__print(const struct set * se, void (*print)(void *));