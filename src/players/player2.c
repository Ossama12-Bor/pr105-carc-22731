#include "playerStruct.h"
#include <assert.h>
struct player_t player;

char const* get_player_name(){
  return "ssuaG";
}
void initialize(enum player_color_t player_id, const struct move_t first_move,struct gameconfig_t config){
  
  player.player_id = player_id;
  player.myboard = initialize_board();
  player.config.deck = config.deck;  
  update_player_board(&player, first_move);
  if(config.mode == NO_MEEPLE){
    player.config.meeples = 0;
    player.config.mode = NO_MEEPLE;
    }
  else if(config.mode == INFINITE_MEEPLE){
    player.config.meeples = -1;
    player.config.mode = INFINITE_MEEPLE;
    }
  else{
    player.config.meeples = config.meeples;
    player.config.mode = FINITE_MEEPLE;
    }
  player.name = get_player_name();
}

struct move_t play(const struct move_t previous_move, const struct tile_t tile){
	
  if(player.player_id==BLACK ||(player.player_id==WHITE && board_size(player.myboard)!=1)){
    update_player_board(&player, previous_move);}
	
  struct pos_t* possible_pos = get_possible_moves(player.myboard, tile);
  assert(possible_pos != NULL);
  struct move_t move_to_play = {.player_id = player.player_id, .tile = tile, .x = (possible_pos[0].box)->x, .y = (possible_pos[0].box)->y, .meeple = NO_CONNECTION};
  update_player_board(&player, move_to_play);
  free(possible_pos);
  return move_to_play;

}

void finalize(){
  free_board(player.myboard);
  deck_free(player.config.deck);
}


