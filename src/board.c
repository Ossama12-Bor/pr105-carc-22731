#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "liste.h"
#include "tile.h"
#include "move.h"
#define NUM_TILES 72
#define NUM_TILE_TYPES 4

struct tile_t TILE_TYPES[] = {CARC_TILE_INIT,
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
    deck_add(mydeck,TILE_TYPES[rand()%NUM_TILE_TYPES]);
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
  set__add_head(board->empty,&board->t[NUM_TILES-1][NUM_TILES-1]);
	return board;
}





/*struct case_t get_cord(struct board_t *board, int id){
  for (int i = 0; i< 2*NUM_TILES ; ++i){
    for (int j = 0 ; j < 2*NUM_TILES; ++j){
	    if (board->t[i][j].id == id) return board->t[i][j];
      }
  }
  struct case_t c = {.x=-1,.y=-1,.id=-1,.is_available_id=-1};
  return c;
}*/




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

void change_neighbours(struct board_t* board,int id_in_empty){
  int d[4][2] ={{-1,0},{1,0},{0,-1},{0,1}};
  struct lelement *current_lelement=get_lelement_from_empty(board->empty,id_in_empty);
  for(int i=0;i<4;i++){
    if(borders(*current_lelement->data,d[i])){
      struct case_t box = get_case(board,current_lelement->data->x+d[i][0],current_lelement->data->y+d[i][1]);
      if (box.is_available_id == 0) {
        box.is_available_id = 1;
        set__add_head(board->empty,&box);
      }
    }
  }
  board->t[current_lelement->data->y][current_lelement->data->x].is_available_id=0;
  set__remove(board->empty,current_lelement);
}

int correct_pasting(struct board_t* board,struct tile_t tile, struct case_t coord) {
  int d[4][2] = {{0, 1}, {0, 1}, {0, -1}, {-1, 0}};
  for (int i = 0; i < 4; i++) {
    if (borders(coord, d[i])) {
      int x = coord.x + d[i][0], y = coord.y + d[i][1];
      if (!is_empty_case(board->t[y][x]) &&
          !check_compatible_colors(tile, TILE_TYPES[board->t[y][x].id], i, (i + 2) % 4)) {
        return 0;
      }
    }
  }
  return 1;
}
struct case_t *get_possible_moves(struct board_t*board,struct tile_t tile){
  struct case_t *new_empty=NULL;
  int count=0;
  for(int i=0;i<set_size(board->empty);i++){
    struct lelement *box=get_lelement_from_empty(board->empty,i);
    if(correct_pasting(board,tile,*(box->data))){
		box->data->id-=i-NUM_TILES;
      	*(new_empty+count)=*box->data;
      	count++;
    }
  }
  return new_empty;

}

struct case_t get_optimal_case(struct board_t *board,struct tile_t tile){
	struct case_t first_case = get_possible_moves(board,tile)[0];
	change_neighbours(board,first_case.id+NUM_TILES);
	return first_case;  
}

void add_tile(struct board_t *board,int id_tile){
	board->size+=1;
	struct case_t box= get_optimal_case(board,TILE_TYPES[id_tile]);
	board->t[box.y][box.x].id=id_tile;
}




void free_board(struct board_t *board){
	free_set(board->empty);
	free(board);
}


void print_case(struct case_t box){
  printf("{%d,%d,%d,%d}",box.x,box.y,box.id,box.is_available_id); 
}

