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
//la direction de add par rapport à la tile 
int set__add_head(struct set *s, struct case_t *add,enum direction_t d,int tile_id){
  if (add == NULL)
    return -1;
  struct lelement *potential_element=set__find(s,add);
  if(potential_element!=NULL){
    potential_element->data->neighbors[d]=tile_id;
    free(add->neighbors);
    free(add);
    return 1;
  }
  struct lelement *e = malloc(sizeof(struct lelement));
  e->data = add;
  e->data->neighbors[d]=tile_id;
  if(s->size==0){
	s->l->head=e;
	e->next=NULL;
	e->prev=NULL;
	s->size++;
  }
  else{
  e->next = s->l->head;
  e->prev = NULL;
  if (s->l->head != NULL)
    s->l->head->prev = e;
  s->l->head = e;
  s->size++;}
  return 0;
}
int set__remove(struct set *s,struct lelement *c) {
  if (c == NULL)
    return -1;
  struct lelement *g = c->prev;
  struct lelement *d = c->next;
  if( g == NULL && d ==NULL){
    *(s->l)=lnk__empty();
  }
  else if(g==NULL){
    s->l->head = d;
    d->prev = NULL;
  }
  else if(d==NULL){
	g->next=NULL;
  }
  else{
    g->next = d;
    d->prev = g;
    }
  
  free(c);
  s->size--;
  return 0;
}
void free_set(struct set *s) {
    while (s->l->head != NULL) {
        struct lelement *c = s->l->head;
	      s->l->head = s->l->head->next;
        free(c->data->neighbors);
        free(c->data);
        free(c);
    }
    free(s->l);
    free(s);
}
int set_size(struct set *s){
  return s->size;
}

void set_print(struct set *s,char*prefix){
  printf("%s [",prefix);
  struct lelement *elt=s->l->head;
  for(int i=0;i<s->size;i++){
    print_case(elt->data);
    elt=elt->next;
  }
  printf("]\n");
}

int get_id_in_empty(struct set*s,int x,int y){
  struct lelement *curseur=s->l->head;
  for(int i=0;s->size;i++){
    if(curseur->data->x==x && curseur->data->y==y){
      return i;
    }
    curseur=curseur->next;
  }
  return -1;
}