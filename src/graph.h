#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "deck.h"
#include "move.h"
#include <igraph.h>
struct coord{
  int x,y;
};
struct attribute{
  int is_there_meeple[2];
  int there_is_meeple;  
  int does_vertex_exist_in_renault;
  enum color_t color;
  int vertex_is_open;
  struct coord coord;
  int already_added_to_a_component;
  };



struct component_t {
  int *vertices;
  int number;
};

struct components_t {
  struct component_t *components;
  int size;
};
struct connected_components{
  igraph_vector_int_t *csize, *membership;
  igraph_integer_t *no;
};

struct attribute *empty_attributes();
struct components_t *get_connected_components(struct tile_t t);

igraph_t *create_graph_for_tile(igraph_t *graph, int id_in_graph, struct tile_t t);

void initialize_new_tile(struct tile_t t,int id_in_graph);

void add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) ;

struct connected_components * get_components(igraph_t *graph);

igraph_vector_int_t * does_adding_ends_a_certain_component(igraph_t *g, int id_in_graph, int direction, int vertex);


igraph_vector_ptr_t * set_of_new_finished(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck);

void free_components(igraph_vector_ptr_t *components) ;

int calculate_score_in_a_component(igraph_vector_int_t *component);

int added_score(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck);

int number_of_vertices_in_new_component(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck, int direction, int vertex);

igraph_vector_int_t * get_biggest_component_of_player_in_a_position(igraph_t *g, struct tile_t t, int neighbours_ids[4],  int id_in_deck , int player_id, enum color_t color, enum gamemode_t mode, int n_meeples);

int meeple_can_be_added(igraph_t *g, int vertex_in_graph);

int which_player_has_more_meeples_in_component(igraph_t *g, int vertex_in_graph);
int meeple_can_be_added_in_a_position(igraph_t *g, struct tile_t t, int id_in_deck, int neighbours_ids[4]);

void add_meeple(igraph_t *g, int vertex_in_graph, int player_id);

int retrieve_meeples(igraph_t *g, int id_in_deck, int player_id); 

void display_graph(igraph_t *graph, const char *filename);
#endif
