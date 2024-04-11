#ifndef __LISTE_H__
#define __LISTE_H__

#include "board.h"

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
struct link lnk__empty(void) ;
struct set * set__empty();
int set_size(struct set *s);
int set__add_head(struct set *s, struct case_t *add) ;
int set__remove(struct set *s,struct lelement *c) ;
void free_set(struct set *s) ;
#endif
