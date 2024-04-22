#include "tile.h"
#include <stdlib.h>
#define VER_NUMBER_PER_SIDE 3
int same_colors(enum color_t *t1,enum color_t *t2,int n){
	for(int i=0;i<n;i++){
		if(t1[i]!=t2[i])
			return 0;
	}
	return 1;
}

enum color_t *get_tile_colors(struct tile_t *t){
	return t->c;
}
enum color_t *get_tile_side(struct tile_t *t,enum direction_t d ){
	enum color_t*p=malloc(sizeof(enum color_t)*VER_NUMBER_PER_SIDE);
	for(int i=0;i<VER_NUMBER_PER_SIDE;i++)
		*(p+i)=t->c[d*VER_NUMBER_PER_SIDE+i];
	return p;
}
int check_compatible_colors(struct tile_t t1,struct tile_t t2,enum direction_t d1,enum direction_t d2){
	enum color_t *side1=get_tile_side(&t1,d1);
	enum color_t *side2=get_tile_side(&t2,d2);
	int is_compatible=same_colors(side1,side2,VER_NUMBER_PER_SIDE);
	free(side1);
	free(side2);
	return is_compatible;
}