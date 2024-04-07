#include "liste.h"
#include <stdlib.h>
#include <stdio.h>
#include<stddef.h>
struct set{
	struct case_t *t;
	int capacity;
	int size;
};
 void shift_left(struct case_t s[],int begin,int end){
    for(int i=begin-1;i<end;i++){
        s[i]=s[i+1];
    }
 }

// Return a struct set representing the empty set
struct set * set__empty(){
	struct set*empty=malloc(sizeof(*empty));
	empty->t=NULL;
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

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
void set__add(struct set *se,struct case_t box){
	if(se->capacity==se->size){
		if(set__is_empty(se)){
			se->t=malloc(sizeof(struct case_t));
			se->capacity=1;
		}
		else{
		se->t=realloc(se->t,(se->capacity)*2*sizeof(struct case_t));
		se->capacity*=2;
		}
	}
	se->t[se->size]=box;
	se->size+=1;
}

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
void set__remove(struct set *se, int n){
	shift_left(se->t,n+1,se->size-1);
	se->size-=1;
	if((se->capacity/2)>=se->size){
		se->capacity/=2;
		se->t=realloc(se->t,se->capacity*sizeof(struct case_t));}
}

// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se){
	free(se->t);
	free(se);
	}

void set__print(struct set*se){
	printf("{size:%d,capacity:%d,[",se->size,se->capacity);
	if(se->t!=NULL){
		for(int i=0;i<se->size;i++){
			case_print(se->t[i]);
			printf(",");
		}
	}
	printf("]}\n");
}
//helper function for debugging : display all elements in se
//void set__print(const struct set * se, void (*print)(void *));