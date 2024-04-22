#include "graph.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>



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
  for(int i=0;i<NUM_TILES; i++)
    deck_add(mydeck, TILE_TYPES[rand() % NUM_TILE_TYPES]);
  return mydeck;
}

/* Board allocator */
struct board_t* allocate_board(){
  igraph_t* board_graph = malloc(sizeof(igraph_t));
  struct board_t* game_board = malloc(sizeof(struct board_t));
  game_board->g = board_graph;
  game_board->empty=set__empty();
  game_board->tiles=malloc(sizeof(struct pos_t)*NUM_TILES);
  return game_board;
}
/* Board initializer (game_board must be alloc before)*/
struct board_t *initialize_board(){
  struct board_t *game_board=allocate_board();
  struct case_t *first_case=malloc(sizeof(*first_case));
  first_case->x=0;
  first_case->y=0;
  first_case->neighbors=malloc(4*sizeof(int));
  for(int i=0;i<4;i++){
	first_case->neighbors[i]=-1;
  }
  set__add_head(game_board->empty,first_case,0,-1);
  game_board->size=0;
  igraph_empty(game_board->g,0,IGRAPH_UNDIRECTED);
  //initialize_neighbors(game_board->tiles);
  return game_board;
}

void change_neighbours(struct board_t* board,int id_in_empty){
  int d[4][2] ={{0,1},{1,0},{0,-1},{-1,0}};
  struct lelement *current_lelement=get_lelement_from_empty(board->empty,id_in_empty);
  struct case_t *boxes[4]={NULL,NULL,NULL,NULL};
  int count=0;
  for(int i=0;i<4;i++){
    if(current_lelement->data->neighbors[i]==-1){
    boxes[count]=malloc(sizeof(struct case_t));
    boxes[count]->x=current_lelement->data->x+d[i][0];
    boxes[count]->y=current_lelement->data->y+d[i][1];
	  boxes[count]->neighbors=malloc(sizeof(int)*4);
    for(int k=0;k<4;k++){
	  
      boxes[count]->neighbors[k]=-1;
    }
    set__add_head(board->empty,boxes[count],(i+2)%4,board->size);
    count++;
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
  struct pos_t *new_empty=malloc(sizeof(struct pos_t)*set_size(board->empty));
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
  new_empty=realloc(new_empty,sizeof(struct pos_t)*count);
  return new_empty;

}

struct case_t *get_optimal_case(struct board_t *board,int id_in_Type){
	struct pos_t *avail_positions=get_possible_moves(board,id_in_Type);
  struct pos_t avail_pos;
  if(avail_positions != NULL){
    avail_pos=avail_positions[0];
    free(avail_positions);}
  else{
    avail_pos.type_id = 0;
    avail_pos.box= get_data(get_head(board->empty));
  }
    struct case_t *optimal_tile=avail_pos.box;
    board->g=add_tile_to_graph(board->g,TILE_TYPES[id_in_Type],optimal_tile->neighbors,board->size);
	  change_neighbours(board,avail_pos.type_id);
	return optimal_tile;  
}

void add_tile(struct board_t *board,int id_tile){
	
	struct case_t *box= get_optimal_case(board,id_tile);
	board->tiles[board->size].type_id=id_tile;
  board->tiles[board->size].box=box;
  board->size+=1;
}

/* Frees the allocated memory for a board */
void free_board(struct board_t* game_board){
  for(int i=0;i<game_board->size;i++){
    free(game_board->tiles[i].box->neighbors);
    free(game_board->tiles[i].box);
  }
  free(game_board->tiles);
  free_set(game_board->empty);
  igraph_destroy(game_board->g);
  free(game_board->g);
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
  printf("%s :\n size:%d\n,tiles:[",prefix,board->size);
  for(int i=0;i<board->size;i++){
    printf("{%d",board->tiles[i].type_id);
    print_case(board->tiles[i].box);
    printf("}");
  }
  printf("]\n");
  set_print(board->empty,"empty:");
  


}
int board_size(struct board_t*board){
	return board->size;
}

struct set*get_board_empty(struct board_t*board){
	return board->empty;
}
struct pos_t *get_board_tiles(struct board_t *board){
	return board->tiles;
}