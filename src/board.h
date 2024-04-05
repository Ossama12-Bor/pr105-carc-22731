#ifndef _BOARD_H_
#define _BOARD_H_

#include "player.h"
#include <igraph.h>
struct board_t;

struct case_t{
  int x,y,id,is_available_id;
};
  
struct deck_t*generate_deck(int seed);

struct board_t *Initialize_board();

struct case_t *get_empty_sides(struct board_t *board);

struct case_t*get_possible_moves(struct board_t*board,int id);


struct case_t *get_case(struct board_t* board,int x,int y);

int get_size_board(struct board_t *board);

int add_tile(struct board_t *board, int id, struct case_t case_);

struct case_t get_cord(struct board_t board,int id );

int is_empty(struct case_t case_,struct board_t* board);

void free_board(struct board_t* board);

void print_case(struct case_t* case_,char* prefix);

void print_board(struct board_t *board,char* prefix);

#endif // _BOARD_H_
