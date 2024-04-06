#include "tile.h"
#include "deck.h"
#include<stdio.h>

int main(){
	struct tile_t t=CARC_TILE_GREEN;
	enum color_t *color=get_tile_colors(&t);
	printf("%d  %d",*color,*(color+1));
	return 0;
}