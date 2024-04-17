#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>
#include "move.h"
struct component_t {
  int *vertices;
  int number;
};

struct components_t {
  struct component_t *components;
  int size;
};

struct components_t *get_connected_components(struct tile_t t) {
  int m = 0;
  for (int i = 0; i < 13; ++i) {
    if (t.t[i] > m) m=t.t[i];
  }

  struct components_t *components = malloc(sizeof(struct components_t));
  components->components = malloc(sizeof(struct component_t) * (m + 1));
  components->size = m + 1;
  for (int i = 0; i <= m; i++) {
    components->components[i].number = 0; 
  }  

  for (int i = 0; i < 13; ++i) {
    components->components[t.t[i]].number++;
  }

  for (int i = 0; i <= m; i++) {  
    components->components[i].vertices = malloc(sizeof(int) * components->components[i].number);
    int compt = 0;
    for (int j = 0; j < 13; j++) {
      if (t.t[j] == i) {
        components->components[i].vertices[compt] = j;
        compt++;
      }
    }
  }
  

  return components;
}

igraph_t *create_graph_for_tile(struct tile_t t){
  struct components_t *components = get_connected_components(t);
  printf("%d\n\n",components->size);
  igraph_t* graph = malloc(sizeof(igraph_t));
  igraph_empty(graph,13,IGRAPH_UNDIRECTED);
   for (int i = 0; i < components->size; ++i){
        // Iterate over vertices in the current component
        for (int j = 0; j < components->components[i].number; ++j){
            // Add edges between adjacent vertices in the component
            if (j < components->components[i].number - 1) {
                igraph_add_edge(graph, components->components[i].vertices[j], 
                                components->components[i].vertices[j+1]);
            }
        }
    }
  for (int i = 0; i < components->size; ++i){
//    free(components->components[i].vertices);
  }
//  free(components->components);
//  free(components);
  return graph; 
}

igraph_t *add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) {
  int t_neighb[4]= { 6, 9, 0, 3};
  int t_[4]= { 0, 3, 6, 9};  
    igraph_t *uniong = malloc(sizeof(igraph_t));
    igraph_t *tile = create_graph_for_tile(t);
    igraph_disjoint_union(uniong, graph, tile);

    int id_in_graph = 13 * id_in_deck;
    for (int i = 0; i < 4; i++) {
        if (neighbours_ids[i] != -1) {
            int neighbour_id = 13 * neighbours_ids[i];
            for (int j = 0; j < 3; j++) {
	      igraph_add_edge(uniong, id_in_graph + t_[i] + j, neighbour_id + t_neighb[i]+j);
            }
        }
    }
    return uniong;
}
