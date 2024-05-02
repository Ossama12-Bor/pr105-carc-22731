#include "playerStruct.h"
#include <assert.h>
struct player_t player;

char const* get_player_name(){
  return "ssuaG";
}

void initialize(enum player_color_t player_id, const struct move_t first_move,struct gameconfig_t config){
  
  player.player_id = player_id;
  update_player_board(&player, first_move);
  player.score = 0;
  if(config.mode == NO_MEEPLE)
    player.n_meeples = 0;
  else if(config.mode == INFINITE_MEEPLE)
    player.n_meeples = -1;
  else
    player.n_meeples = config.meeples;
  player.name = get_player_name();
}

struct move_t play(const struct move_t previous_move, const struct tile_t tile){
  update_player_board(&player, previous_move);
  struct pos_t* possible_pos = get_possible_moves(player.myboard, tile);
  assert(possible_pos != NULL);
  struct move_t move_to_play = {.player_id = player.player_id, .tile = tile, .x = (possible_pos[0].box)->x, .y = (possible_pos[0].box)->y, .meeple = NO_CONNECTION};
  return move_to_play;
}

void finalize(){
  return;
}


