#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "liste.h"
#include "tile.h"
#include "deck.h"
#define NUM_TILES 72
#define NUM_TILE_TYPES 5
const struct tile_t TILE_TYPES[] = {CARC_TILE_EMPTY,
				  CARC_TILE_INIT,
				  CARC_TILE_GREEN,
				  CARC_TILE_XROAD,
				  CARC_TILE_TINI};


struct board_t{
  struct case_t t[2*NUM_TILES-1][2*NUM_TILES-1];
  struct set *empty;
  int size;
};



/*this function generate game deck*/
struct deck_t* generate_deck(int seed){
  struct deck_t* mydeck = deck_empty(NUM_TILES);
  srand(seed);
  for(int i=0;i<NUM_TILES;i++){
    deck_add(mydeck,TILE_TYPES[rand()%NUM_TILES]);
  }
  return mydeck;
}




struct board_t *Initialize_board(){
	struct board_t *board=malloc(sizeof(*board));
	board->size=0;
	for(int i=0;i<NUM_TILES;i++){
		for(int j=0;j<NUM_TILES;j++){
			board->t[i][j].id=-1;
			board->t[i][j].x=j;
			board->t[i][j].y=i;
      board->t[i][j].is_available_id=0;	
		}
	}
  board->t[NUM_TILES-1][NUM_TILES-1].is_available_id=1;
  board->empty=set__empty();
  set__add(board->empty,board->t[NUM_TILES-1][NUM_TILES-1]);
	return board;
}





struct case_t get_cord(struct board_t *board, int id){
  for (int i = 0; i< 2*NUM_TILES ; ++i){
    for (int j = 0 ; j < 2*NUM_TILES; ++j){
	    if (board->t[i][j].id == id) return board->t[i][j];
      }
  }
  struct case_t c = {.x=-1,.y=-1,.id=-1,.is_available_id=-1};
  return c;
}




int is_empty_case(struct case_t box){
  return box.id==-1;
}



struct case_t get_case(struct board_t *board,int x,int y){
  return board->t[x][y];
}





void print_board(struct board_t* board, char* prefix){
  printf("%s\n",prefix);
  for(int x=0;x<2*NUM_TILES;x++){
    for(int y=0;y<2*NUM_TILES;y++){
      if(!is_empty_case(get_case(board,x,y)))
	          print_case(get_case(board,x,y));
    }
  }
}
int borders(struct case_t coord,int d[]){
  if(coord.x+d[0] >= 0 && coord.x+d[0]<2*NUM_TILES-1 &&
	   coord.y+d[1] >= 0 && coord.y+d[1]<2*NUM_TILES-1)
     return 1;
  return 0;
}


void change_neighbours(struct board_t* board,int id){
  int d[4][2] ={{-1,0},{1,0},{0,-1},{0,1}};
  struct case_t current_case=get_case_array(board->empty)[id];
  for(int i=0;i<4;i++){
    if(borders(current_case,d[i])){
      struct case_t box = get_case(board,current_case.x+d[i][0],current_case.y+d[i][1]);
      if (box.is_available_id == 0) {
        box.is_available_id = 1;
        set__add(board->empty,box);
      }
    }
  }
  board->t[current_case.y][current_case.x].is_available_id=0;
  set__remove(board->empty,id);
}

int correct_pasting(struct board_t* board, const struct deck_t* deck, struct tile_t tile, struct case_t coord) {
  int d[4][2] = {{0, 1}, {0, 1}, {0, -1}, {-1, 0}};
  for (int i = 0; i < 4; i++) {
    if (borders(coord, d[i])) {
      int x = coord.x + d[i][0], y = coord.y + d[i][1];
      if (!is_empty_case(board->t[y][x]) &&
          !check_compatible_colors(tile, deck_get(deck, get_case(board, x, y).id), i, (i + 2) % 4)) {
        return 0;
      }
    }
  }
  return 1;
}
struct case_t *get_possible_moves(struct board_t*board,const struct deck_t *deck,struct tile_t tile){
  struct case_t *new_empty;
  int count=0;
  for(int i=0;i<set_size(board->empty);i++){
    struct case_t box=get_case_array(board->empty)[i];
    if(correct_pasting(board,deck,tile,box)){
      *(new_empty+count)=box;
      count++;
    }
  }
  return new_empty;

}



/*int add_tile(struct board_t *board,struct case_t coord ){
	board->t[coord.y][coord.x]=coord;
	board->size+=1;
	change_neighbours(board,coord);
	// removeList(coord,get_empty(board))
	return 1;
}




void free_board(struct board_t *board);


void print_case(struct case_t box){
  printf("{%d,%d,%d,%d}",box.x,box.y,box.id,box.is_available_id); 
}*/