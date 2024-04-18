#ifndef _BOARD_H_
#define _BOARD_H_

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
  struct case_t box;
}


/*struct deck_t*generate_deck(int seed);

struct board_t *Initialize_board();

//Get empty cases where we are allowed to add new cases

struct case_t get_empty_sides(struct board_t *board);

int correct_pasting(struct board_t*board,struct tile_t tile,struct case_t coord);

//Same but only cases matching the tile : id

struct case_t *get_possible_moves(struct board_t*board,struct tile_t tile);



//Get the case of coordinates (x,y) in the board

struct case_t get_case(struct board_t* board,int x,int y);

//Get how many tiles are there in the board

int get_size_board(struct board_t *board);


//adjust the field of the is_available_id of the empty adjacent cases to coord

void change_neighbours(struct board_t* board,int id_in_empty);


void add_tile(struct board_t *board, int id_tile);

struct case_t get_cord(struct board_t *board, int id);

int is_empty(struct case_t case_,struct board_t* board);

void free_board(struct board_t* board);

void print_case(struct case_t box);

void print_board(struct board_t *board,char* prefix);*/

#endif // _BOARD_H_
