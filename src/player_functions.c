#include "player_functions.h"
//no meeple functions

struct move_t* initialize_move(int player_id, struct tile_t tile, int x, int y, int meeple) {
    struct move_t* optimal = malloc(sizeof(struct move_t));
    if (optimal == NULL) {
        return NULL;
    }
    optimal->player_id = player_id;
    optimal->tile = tile;
    optimal->x = x;
    optimal->y = y;
    optimal->meeple = meeple;
    return optimal;
}


struct move_t *get_optimal_position_no_meeple(struct board_t *board, struct tile_t t, int player_id){
  int size = 0;
  int verifier = -1;
  struct move_t *optimal = NULL;
    
  for (int d = 0; d < 4; d++){
    struct tile_t flipped_tile = flip_tile(t, d);    
    struct pos_t *possible_moves = get_possible_moves(board, flipped_tile);
    for (int i = 0; i < get_size_possible_moves(possible_moves); ++i){
      int size_test = added_score(get_graph(board),flipped_tile,possible_moves[i].box->neighbors,board_size(board));
      if (size_test > size) {
	size = size_test;
	free(optimal);	
	optimal = initialize_move(player_id, flipped_tile, (possible_moves[i].box)->x, (possible_moves[i].box)->y, NO_CONNECTION);
	verifier = 1;
      }
    }
    free(possible_moves); 
  }
  if (verifier == 1) return optimal;
  return NULL;
}

struct move_t *get_biggest_open_road_component(struct board_t *board, struct tile_t t, int player_id, struct gameconfig_t config, enum color_t color){
  int _t[4] = { 0, 3 , 6, 9};  
  int size = 0;
  int verifier = -1;
  struct move_t *optimal = NULL;
    
  for (int d = 0; d < 4; ++d){
    struct tile_t flipped_tile = flip_tile(t, d);    
    struct pos_t *possible_moves_flipped = get_possible_moves(board, flipped_tile);
        
    for (int k = 0; k < get_size_possible_moves(possible_moves_flipped); ++k){
      for (int i = 0; i < 13; ++i){
	  if (t.c[i] == color){
	    int size_test = number_of_vertices_in_new_component(get_graph(board), flipped_tile, possible_moves_flipped[k].box->neighbors, board_size(board), i);
	    if (size_test > size && (config.mode == NO_MEEPLE || (player_id == 0 && (config.mode == FINITE_MEEPLE && color == GRAY && size_test >=4)) || (player_id == 0 && (config.mode == FINITE_MEEPLE && color == BROWN) ))) {
	      size = size_test;
	      free(optimal);
	      // Allouer une nouvelle structure move_t à chaque itération
	      optimal = malloc(sizeof(struct move_t));
	      // Copier les valeurs dans la nouvelle structure
	      optimal->player_id = player_id;
	      optimal->tile = flipped_tile;
	      optimal->x = (possible_moves_flipped[k].box)->x;
	      optimal->y = (possible_moves_flipped[k].box)->y;
//		printf("%d\n",config.meeples);	      			      
	      if ((config.mode == FINITE_MEEPLE) && (config.meeples > 0)){
		printf("olaaa\n");
		optimal->meeple = i;
		}
	      else
		optimal->meeple = NO_CONNECTION;

	      verifier = 1;
	    }
	  }
	}
      }
    
    free(possible_moves_flipped); // Libérer la mémoire allouée pour possible_moves_flipped
  }
  if (verifier == 1) return optimal;
  return NULL;
}

//infinite meeple functions

struct move_t *get_biggest_finished_component(struct board_t *board, struct tile_t t, int player_id, enum color_t color, struct gameconfig_t config){
  int size = 0;
  struct move_t *optimal = NULL;

  for (int d = 0; d < 4; ++d){
    struct tile_t flipped_tile = flip_tile(t, d);
    struct pos_t *possible_moves_flipped = get_possible_moves(board, flipped_tile);

    for (int k = 0; k < get_size_possible_moves(possible_moves_flipped); ++k){
	  igraph_vector_int_t *component = get_biggest_component_of_player_in_a_position(get_graph(board), flipped_tile, possible_moves_flipped[k].box->neighbors, board_size(board), player_id, color, config.mode, config.meeples); 
	  int size_test = igraph_vector_int_size(component); 
	  if (size_test > size){
	    free(optimal);
	    size = size_test;
	    optimal = initialize_move(player_id, flipped_tile, (possible_moves_flipped[k].box)->x, (possible_moves_flipped[k].box)->y, NO_CONNECTION);	    
	  }
	  igraph_vector_int_destroy(component);
	  free(component);
    }
    free(possible_moves_flipped); 
  }
  return optimal;
}


struct move_t *get_a_position_where_there_is_no_meeple(struct board_t *board, struct tile_t t, int player_id){
  for (int d = 0; d < 4; ++d){
    struct tile_t flipped_tile = flip_tile(t, d);
    struct pos_t *possible_moves_flipped = get_possible_moves(board, flipped_tile);  
        
    struct move_t *optimal = malloc(sizeof(struct move_t));
        
    for (int k = 0; k < get_size_possible_moves(possible_moves_flipped); ++k){
      int position = meeple_can_be_added_in_a_position(get_graph(board), flipped_tile, board_size(board), possible_moves_flipped[k].box->neighbors);
      if (position != -1){
	struct move_t mov = {.player_id = player_id, .tile = flipped_tile, .x = (possible_moves_flipped[k].box)->x, .y = (possible_moves_flipped[k].box)->y, .meeple = position-board_size(board)*13};
	free(possible_moves_flipped);			
	*optimal = mov;
	return optimal;
      }
    }
    free(possible_moves_flipped);
    free(optimal); 
  }
  return NULL; 
}


struct move_t *get_random_possible_position(struct board_t *board, struct tile_t t, int player_id){
  struct move_t *random = malloc(sizeof(struct move_t));  
  struct pos_t *possible_moves = get_possible_moves(board, t);
  random->player_id = player_id;
  random->tile = t;
  random->x = (possible_moves[0].box)->x;
  random->y = (possible_moves[0].box)->y;
  random->meeple = NO_CONNECTION;
  free(possible_moves);
  return random;
}

