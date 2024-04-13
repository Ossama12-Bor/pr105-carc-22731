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
  igraph_t* graph = malloc(sizeof(igraph_t));
  igraph_empty(graph,13,IGRAPH_UNDIRECTED);
   for (int i = 0; i < components->size; ++i){
        for (int j = 0; j < components->components[i].number; ++j){
            if (j < components->components[i].number - 1) {
                igraph_add_edge(graph, components->components[i].vertices[j], 
                                components->components[i].vertices[j+1]);
            }
  return graph; 
}
   }

