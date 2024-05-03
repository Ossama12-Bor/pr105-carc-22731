#include "tile.h"
#include "deck.h"
#include<stdio.h>
#include<assert.h>

void test_start(char* s){
  printf("%s\n",s);
}

int main(){
	struct tile_t tile1=CARC_TILE_GREEN;
	//struct tile_t tile2=CARC_TILE_EMPTY;
	struct tile_t tile3=CARC_TILE_INIT;  
	struct tile_t tile2=CARC_TILE_XROAD ;
	struct tile_t tile4=CARC_TILE_TINI;
	test_start("Checking colors");
	assert(check_compatible_colors(tile1,tile3,N,S)==1);
	assert(check_compatible_colors(tile1,tile3,S,N)==0);
	assert(check_compatible_colors(tile1,tile4,W,E)==0);
	assert(check_compatible_colors(CARC_TILE_GREEN,CARC_TILE_TINI,E,W)==0);
	printf("OK!\n");
	test_start("tests getting colors\n");
	test_start("test entire tile");
	enum color_t* c = get_tile_colors(&tile1);
	for(int i = 0;i<13;i++){
	  assert(c[i] == 0);
	}
	printf("OK!\n");
	test_start("test just a side");
	enum color_t* aSide = get_tile_side(&tile2,0); // 0 is North
	assert(aSide[0] == GREEN);
	assert(aSide[1] == GRAY);
	assert(aSide[2] == GREEN);
	
	printf("OK!\n");
	
	
	return 0;
}
