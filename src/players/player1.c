#include "playerStruct.h"

struct player_t player1;

char const* get_player_name()
	{
		return "Aymane";
	}

void initialize(unsigned int player_id, const struct move_t first_move,
                struct gameconfig_t config)
	{
		player1.player_id=player_id;
		player1.myboard=add_board(board,first_move);
		player1.score=0;
		player1.n_meeples=0;
		player1.name=get_player_name();

	}

struct move_t play(const struct move_t previous_move, const struct tile_t tile);

void finalize(){
	free(player1.gamemode);
}


