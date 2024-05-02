#include "player.h"
#include "playerStruct.h"
#include <assert.h>

struct player_t player2;

char const* get_player_name()
	{
		return "freePl";
	}

void initialize(unsigned int player_id, const struct move_t first_move,
                struct gameconfig_t config)
	{
		player2.player_id=player_id;
		player2.gamemode.mode=config.mode;
        player2.gamemode.meeples=config.meeples;
        player2.gamemode.deck=deck_copy(config.deck);
		player2.name=get_player_name();
    }

struct move_t play(const struct move_t previous_move, const struct tile_t tile){
  update_player_board(&player2, previous_move);
  struct pos_t* possible_pos = get_possible_moves(player2.myboard, tile);
  assert(possible_pos != NULL);
  struct move_t move_to_play = {.player_id = player2.player_id, .tile = tile, .x = (possible_pos[0].box)->x, .y = (possible_pos[0].box)->y, .meeple = NO_CONNECTION};
  update_player_board(&player2,move_to_play);
  return move_to_play;
}

void finalize(){
  free_board(player2.myboard);
}