#include "../player.h"
#include "playerStruct.h"

struct player_t player2;

char const* get_player_name()
	{
		return "Renault w9";
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

