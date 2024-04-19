
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include "liste.h"
#include "tile.h"
#include "move.h"
#include <igraph.h>
#define NUM_TILES 72
#define NUM_TILE_TYPES 4

struct tile_t TILE_TYPES[] = {CARC_TILE_INIT,
				  CARC_TILE_GREEN,
				  CARC_TILE_XROAD,
				  CARC_TILE_TINI};



struct board_t{
  igraph_t* g;
  struct pos_t* tiles;
  int size;
  struct set *empty;
};

/* Deck generator */
struct deck_t* generate_deck(int seed){
  srand(seed);
  struct deck_t* mydeck = deck_empty(NUM_TILES);
  for(int i=0; i<NUM_TILES; i++)
    deck_add(mydeck, TILE_TYPES[rand() % NUM_TILE_TYPES]);
  return mydeck;
}

/* Board allocator */
struct board_t* allocate_board(){
  igraph_t* board_graph = malloc(sizeof(igraph_t));
  struct board_t* game_board = malloc(sizeof(struct board_t));
  game_board->g = board_graph;
  game_board->empty=set__empty();
  game_board->tiles=malloc(sizeof(struct pos_t )*NUM_TILES);
  return game_board;
}

void initialize_neighbors(struct pos_t * tiles){
  for(int i=0;i<NUM_TILES;i++){
    for(int j=0;j<4;j++){
      tiles[i].box->neighbors[j]=-1;
      tiles[i].type_id=-1;
    }
  }
}

/* Board initializer (game_board must be alloc before)*/
void initialize_board(struct board_t* game_board){
  int t[4]={-1,-1,-1,-1};
  struct case_t *first_case=malloc(sizeof(*first_case));
  first_case->x=0;
  first_case->y=0;
  first_case->neighbors=t;
  set__add_head(game_board->empty,first_case,0,-1);
  game_board->size=0;
  igraph_empty(game_board->g,0,IGRAPH_UNDIRECTED);
  initialize_neighbors(game_board->tiles);
}

void change_neighbours(struct board_t* board,int id_in_empty){
  int d[4][2] ={{0,1},{1,0},{0,-1},{-1,0}};
  struct lelement *current_lelement=get_lelement_from_empty(board->empty,id_in_empty);
  for(int i=0;i<4;i++){
    if(current_lelement->data->neighbors[i]==-1){
    struct case_t *box=malloc(sizeof(struct case_t));
    box->x=current_lelement->data->x+d[i][0];
    box->y=current_lelement->data->y+d[i][1];
    for(int k=0;k<4;k++){
      box->neighbors[k]=-1;
    }
    set__add_head(board->empty,box,(i+2)%4,board->size);
    }
    else{
      board->tiles[current_lelement->data->neighbors[i]].box->neighbors[(i+2)%4]=board->size;
    }
  }
  set__remove(board->empty,current_lelement);
}

int correct_pasting(struct board_t* board,struct tile_t tile, int id_in_empty) {
  struct lelement*elt=get_lelement_from_empty(board->empty, id_in_empty);
  for (int i = 0; i < 4; i++) {
    int tile_id=get_ith_neighbor(elt,i);
      if (tile_id!=-1 && !check_compatible_colors(tile, TILE_TYPES[board->tiles[tile_id].type_id], i, (i + 2) % 4)) {
        return 0;
    
    }
  }
  return 1;
}

struct pos_t*get_possible_moves(struct board_t*board,int id_in_Type){
  struct pos_t *new_empty=NULL;
  int count=0;
  struct lelement *first=get_head(board->empty);
  int size=set_size(board->empty);
  for(int i=0;i<size;i++){
    if(correct_pasting(board,TILE_TYPES[id_in_Type],i)){
      	(new_empty+count)->type_id=i; //on stocke les indices des positions disponibles de empty dans new_empty
        (new_empty+count)->box=get_data(first);
      	count++;
    }
    first=first->next;
  }
  return new_empty;

}

struct case_t *get_optimal_case(struct board_t *board,int id_in_Type){
	struct pos_t avail_pos=get_possible_moves(board,id_in_Type)[0];
  struct case_t *optimal_tile=avail_pos.box;
	change_neighbours(board,avail_pos.type_id);
	return optimal_tile;  
}

void add_tile(struct board_t *board,int id_tile){
	
	struct case_t *box= get_optimal_case(board,id_tile);
	board->tiles[board->size].type_id=board->size;
  board->tiles[board->size].box=box;
  board->size+=1;
}

/* Frees the allocated memory for a board */
void free_board(struct board_t* game_board){
  igraph_destroy(game_board->g);
  free(game_board->tiles);
  free_set(game_board->empty);
  free(game_board);
}
int get_size_board(struct board_t*board){
  return board->size;
}

void print_case(struct case_t *box){
  printf("{(%d,%d),{",box->x,box->y);
  for(int i=0;i<3;i++)
    printf("%d,",box->neighbors[i]);
  printf("%d}}",box->neighbors[3]);
}

void print_board(struct board_t *board,char* prefix){
  printf("%s :\n size:%d,tiles:[",prefix,board->size);
  for(int i=0;i<board->size;i++){
    printf("{%d",board->tiles[i].type_id);
    print_case(board->tiles[i].box);
    printf("}");
  }
  printf("]");
  set_print(board->empty,"empty:");
  


}