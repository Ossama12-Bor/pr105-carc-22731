#include "test_board.h"

void test_board(void){
 
  struct board_t *board = initialize_board();
  print_board(board,"myboard");

  assert(board_size(board)==0);
  assert(set_size(get_board_empty(board))==1);
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

  printf("all tests passed\n");
}

void second_test_board(void){
  struct board_t *board = initialize_board();
  print_board(board,"myboard");
  struct pos_t *pos1=get_possible_moves(board,TILE_TYPES[0]);
  add_tile(board,TILE_TYPES[0],pos1[0]);
  assert(board_size(board)==1);
  print_board(board,"myboard");
  struct pos_t *pos2=get_possible_moves(board,TILE_TYPES[5]);
  add_tile(board,TILE_TYPES[5],pos2[1]);
  print_board(board,"my beautiful board");
  
  struct pos_t *pos3=get_possible_moves(board,TILE_TYPES[0]);
  add_tile(board,TILE_TYPES[0],pos3[2]);
  print_board(board,"my second beautiful board");
  struct pos_t *pos4=get_possible_moves(board,flip_tile(TILE_TYPES[4],1));
  add_tile(board,flip_tile(TILE_TYPES[4],1),pos4[1]);
  print_board(board,"my third beautiful board");
  struct pos_t *pos5=get_possible_moves(board,TILE_TYPES[6]);
  add_tile(board,TILE_TYPES[6],pos5[0]);
  print_board(board,"my forth beautiful board");
  struct pos_t *pos6=get_possible_moves(board,flip_tile(TILE_TYPES[7],1));
  add_tile(board,flip_tile(TILE_TYPES[7],1),pos6[1]);
  struct pos_t *pos7=get_possible_moves(board,flip_tile(TILE_TYPES[8],2));
  add_tile(board,flip_tile(TILE_TYPES[8],2),pos7[0]);
  print_board(board,"my fiveth beautiful board");
  display_graph(get_graph(board),"test.dot");
  free(pos1);
  free(pos2);
  free(pos3);
  free(pos4);
  free(pos5);
  free(pos6);
  free(pos7);
  free_board(board);
  printf("all tests passed\n");
}

	
