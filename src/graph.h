#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "deck.h"
#include "move.h"
#include <igraph.h>
struct attribute{
  int is_there_meeple;
  int does_vertex_exist_in_renault;
  enum color_t color;
  int vertex_can_be_added;
  };



struct component_t {
  int *vertices;
  int number;
};

struct components_t {
  struct component_t *components;
  int size;
};
struct attribute *empty_attributes();
struct components_t *get_connected_components(struct tile_t t);

igraph_t *create_graph_for_tile(struct tile_t t);

void initialize_new_tile(struct tile_t t,int id_in_graph);

igraph_t *add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) ;

#endif
