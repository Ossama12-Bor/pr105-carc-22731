#include "../player.h"
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
		player1.myboard =deck_copy(config.deck);
		player1.name=get_player_name();




	}
