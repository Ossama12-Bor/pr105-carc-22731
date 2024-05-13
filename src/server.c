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
  printf("ll\n");  
  make_move(game_board, first_move);
  printf("ll");
  return first_move;
}

void run_game(struct gameconfig_t config, char* lib1, char* lib2, int seed){
  
  void *handle1;
  void *handle2;
  char *error;
  // function pointers of each player s functions
 // char const* (*get_player_name[2])(void);

  void (*initialize[2]) (enum player_color_t, const struct move_t, struct gameconfig_t);
  
  struct move_t (*play[2]) (const struct move_t, const struct tile_t);

  void (*finalize[2])();
  
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

  /*get_player_name[0] = dlsym(handle1, "get_player_name");
  get_player_name[1] = dlsym(handle2, "get_player_name");*/

  initialize[0] = dlsym(handle1, "initialize");
  initialize[1] = dlsym(handle2, "initialize");

  play[0] = dlsym(handle1, "play");
  play[1] = dlsym(handle2, "play");

  finalize[0] = dlsym(handle1, "finalize");
  finalize[1] = dlsym(handle2, "finalize");

  // server starts

  initialize_server(seed);
  struct move_t first_move = play_first_move();
 
  int first_player = rand() % 2;

  initialize[first_player](BLACK, first_move, config);
  initialize[1-first_player](WHITE, first_move, config);
  
  size_t turn_counter = 1;

  struct move_t last_move_played = first_move;
  size_t d_size=deck_size(game_deck);
  while( turn_counter < d_size ){
    printf("%d\n",turn_counter);
    struct tile_t curr_tile = deck_get(game_deck, turn_counter);
    struct move_t curr_move = play[(first_player+turn_counter-1) % 2](last_move_played, curr_tile);
    struct pos_t *possible_moves = get_possible_moves(game_board,curr_tile);
    print_case(possible_moves[0].box);
  //  printf("%d,%d\n",curr_move.x,curr_move.y);
    free(possible_moves);
	if(!is_correctly_played(game_board,curr_move)){
    make_move(game_board, curr_move);
		printf("player %ld made invalid move in %ld turn \n",(first_player+turn_counter-1)%2,turn_counter);
		break;
	}
    make_move(game_board, curr_move);
 if (curr_move.meeple != NO_CONNECTION){
    add_meeple(get_graph(game_board), (board_size(game_board)-1)*13 + curr_move.meeple, (first_player+turn_counter-1) % 2);
    
  }
    retrieve_meeples(get_graph(game_board), board_size(game_board)-1, (first_player+turn_counter-1) % 2);
    
    last_move_played = curr_move;
    if(turn_counter == 20)
      display_graph(get_graph(game_board), "test.dot");
    turn_counter++;
  }
  display_graph(get_graph(game_board), "test.dot");
  printf("game over !\n");

  finalize[0]();
  finalize[1]();
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
    //printf("%s",argv[i]);
    lib[i-optind] = argv[i];
  }

  initialize_server(seed);
  
  struct gameconfig_t config = {.mode = INFINITE_MEEPLE, .meeples = 7, .deck = game_deck};
  run_game(config, lib[0], lib[1], seed);
  finalize_server();
  
  return 0;
}
