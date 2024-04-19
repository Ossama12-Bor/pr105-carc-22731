#ifndef _BOARD_H_
#define _BOARD_H_
#define NUM_TILES 72
#include "move.h"
#include "liste.h"
//#include <igraph.h>
struct board_t;


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



int correct_pasting(struct board_t* board,struct tile_t tile, int id_in_empty);

//Same but only cases matching the tile : id

struct pos_t*get_possible_moves(struct board_t*board,int id_in_Type);


struct case_t *get_optimal_case(struct board_t *board,int id_in_Type);
//Get the case of coordinates (x,y) in the board

void add_tile(struct board_t *board,int id_tile);

//Get how many tiles are there in the board

int get_size_board(struct board_t *board);


//adjust the field of the is_available_id of the empty adjacent cases to coord

void free_board(struct board_t* board);

void print_case(struct case_t *box);

void print_board(struct board_t *board,char* prefix);

#endif // _BOARD_H_
