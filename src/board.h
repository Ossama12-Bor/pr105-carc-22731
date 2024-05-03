#ifndef _BOARD_H_
#define _BOARD_H_
#define NUM_TILES 72
#include "move.h"
#include "liste.h"
//#include <igraph.h>

struct board_t;

extern struct tile_t TILE_TYPES[];

struct case_t {
  int x,y;
  int *neighbors;
};

struct pos_t{
  int type_id;
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

#endif // _BOARD_H_
