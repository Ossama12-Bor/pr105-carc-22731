#include "board.h"
#include <stdlib.h>
#include <stdio.h>

#define NUM_TILES 72
#define NUM_TILE_TYPES 5
const struct tile_t TILE_TYPES = {CARC_TILE_EMPTY,
				  CARC_TILE_INIT,
				  CARC_TILE_GREEN,
				  CARC_TILE_XROAD,
				  CARC_TILE_TINI};

struct board_t{
  struct case_t t[2*NUM_TILES][2*NUM_TILES];
  struct case_t *empty;
  int size;
};
struct case_t *get_empty(struct board_t *board){
  return board->empty;
  
}
struct case__t get_cord(struct board_t board, int id){
  for (int i = 0; i< 2*NUM_TILES ; ++i){
    for (int j = 0 ; j < 2*NUM_TILES; ++j){
	if (t[i][j].id == id) return t[i][j];
      }
  }
  struct case__t c = {.x=-1,.y=-1,.id=-1,id_is_available=-1};
  return c;
}


struct deck_t* generate_deck(int n,int seed){
  struct deck_t* mydeck = deck_empty(NUM_TILES);
  srand(seed);
  for(int i=0;i<NUM_TILES;i++){
    deck_add(mydeck,TILE_TYPES[rand()%NUM_TILES]);
  }
  return mydeck;
}

int get_size_board(struct board_t *board){
  return board->size;
}

struct case_t* get_case(struct board_t* board,int x,int y){
  return &(board->t[x][y]);
}

void print_case(struct case_t* case_, char* prefix){
  printf("(%d,%d) has id %d",case_.x,case_.y,case_.id); 
}

void print_board(struct board_t* board, char* prefix){
  printf("%s\n",prefix);
  for(int x=0;x<2*NUM_TILES;x++){
    for(int y=0;y<2*NUM_TILES;y++){
      if(!is_empty(*get_case(board,x,y),board))
	print_case(get_case(board,x,y),"");
    }
  }
}
struct board_t *Initialize_board(){
	struct board_t *board=malloc(sizeof(*board));
	board->size=0;
	for(int i=0;i<NUM_TILES;i++){
		for(int j=0;j<NUM_TILES;j++){
			board->t[i][j].id=-1;
			board->t[i][j].x=-1;
			board->t[i][j].y=-1;	
		}
	}
	return board;
}
 
int add_tile(struct board_t *board,struct case_t coord ){
	board->t[coord.y][corrd.x]=coord.id;
	board->size+=1;
	return 1;
}

void free(struct board_t *board);

 
