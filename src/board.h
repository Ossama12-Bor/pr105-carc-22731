#ifndef _BOARD_H_
#define _BOARD_H_
#define NUM_TILES 72
#include "move.h"
#include "graph.h"
#include "liste.h"

#include <igraph.h>

 // adding some new tiles 
#define CARC_V_CASTLE  ((struct tile_t) { .t={0,0,0,1,1,1,2,2,2,2,2,2,2}, \
                              .c={BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,   \
                                  GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN}})

#define CARC_SOLO_ROAD  ((struct tile_t) { .t={0,0,0,0,1,2,2,2,2,2,1,0,1}, \
                              .c={GREEN,GREEN,GREEN,GREEN,GRAY,GREEN,   \
                                  GREEN,GREEN,GREEN,GREEN,GRAY,GREEN,GRAY}})

#define CARC_TOWN_3ROAD  ((struct tile_t) { .t={0,0,0,0,1,2,2,3,4,4,5,0,6}, \
                              .c={GREEN,GREEN,GREEN,GREEN,GRAY,GREEN,   \
                                  GREEN,GRAY,GREEN,GREEN,GRAY,GREEN,PURPLE}})
                          
#define CARC_CURVED_ROAD  ((struct tile_t) { .t={0,0,0,0,1,2,2,1,0,0,0,0,1}, \
                              .c={GREEN,GREEN,GREEN,GREEN,GRAY,GREEN,   \
                                  GREEN,GRAY,GREEN,GREEN,GREEN,GREEN,GRAY}})

#define CARC_PIZZA  ((struct tile_t) { .t={0,0,0,0,0,0,1,1,1,1,1,1,0}, \
                              .c={BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,   \
                                  GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,BROWN}})
                        
#define CARC_SOLO_CASTLE  ((struct tile_t) { .t={0,0,0,1,1,1,1,1,1,1,1,1,1}, \
                              .c={BROWN,BROWN,BROWN,GREEN,GREEN,GREEN,   \
                                  GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN}})


struct board_t; // board structure 

extern struct tile_t TILE_TYPES[]; // declared extern in order to use it in other files


struct case_t {
  int x,y; // position (x,y)
  int *neighbors; // array of neighbors ids (NORTH,EAST,SOUTH,WEST)
};

/* it gives the tile status*/
struct status {
  int type_id; // from 1 to 10
  int rotation; // from 0 to 3
};
struct pos_t{
  struct status status;
  struct case_t *box;
};

int board_size(struct board_t*board);
struct deck_t*generate_deck(int seed);

struct board_t* allocate_board();

void initialize_neighbors(struct pos_t * tiles);

struct board_t *initialize_board();

void change_neighbours(struct board_t* board,int id_in_empty);

//Get empty cases where we are allowed to add new cases
int empty_tile(struct tile_t t);


int correct_pasting(struct board_t* board,struct tile_t tile, int id_in_empty);

//Same but only cases matching the tile : id

struct pos_t*get_possible_moves(struct board_t*board,struct tile_t tile);

int get_size_possible_moves(struct pos_t * possible_moves);
//struct case_t *get_optimal_case(struct board_t *board,int id_in_Type);
//Get the case of coordinates (x,y) in the board

void add_tile(struct board_t *board,struct tile_t tile,struct pos_t optimal_pos);

//change board by making  a move

void make_move(struct board_t *board,struct move_t move);

//check if the move that was made is correct or not 
 
int is_correctly_played(struct board_t *board,struct move_t move);

//Get how many tiles are there in the board

int get_size_board(struct board_t *board);


void free_board(struct board_t* board);

void print_case(struct case_t *box);

void print_board(struct board_t *board,char* prefix);

struct pos_t *get_board_tiles(struct board_t *board);

struct set*get_board_empty(struct board_t*board);

igraph_t * get_graph(struct board_t *board);

#endif // _BOARD_H_
