#include <dlfcn.h>
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
  int s[2];
  s[0] = 0;
  s[1] = 0;

  initialize_server(seed);
  struct move_t first_move = play_first_move();
 
  int first_player = rand() % 2;

  struct deck_t* deck_black = deck_copy(game_deck);
  struct deck_t* deck_white = deck_copy(game_deck);
  struct gameconfig_t config_black = {.mode = config.mode, .meeples = 7, .deck = deck_black};
  struct gameconfig_t config_white = {.mode = config.mode, .meeples = 7, .deck = deck_white};  
  initialize[first_player](BLACK, first_move, config_black);
  initialize[1-first_player](WHITE, first_move, config_white);
  
  size_t turn_counter = 1;

  struct move_t last_move_played = first_move;
  size_t d_size= deck_size(game_deck);
  int move_is_correct = 1;  
  while( turn_counter < d_size ){
    struct tile_t curr_tile = deck_get(game_deck, turn_counter);
    struct move_t curr_move = play[(first_player+turn_counter-1) % 2](last_move_played, curr_tile);
    struct tile_t tile=curr_move.tile;
    int id_in_empty=get_id_in_empty(get_board_empty(game_board),curr_move.x,curr_move.y);
    struct case_t *box=get_data(get_lelement_from_empty(get_board_empty(game_board),id_in_empty));
    s[(first_player+turn_counter-1)%2] += added_score(get_graph(game_board), curr_move.tile, box->neighbors, board_size(game_board));
  /* struct pos_t pos={.status={id_in_empty,0},.box=box};     */
	if(!is_correctly_played(game_board,curr_move)){
    make_move(game_board, curr_move);
		printf("player %ld made invalid move in %ld turn \n",(first_player+turn_counter-1)%2,turn_counter);
		move_is_correct = 0;
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
  if(move_is_correct == 1){
  printf("score de 1er joueur : %d\n",s[0]);
  printf("score de 2eme joueur : %d\n",s[1]);
  if (s[1] > s[0])
    printf("le joueur 2 a gagné!");
  else
    printf("le joueur 1 a gagné!\n");
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
    lib[i-optind] = argv[i];
  }

//  initialize_server(seed);

  struct gameconfig_t config = {.mode = mode, .meeples = 7, .deck = game_deck};
  run_game(config, lib[0], lib[1], seed);
  finalize_server();
  
  return 0;
}
