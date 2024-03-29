#ifndef _PLAYER_STRUCT_H_
#define _PLAYER_STRUCT_H_

#include "player.h"

struct player_t{
  int player_id;
  struct deck_t* mydeck;
  unsigned int n_meeples;
  char* name;
};
/* Returns the player's id */
int get_player_id(struct player_t* p);

/* Returns the player's current # of meeples */
unsigned int get_player_meeples(struct player_t* p);

/* updates players*/
void update_player_deck(struct player_t* p);

/* displays a player's info*/
void display_player(struct player_t* p);

#endif //_PLAYER_STRUCT_H_
