#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

#define NUM_TILES 72
#define NUM_TILE_TYPES 5
const struct tile_t TILE_TYPES[] = {CARC_TILE_EMPTY,
				  CARC_TILE_INIT,
				  CARC_TILE_GREEN,
				  CARC_TILE_XROAD,
				  CARC_TILE_TINI};

struct board_t{
  struct case_t t[2*NUM_TILES][2*NUM_TILES];
  struct set *empty;
  int size;
};

void case_print(struct case_t box){
    printf("{%d,%d,%d,%d}",box.x,box.y,box.id,box.is_available_id);
}
struct set*get_empty(struct board_t *board){
  return board->empty;
  
}
struct case__t get_cord(struct board_t *board, int id){
  for (int i = 0; i< 2*NUM_TILES ; ++i){
    for (int j = 0 ; j < 2*NUM_TILES; ++j){
	if (board->t[i][j].id == id) return t[i][j];
      }
  }
  struct case__t c = {.x=-1,.y=-1,.id=-1,is_available_id=-1};
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

struct case_t get_case(struct board_t* board,int x,int y){
  return board->t[x][y];
}

void print_case(struct case_t case_, char* prefix){
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
void change_neighbours(struct board_t* board,struct case_t coord){
  int d[][] ={{-1,0},{1,0},{0,-1},{0,1}};
  int x = coord.x, y = coord.y;
  for(int i=0;i<4;i++){
    assert(x+d[i][0] >= 0 && x+d[i][0]<2*NUM_TILES &&
	   y+d[i][1] >= 0 && y+d[i][1]<2*NUM_TILES);
    struct case_t* case_ = get_case(board,x+d[i][0],y+d[i][1]);
    if (case_->is_available_id == 0) {
    case_->is_available_id = 1;
    // AddList(empty,case_) when list is impleme
    }
    }
  }
}
int add_tile(struct board_t *board,struct case_t coord ){
	board->t[coord.y][corrd.x]=coord;
	board->size+=1;
	change_neighbours(board,coord);
	// removeList(coord,get_empty(board))
	return 1;
}

void free(struct board_t *board);


