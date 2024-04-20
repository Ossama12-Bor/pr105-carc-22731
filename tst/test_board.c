#include "board.h"
#include "assert.h"
#include <stdio.h>


void test_board(void){
  struct deck_t *deck = generate_deck(42);
  assert(deck_size(deck) == NUM_TILES);
  struct board_t *board = initialize_board();

  assert(board_size(board)==0);
  assert(set_size(get_board_empty(board))==1);
  add_tile(board,0);
  assert(board_size(board)==1);
  print_board(board,"myboard");
  add_tile(board,1);
  print_board(board,"my beautiful board");


  /*for (int i = 0; i < 2*NUM_TILES-1; ++i){
    for (int j = 0 ; j < 2*NUM_TILES-1; ++j){
      assert(is_empty_case(board->t[i][j]));
      assert(board->t[i][j].id_is_available == -1);
	     }
  }
  assert(board->empty->size == 0);
  change_neigbours(board, 0);
  assert(board->t[NUM_TILES-1][NUM_TILES-1].is_available_id == 0); 
  assert(board->t[NUM_TILES][NUM_TILES-1].is_available_id == 1);
  assert(board->t[NUM_TILES-1][NUM_TILES].is_available_id == 1);
  assert(board->t[NUM_TILES-2][NUM_TILES-1].is_available_id == 1);
  assert(board->t[NUM_TILES-1][NUM_TILES-2].is_available_id == 1);
  struct tile_t tile = CARC_TILE_EMPTY;
  assert(correct_pasing(board,tile, board->t[NUM_TILES-1][NUM_TILES-1]));
  board->t[NUM_TILES-1][NUM_TILES-1].id = 0;*/
  printf("all tests passed\n");
}
int main(){
  test_board();
  return 0;
}
	
	
