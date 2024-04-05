#ifndef _BOARD_H_
#define _BOARD_H_

#include "player.h"
#include <igraph.h>
struct board_t;
struct case_t{
	int x,y,id;
}
struct board_t *Initialize_board();

struct case_t *get_available_sides(struct board_t *board);

int add_tile(struct board_t *board,struct tile_t t,struct case_t coord );                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    );
struct case_t get_cord(struct board_t board,int id );
int is_empty(struct case_t case,struct board_t* board);
void free_board(struct board_t* board);
void print_board(struct board_t *board,char* prefix);

#endif // _BOARD_H_
