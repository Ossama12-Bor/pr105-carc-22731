#ifndef __LISTE_H__
#define __LISTE_H__

#include "board.h"
#include "tile.h"

struct lelement {
  struct case_t *data;
  struct lelement *next;
  struct lelement *prev;
};

struct link {
  struct lelement *head;
};

struct set{
  struct link *l;
  int size;
};

int get_ith_neighbor(struct lelement *elt,enum direction_t d);
struct lelement *get_head(struct set *s );
struct case_t *get_data(struct lelement*elt);
struct lelement * get_lelement_from_empty(struct set *s, int id_in_empty);
struct link lnk__empty(void) ;
struct set * set__empty();
int set_size(struct set *s);
int set__add_head(struct set *s, struct case_t *add,enum direction_t d,int tile_id) ;
int set__remove(struct set *s,struct lelement *c) ;
void free_set(struct set *s) ;
#endif
