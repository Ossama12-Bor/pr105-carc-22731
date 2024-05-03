#include "board.h"
#include "assert.h"
#include <stdio.h>


void test_board(void){
  /*struct deck_t *deck = generate_deck(42);
  assert(deck_size(deck) == NUM_TILES);*/
  struct board_t *board = initialize_board();
  print_board(board,"myboard");

  /*assert(board_size(board)==0);
  assert(set_size(get_board_empty(board))==1);*/
  struct pos_t *pos1=get_possible_moves(board,TILE_TYPES[0]);
  add_tile(board,TILE_TYPES[0],pos1[0]);
  assert(board_size(board)==1);
  print_board(board,"myboard");
  struct pos_t *pos2=get_possible_moves(board,TILE_TYPES[1]);
  add_tile(board,TILE_TYPES[1],pos2[0]);
  print_board(board,"my beautiful board");
  
  struct pos_t *pos3=get_possible_moves(board,TILE_TYPES[1]);
 add_tile(board,TILE_TYPES[1],pos3[0]);
  print_board(board,"my second beautiful board");
  struct pos_t *pos4=get_possible_moves(board,TILE_TYPES[2]);
  add_tile(board,TILE_TYPES[2],pos4[0]);
  print_board(board,"my third beautiful board");
  struct pos_t *pos5=get_possible_moves(board,TILE_TYPES[3]);
  add_tile(board,TILE_TYPES[3],pos5[0]);
  print_board(board,"my forth beautiful board");
  struct pos_t *pos6=get_possible_moves(board,TILE_TYPES[3]);
  add_tile(board,TILE_TYPES[3],pos6[0]);
  print_board(board,"my fiveth beautiful board");
  display_graph(get_graph(board),"test.dot");
  free(pos1);
  free(pos2);
  free(pos3);
  free(pos4);
  free(pos5);
  free(pos6);
  free_board(board);
 // deck_free(deck);*/


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
	
	
