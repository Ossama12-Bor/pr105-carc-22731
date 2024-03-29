#ifndef _TILE_H_
#define _TILE_H_

#include "move.h"

enum direction_t {
  N=0,
  E=1,
  S=2,
  W=3,
}; 


/* Returns a tile's colors */
enum color_t* get_tile_colors(struct tile_t* t){
  return t->c;
}

enum color_t* get_tile_side(struct tile_t* t,enum direction d){
  
}

/* Checks if two tiles have compatible colors */
int check_compatible_colors(struct tile_t* t1,struct tile_t* t2,enum direction_t d1,
			    enum direction_t d2){
  
}


#endif
