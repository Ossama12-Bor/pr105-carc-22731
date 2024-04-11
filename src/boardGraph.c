#include "boardGraph.h"
#include <stdlib.h>

#define NUM_TILE_TYPES 5
const struct tile_t TILE_TYPES[] = {CARC_TILE_EMPTY,
				  CARC_TILE_INIT,
				  CARC_TILE_GREEN,
				  CARC_TILE_XROAD,
				  CARC_TILE_TINI};

/* Struct representing a board */
struct board_t{
  igraph_t* g;
  struct deck_t* deck;
  struct euclidian_tile* played_tiles;
};

/* Deck generator */
void generate_deck(struct deck_t* game_deck,int seed,int deck_size){
  srand(seed);
  for(int i=0; i<deck_size; i++)
    deck_add(game_deck, TILE_TYPES[rand() % NUM_TILE_TYPES]);
}

/* Board allocator */
struct board_t* allocate_board(size_t deck_capacity){
  igraph_t* board_graph = malloc(sizeof(igraph_t));
  struct deck_t* game_deck = deck_empty(deck_capacity);
  struct board_t* game_board = malloc(sizeof(struct board_t));
  game_board->g = board_graph;
  game_board->deck = game_deck;
  return game_board;
}

/* Board initializer (game_board must be alloc before)*/
void initialize_board(struct board_t* game_board){
  generate_deck(game_board-> deck);
}

void make_move(struct board_t* game_board){
  return;
}

/* Frees the allocated memory for a board */
void free_board(struct board_t* game_board){
  igraph_destroy(game_board->g);
  free_deck(game_board->deck);
  free(game_board);
}
