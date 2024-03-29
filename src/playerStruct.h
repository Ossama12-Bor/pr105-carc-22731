#ifndef _PLAYER_STRUCT_H_
#define _PLAYER_STRUCT_H_

#include "player.h"
#include "board.h"

/* Structure to manipulate a player */
struct player_t{
  int player_id;
  struct board_t* myboard;
  unsigned int n_meeples;
  char* name;
  int score;
};

/* Returns the player's id */
int get_player_id(struct player_t* p);

/* Returns the player's current # of meeples */
unsigned int get_player_meeples(struct player_t* p);

/* updates players*/
void update_player_board(struct player_t* p,struct move_t m);

/* displays a player's info*/
void display_player(struct player_t* p);

#endif //_PLAYER_STRUCT_H_
