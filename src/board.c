#include "board.h"

#define NUM_TILES 72
struct board_t{
  struct case_t *t[2*NUM_TILES][2*NUM_TILES];
  int size;
};

 
