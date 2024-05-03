#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "server.h"

struct board_t* game_board;
struct deck_t* game_deck;

void initialize_server(int seed){
  srand(seed);
  game_deck = generate_deck(seed);
  game_board = initialize_board();
}

struct move_t play_first_move(){
  struct tile_t first_tile = deck_get(game_deck, 0);
  struct move_t first_move = {.player_id = -1, .x = 0, .y = 0, .tile = first_tile, .meeple = NO_CONNECTION};
  make_move(game_board, first_move);
  return first_move;
}

void run_game(struct gameconfig_t config, char* lib1, char* lib2, int seed){
  
  void *handle1;
  void *handle2;
  char *error;
  // function pointers of each player s functions
  char const* (*get_player_name[2])(void);

  void (*initialize[2]) (enum player_color_t, const struct move_t, struct gameconfig_t);
  
  struct move_t (*play[2]) (const struct move_t, const struct tile_t);
  
  handle1 = dlopen (lib1, RTLD_LAZY);
  handle2 = dlopen (lib2, RTLD_LAZY);
  
  if (!handle1 || !handle2) {
    fputs (dlerror(), stderr);
    exit(1);
  }
  
  if ((error = dlerror()) != NULL){
    fputs(error, stderr);
    exit(1);
  }

  get_player_name[0] = dlsym(handle1, "get_player_name");
  get_player_name[1] = dlsym(handle2, "get_player_name");

  initialize[0] = dlsym(handle1, "initialize");
  initialize[1] = dlsym(handle2, "initialize");

  play[0] = dlsym(handle1, "play");
  play[1] = dlsym(handle2, "play");

  // server starts

  initialize_server(seed);
  struct move_t first_move = play_first_move();
 
  int first_player = rand() % 2;

  initialize[first_player](WHITE, first_move, config);
  initialize[1-first_player](BLACK, first_move, config);
  
  int turn_counter = 1;

  struct move_t last_move_played = first_move;
  while( 1 ){
    struct tile_t curr_tile = deck_get(game_deck, turn_counter);
    if(empty_tile(curr_tile)){
      printf("Game Over ! no more tiles\n");
    }
    struct move_t curr_move = play[(first_player+turn_counter) % 2](last_move_played, curr_tile);
    /*
      checking here if move is valid
     */
    
    make_move(game_board, curr_move);
    last_move_played = curr_move;
    turn_counter++;
    if(turn_counter == 37)
      display_graph(game_board->g, "game.dot");
  }
  // closing libraries
  dlclose(handle1);
  dlclose(handle2);
}

void finalize_server(){
  free_board(game_board);
  deck_free(game_deck);
}

int main(int argc, char* argv[]){
  int opt;
  // a random seed 
  int seed = time(NULL);
  int meeples = 0;
  // the game mode
  enum gamemode_t mode = NO_MEEPLE;
  while((opt = getopt(argc, argv, "s:m:")) != -1)
    {  
        switch(opt)  
        {
            case 's':
		printf("option %c\n", opt);
	        seed = atoi(optarg);
		break;
            case 'm':
		printf("option: %c\n", opt);
	        mode = atoi(optarg);
		break;  
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }
  char* lib[2];
  // non option arguments ( the libs )
  for(int i = optind; i < argc; i++){
    printf("%s",argv[i]);
    lib[i-optind] = argv[i];
  }

  initialize_server(seed);
  
  struct gameconfig_t config = {.mode = mode, .meeples = meeples, .deck = game_deck};
  run_game(config, lib[0], lib[1], seed);
  finalize_server();
  
  return 0;
}
