#include "tile.h"
#include "deck.h"
#include<stdio.h>
#include<assert.h>

int main(){
	struct tile_t tile1=CARC_TILE_GREEN;
	//struct tile_t tile2=CARC_TILE_EMPTY;
	struct tile_t tile3=CARC_TILE_INIT;  
	//struct tile_t tile4=CARC_TILE_XROAD ;
	struct tile_t tile4=CARC_TILE_TINI; 
	assert(check_compatible_colors(tile1,tile3,N,S)==1);
	printf("first test");
	assert(check_compatible_colors(tile1,tile3,S,N)==0);
	assert(check_compatible_colors(tile1,tile4,W,E)==0);
	/*assert(check_compatible_colors(tile1,tile2,N,N));
	assert(check_compatible_colors(tile1,tile2,N,N));
	assert(check_compatible_colors(tile1,tile2,N,N));
	assert(check_compatible_colors(tile1,tile2,N,N));
	assert(check_compatible_colors(tile1,tile2,N,N));
	assert(check_compatible_colors(tile1,tile2,N,N));
	assert(check_compatible_colors(tile1,tile2,N,N));*/


	return 0;
}