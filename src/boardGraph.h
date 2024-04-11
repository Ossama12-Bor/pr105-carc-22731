#ifndef _BOARD_GRAPH_H_
#define _BOARD_GRAPH_H_

#include "player.h"
#include <igraph.h>

/* Struct representing a board */
struct board_t;

/* Deck generator */
void generate_deck(struct deck_t* game_deck);

/* Board allocator */
struct board_t* allocate_board();

/* Board Initializer */
void initialize_board(struct board_t* game_board);

/* Makes a move, and updates board */
void make_move(struct board_t* game_board,struct move_t m);

/* Frees the allocated memory for a board */
void free_board(struct board_t* game_board);
 

#endif // _BOARD_GRAPH_H_
