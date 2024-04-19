#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_TILES 72
#include "graph.h"
struct connected_components{
  int *csize;
  int *membership;
  int *no;
};
  
struct attribute attributes[NUM_TILES];


  
struct components_t *get_connected_components(struct tile_t t) {
  unsigned int m = 0;
  for (unsigned int i = 0; i < 13; ++i) {
    if (t.t[i] > m) m=t.t[i];
  }

  struct components_t *components = malloc(sizeof(struct components_t));
  components->components = malloc(sizeof(struct component_t) * (m + 1));
  components->size = m + 1;
  for (unsigned int i = 0; i <= m; i++) {
    components->components[i].number = 0; 
  }  

  for (unsigned int i = 0; i < 13; ++i) {
    components->components[t.t[i]].number++;
  }

  for (unsigned int i = 0; i <= m; i++) {  
    components->components[i].vertices = malloc(sizeof(unsigned int) * components->components[i].number);
    unsigned int compt = 0;
    for (unsigned int j = 0; j < 13; j++) {
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
void initialize_new_tile(struct tile_t t,int id_in_graph){
  for(int i = id_in_graph ; i < id_in_graph + 13; ++i){
      attributes[i].does_vertex_exist_in_renault = 1;
      attributes[i].color = t.c[i];
      attributes[i].vertex_can_be_added = 1;
      attributes[i].is_there_meeple = 0;    
  }
}
igraph_t *add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) {
  int t_neighb[4]= { 6, 9, 0, 3};
  int t_[4]= { 0, 3, 6, 9};
    int id_in_graph = 13 * id_in_deck;  
    igraph_t *uniong = malloc(sizeof(igraph_t));
    igraph_t *tile = create_graph_for_tile(t);
    //    attributes = realloc(attributes,id_in_graph + 13);
    initialize_new_tile(t,id_in_graph);
    igraph_disjoint_union(uniong, graph, tile);
    for (int i = 0; i < 4; i++) {
        if (neighbours_ids[i] != -1) {
            int neighbour_id = 13 * neighbours_ids[i];
            for (int j = 0; j < 3; j++) {
	      igraph_add_edge(uniong, id_in_graph + t_[i] + j, neighbour_id + t_neighb[i]+2-j);
	      attributes[neighbour_id + t_neighb[i]+2-j].does_vertex_exist_in_renault = 0;
	      attributes[neighbour_id + t_neighb[i]+2-j].vertex_can_be_added = 0;
	      attributes[id_in_graph + t_[i] + j].vertex_can_be_added = 0;
            }
        }
    }
    return uniong;
}

struct connected_components * get_components(igraph_t *graph){
  struct connected_components *con = malloc(sizeof(struct connected_components));
  igraph_vector_int_t *csize;
  igraph_vector_int_t *membership;  
  igraph_integer_t *no = 0;
  igraph_vector_int_init(csize, 0);
  igraph_vector_int_init(membership, 0);
  igraph_connected_components(graph, membership, csize, no,  IGRAPH_WEAK);
  con->csize = csize;
  con->membership = membership;
  con->no = no;
  return con;
}


  
