#include "liste.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

int get_ith_neighbor(struct lelement *elt,enum direction_t d){
  return elt->data->neighbors[d];
}

struct link lnk__empty(void) {
  struct link l;
  l.head = NULL;
  return l;
}
struct set * set__empty(){
  struct set *s = malloc(sizeof(struct set));
  s->l = malloc(sizeof(struct link));
  *(s->l) = lnk__empty();
  s->size = 0;
  return s;
}
struct lelement *get_head(struct set *s ){
  return s->l->head;
}
struct case_t *get_data(struct lelement*elt){
  return elt->data;
}

struct lelement * get_lelement_from_empty(struct set *s, int id_in_empty){
  struct lelement *e = s->l->head;
  for (int i = 0; i < id_in_empty; ++i){
    e = e->next;
  }
  return e;
}
struct lelement *set__find(struct set *s,struct case_t *add){
  struct lelement *e=s->l->head;
  for(int i=0;i<s->size;i++){
    if(e->data->x==add->x && e->data->y==add->y){
      return e;
    }
    e=e->next;
  }
  return NULL;
}

int set__add_head(struct set *s, struct case_t *add,enum direction_t d,int tile_id){
  if (add == NULL)
    return -1;
  struct lelement *potential_element=set__find(s,add);
  if(potential_element!=NULL){
    potential_element->data->neighbors[d]=tile_id;
    return 1;
  }
  struct lelement *e = malloc(sizeof(struct lelement));
  e->data = add;
  e->data->neighbors[d]=tile_id;
  e->next = s->l->head;
  e->prev = NULL;
  if (s->l->head != NULL)
    s->l->head->prev = e;
  s->l->head = e;
  s->size++;
  return 0;
}

int set__remove(struct set *s,struct lelement *c) {
  if (c == NULL)
    return -1;
  struct lelement *g = c->prev;
  struct lelement *d = c->next;
  if (g != NULL){
    g->next = d;
    d->prev = g;
    }
  else {
    s->l->head = d;
    d->prev = NULL;
  }
  s->size--;
  free(c);
  return 0;
}
void free_set(struct set *s) {
    while (s->l->head != NULL) {
        struct lelement *c = s->l->head;
	      s->l->head = s->l->head->next;
        free(c);
    }
    free(s->l);
    free(s);
}
int set_size(struct set *s){
  return s->size;
}
