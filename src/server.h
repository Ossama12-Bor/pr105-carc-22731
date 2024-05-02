#ifndef _SERVER_H_
#define _SERVER_H_

#include "board.h"

struct board_t* game_board;
struct deck_t* game_deck;

/* initializes the board,deck  */
void initialize_server(int seed);

/* plays the first move and returns it for players*/
struct move_t play_first_move();

/* THE game loop with the given mode*/
void run_game(enum gamemode_t mode);

/* frees what has to be freed (board, deck ...)*/
void finalize_server();



#endif // _SERVER_H_
