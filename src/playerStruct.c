#include "playerStruct.h"
#include <stdio.h>

int get_player_id(struct player_t* p){
  return p->player_id;
}

unsigned int get_player_meeples(struct player_t* p){
  return p->n_meeples;
}

void update_player_board(struct player_t* p,struct move_t m){
  make_move(p->myboard, m);
}

void display_player(struct player_t* p){
  printf("--Player : %s--\n",p->name); /*get_player_name()*/
  printf("Player id : %d\n",get_player_id(p));
  printf("Meeples left : %d\n",get_player_meeples(p));
  //printf("Personal Board : \n");
  //display_player_board(p);
  printf("--------------");/*fix number of - after*/
}


