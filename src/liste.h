#ifndef __LISTE_H__
#define __LISTE_H__

#include "board.h"
#include "tile.h"

//linked list

struct lelement {
  struct case_t *data; // data 
  struct lelement *next; // next element
  struct lelement *prev; // previous element
};

struct link {
  struct lelement *head;
};

struct set{
  struct link *l;
  int size;
};
/*gives the ith empty element neighbor id according to d */
int get_ith_neighbor(struct lelement *elt,enum direction_t d);

/* returns the first element of s*/
struct lelement *get_head(struct set *s );

/* gives the data of elt element*/
struct case_t *get_data(struct lelement*elt);

/*returns the id_in_empty_th element of s*/
struct lelement * get_lelement_from_empty(struct set *s, int id_in_empty);

/*returns an empty link*/
struct link lnk__empty(void) ;

struct set * set__empty();

/*returns the set size*/
int set_size(struct set *s);

/*add add-element at the begining of s*/
int set__add_head(struct set *s, struct case_t *add,enum direction_t d,int tile_id) ;

/*removes c element from s*/
int set__remove(struct set *s,struct lelement *c) ;

/*frees s set*/
void free_set(struct set *s) ;

/*prints s set*/
void set_print(struct set *s,char*prefix);

/*takes (x,y) and returns the id of the corresponding s element */
int get_id_in_empty(struct set*s,int x,int y);
#endif