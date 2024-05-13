#include "playerStruct.h"
#include "board.h"
#include "player_functions.h"
#include <assert.h>
struct player_t player;

char const* get_player_name(){
  return "ssuaG";
}



//modes

struct move_t *play_in_no_meeple(struct board_t *board, const struct tile_t t, int player_id){ 
    struct move_t *optimal = get_optimal_position_no_meeple(board, t, player_id);
    
    if (optimal != NULL) return optimal;
    
    optimal = get_biggest_open_road_component(board, t, player_id, NO_MEEPLE, 0,GRAY);
    
    if (optimal != NULL) return optimal;
    
    // Allouer une nouvelle structure move_t
    optimal = get_random_possible_position(board,t,player_id);
        
    return optimal;
}

struct move_t *play_in_infinite_meeple(struct board_t *board, const struct tile_t t, int player_id){
  struct move_t *brown = get_biggest_finished_component(board, t, 0, BROWN, -1, INFINITE_MEEPLE);
    if (brown != NULL) return brown;
    
    struct move_t *road = get_biggest_finished_component(board, t, 0, GRAY, -1, INFINITE_MEEPLE);
    if (road != NULL) return road;
    
    struct move_t *road_adversary = get_biggest_finished_component(board, t, 1 - 0, GRAY, -1, INFINITE_MEEPLE);
    if (road_adversary != NULL) return road_adversary;
    
    struct move_t *green = get_biggest_finished_component(board, t, 0, GREEN, -1, INFINITE_MEEPLE);
    if (green != NULL) return green;
    
   struct move_t *no_meeple = get_a_position_where_there_is_no_meeple(board, t, player_id);
    if (no_meeple != NULL) return no_meeple;
   
    // Allouer une nouvelle structure move_t
    struct move_t *random = get_random_possible_position(board,t,player_id);
        
    return random;
}

struct move_t *play_in_finite_meeple(struct board_t *board, const struct tile_t t, int player_id, int n_meeples){
  struct move_t *brown = get_biggest_finished_component(board, t, 0, BROWN, -1, FINITE_MEEPLE);
    if (brown != NULL) return brown;
    
    struct move_t *road = get_biggest_finished_component(board, t, 0, GRAY, -1, FINITE_MEEPLE);
    if (road != NULL) return road;
    
    struct move_t *road_adversary = get_biggest_finished_component(board, t, 1 - 0, GRAY, -1, FINITE_MEEPLE);
    if (road_adversary != NULL) return road_adversary;
    
    struct move_t *green = get_biggest_finished_component(board, t, 0, GREEN, -1, FINITE_MEEPLE);
    if (green != NULL) return green;    
    
  struct move_t *open_brown_meeple = get_biggest_open_road_component(board, t, player_id,FINITE_MEEPLE,n_meeples,BROWN);
    if (open_brown_meeple != NULL) return open_brown_meeple;
   struct move_t *open_road_meeple = get_biggest_open_road_component(board, t, player_id,FINITE_MEEPLE,n_meeples,GRAY);
    if (open_road_meeple != NULL) return open_road_meeple;
    
    struct move_t *random = get_random_possible_position(board,t,player_id);
        
    return random;
}  

void initialize(enum player_color_t player_id, const struct move_t first_move,struct gameconfig_t config){
  
  player.player_id = player_id;
  player.myboard = initialize_board();
  update_player_board(&player, first_move);
  player.score = 0;
  if(config.mode == NO_MEEPLE){
    player.n_meeples = 0;
    player.mode = FINITE_MEEPLE;
    }
  else if(config.mode == INFINITE_MEEPLE){
    player.n_meeples = -1;
    player.mode = INFINITE_MEEPLE;
    }
  else{
    player.n_meeples = config.meeples;
    player.mode = FINITE_MEEPLE;
    }
  player.name = get_player_name();
}

struct move_t play(const struct move_t previous_move, const struct tile_t tile){
  printf("sjsfhsiqgf\n");                 
  if(player.player_id==WHITE ||(player.player_id==BLACK && board_size(player.myboard)!=1)){
    update_player_board(&player, previous_move);}
  struct move_t *move_to_play = play_in_finite_meeple(player.myboard, tile, player.player_id,0);
  update_player_board(&player, *move_to_play);
  return *move_to_play;

}

void finalize(){
  free_board(player.myboard);
}


