#ifndef _TILE_H_
#define _TILE_H_

#include "move.h"
#include "deck.h"

enum direction_t{
  N,
  E,
  S,
  W,
  NUM_SIDES,
}; 


/* Returns a tile's colors */
int same_colors(enum color_t *t1,enum color_t *t2,int n);

enum color_t* get_tile_colors(struct tile_t *t);

enum color_t* get_tile_side(struct tile_t *t,enum direction_t d);

/* Checks if two tiles have compatible colors */
int check_compatible_colors(struct tile_t t1,struct tile_t  t2,enum direction_t d1, enum direction_t d2);

/*flips tile according to d direction*/
struct tile_t flip_tile(struct tile_t tile,int d);

#endif
