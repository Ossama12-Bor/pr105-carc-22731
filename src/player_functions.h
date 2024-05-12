#ifndef __PLAYER_FUNCTIONS_H__
#define __PLAYER_FUNCTIONS_H__

#include "graph.h"
#include "board.h"

//no meeple functions

struct move_t *get_optimal_position_no_meeple(struct board_t *board, struct tile_t t, int player_id);


struct move_t *get_biggest_open_road_component(struct board_t *board, struct tile_t t, int player_id, enum gamemode_t mode, int n_meeples);


struct move_t *get_biggest_finished_component(struct board_t *board, struct tile_t t, int player_id, enum color_t color, int n_meeples,enum gamemode_t mode);

struct move_t *get_a_position_where_there_is_no_meeple(struct board_t *board, struct tile_t t, int player_id);

struct move_t *get_random_possible_position(struct board_t *board, struct tile_t t, int player_id);

#endif
