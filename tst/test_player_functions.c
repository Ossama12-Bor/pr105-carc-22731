
#include "test_player_functions.h"


void test_player(){
  struct board_t *board;
  struct deck_t *deck;
  deck = generate_deck(42);
  board = initialize_board();
//  struct tile_t first_tile = deck_get(deck, 0);
  struct move_t move_1 = {.player_id = -1, .x = 0, .y = 0, .tile = CARC_TILE_INIT, .meeple = NO_CONNECTION};
  make_move(board, move_1);
//  struct move_t move_2 = {.player_id = -1, .x = 0, .y = 1, .tile = CARC_TILE_TINI, .meeple = NO_CONNECTION};
  //struct pos_t* possible_moves = get_possible_moves(board, CARC_TILE_INIT);
 struct move_t *move_2 = get_optimal_position_no_meeple(board, CARC_TILE_INIT,-1);
 assert(move_2 != NULL);
  make_move(board, *move_2);
  free(move_2);
 struct move_t *move_3_false = get_optimal_position_no_meeple(board, CARC_TILE_XROAD,-1);
// printf("%d\n",move_3->x);
 assert(move_3_false == NULL);
  struct move_t move_3 = {.player_id = -1, .x = 1, .y = 1, .tile = CARC_TILE_XROAD, .meeple = NO_CONNECTION};
  make_move(board, move_3);
 struct move_t *move_4 = get_optimal_position_no_meeple(board, CARC_TILE_XROAD,-1);
 assert(move_4 != NULL);
  make_move(board, *move_4);
  free(move_4);
  struct move_t *move_5 = get_biggest_open_road_component(board, CARC_TILE_XROAD, -1, NO_MEEPLE,7,GRAY);
 assert(move_5 != NULL);
  make_move(board, *move_5);
  free(move_5);
 struct move_t *move_6 = get_optimal_position_no_meeple(board, flip_tile(CARC_TILE_XROAD,1),-1);
 assert(move_6 != NULL);
  make_move(board, *move_6);
  free(move_6);
 add_meeple(get_graph(board),72,0);
 struct move_t *move_7 = get_biggest_finished_component(board, CARC_TILE_XROAD,0, GRAY,6,FINITE_MEEPLE);
 assert(move_7 != NULL);
 make_move(board, *move_7);
 free(move_7); 
 add_meeple(get_graph(board),85,1);
 struct move_t *move_8 = get_biggest_finished_component(board, CARC_TILE_XROAD,1, GRAY,0,FINITE_MEEPLE);
 assert(move_8 != NULL);
  make_move(board, *move_8);
 free(move_8);  
  add_meeple(get_graph(board),95,1);
 struct move_t *move_9 = get_biggest_finished_component(board, CARC_TILE_XROAD,1, GRAY,4,FINITE_MEEPLE);
 assert(move_9 != NULL);
  make_move(board, *move_9);
 free(move_9);  
  struct move_t *move_10 = get_a_position_where_there_is_no_meeple(board, CARC_TILE_GREEN,1);
  assert(move_10 != NULL);
  make_move(board, *move_10);
 free(move_10);
  add_meeple(get_graph(board),14,1);
  struct move_t *move_11 = get_a_position_where_there_is_no_meeple(board, CARC_TILE_GREEN,1);
  assert(move_11 == NULL);
  
  
  
 
  
  display_graph(get_graph(board), "test.dot");
  free_board(board);
  deck_free(deck);
}

