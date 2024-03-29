#include "board.h"


Initialize_board(){
}
is_empty(x,y,board){
}  
get_available_sides(board){
  struct tuile tableau;
  get_available_side(tuile);
  fill_table(tableau);
  return tableau;
}
add_tile(board,deck,Tile){
  tableau = get_available_sides();
  x,y = pick_side(tableau);
  remove_from_deck(deck,tile);
  fill_board(board,x,y);
}

