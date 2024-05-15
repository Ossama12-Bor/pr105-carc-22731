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
 if (m.meeple != NO_CONNECTION){
    add_meeple(get_graph(p->myboard), (board_size(p->myboard)-1)*13 + m.meeple, p->player_id);
    if (p->mode == FINITE_MEEPLE){
      p->n_meeples += retrieve_meeples(get_graph(p->myboard), board_size(p->myboard)-1, p->player_id);
      p->n_meeples--;
      printf("\nn_meeples == %d\n",p->n_meeples);
    }
    if (p->mode == INFINITE_MEEPLE){
      printf("r = %d\n",retrieve_meeples(get_graph(p->myboard), board_size(p->myboard)-1, p->player_id));    
    }
 }
 }

void display_player(struct player_t* p){
  printf("--Player : %s--\n",p->name); /*get_player_name()*/
  printf("Player id : %d\n",get_player_id(p));
  printf("Meeples left : %d\n",get_player_meeples(p));
  //printf("Personal Board : \n");
  //display_player_board(p);
  printf("--------------\n");/*fix number of - after*/
}


