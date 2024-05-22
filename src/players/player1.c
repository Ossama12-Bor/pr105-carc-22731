#include "playerStruct.h"
#include "player_functions.h"
#include <assert.h>
struct player_t player;

char const* get_player_name(){
  return "ssuaG";
}



//modes

struct move_t *play_in_no_meeple(struct board_t *board, const struct tile_t t, int player_id){
  struct gameconfig_t config = {.mode = NO_MEEPLE, .meeples = 7, .deck = player.config.deck};    
   struct move_t *optimal = get_optimal_position_no_meeple(board, t, player_id);
    
    if (optimal != NULL) return optimal;
    
    optimal = get_biggest_open_component(board, t, player_id, config,GRAY);
    
    if (optimal != NULL) return optimal;
    
    optimal = get_random_possible_position(board,t,player_id);
        
    return optimal;
}

struct move_t *play_in_infinite_meeple(struct board_t *board, const struct tile_t t, int player_id){
  struct gameconfig_t config = {.mode = INFINITE_MEEPLE, .meeples = 7, .deck = player.config.deck};  
  struct move_t *brown = get_biggest_finished_component(board, t, 0, BROWN, config);
    if (brown != NULL) return brown;
    
    if (rand()%2 == 0){
    struct move_t *road_adversary = get_biggest_finished_component(board, t, 1 - 0, GRAY, config);
    if (road_adversary != NULL) return road_adversary;
    }
    else{
    struct move_t *no_meeple = get_a_position_where_there_is_no_meeple(board, t, player_id);
    if (no_meeple != NULL) return no_meeple;
    }

    struct move_t *random = get_random_possible_position(board,t,player_id);
        
    return random;
}

struct move_t *play_in_finite_meeple(struct board_t *board, const struct tile_t t, int player_id, struct gameconfig_t config){

  struct move_t *brown = get_biggest_finished_component(board, t, 0, BROWN, config);
   if (brown != NULL) return brown;
   if (rand()%2 == 0){     
   struct move_t *road_adversary = get_biggest_finished_component(board, t, 1 - 0, GRAY, config);
   if (road_adversary != NULL) return road_adversary;
       } else {
  struct move_t *open_road_meeple = get_biggest_open_component(board, t, player_id,config,GRAY);
   if (open_road_meeple != NULL) return open_road_meeple;
   }
    struct move_t *random = get_random_possible_position(board,t,player_id);
        
    return random;
}  

void initialize(enum player_color_t player_id, const struct move_t first_move,struct gameconfig_t config){
  
  player.player_id = player_id;
  player.myboard = initialize_board();
  player.config.deck = config.deck;  
  update_player_board(&player, first_move);
  if(config.mode == NO_MEEPLE){
    player.config.meeples = 0;
    player.config.mode = NO_MEEPLE;
    }
  else if(config.mode == INFINITE_MEEPLE){
    player.config.meeples = -1;
    player.config.mode = INFINITE_MEEPLE;
    }
  else{
    player.config.meeples = config.meeples;
    player.config.mode = FINITE_MEEPLE;
    }
  player.name = get_player_name();
}

struct move_t play(const struct move_t previous_move, const struct tile_t tile){
  struct move_t *move_to_play = NULL;
  struct move_t mv ;  
  if(previous_move.player_id!=-1){
    printf("(%d,%d) my previous move\n",previous_move.x,previous_move.y);
    update_player_board(&player, previous_move);}
  if (player.config.mode == NO_MEEPLE){
    move_to_play = play_in_no_meeple(player.myboard, tile, player.player_id);
    printf("(%d,%d) my  move\n",move_to_play->x,move_to_play->y);
    mv = *move_to_play;        
  }
  else if (player.config.mode == INFINITE_MEEPLE){
    move_to_play = play_in_infinite_meeple(player.myboard, tile, player.player_id);
    mv = *move_to_play;        
  }
  else{
    move_to_play = play_in_finite_meeple(player.myboard, tile, player.player_id, player.config);
    mv = *move_to_play;    
    }
  
  update_player_board(&player, mv);
  free(move_to_play);
  return mv;

}

void finalize(){
  free_board(player.myboard);
  deck_free(player.config.deck);
}


