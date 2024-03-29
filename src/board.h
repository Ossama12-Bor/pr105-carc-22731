#ifndef _BOARD_H_
#define _BOARD_H_

#include "player.h"
#include <igraph.h>
struct board_t board;
Initialize_board();
get_available_sides(board);
add_tile(board,struct tile_t t);
get__cord(Board, Tile);
is_empty(x,y,board);
free_board();
print_board();

#endif // _BOARD_H_
