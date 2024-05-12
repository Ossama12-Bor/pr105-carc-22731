#include <igraph.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_TILES 72
#include "graph.h"

  
struct attribute attributes[13*NUM_TILES];

void initialize_coordinates_of_middle(){
  int coords[13][2] = {
    {-1, 2}, {0, 2}, {1, 2}, {2, 1}, {2, 0}, {2, -1},
    {1, -2}, {0, -2}, {-1, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {0, 0}
  };

  for (int i = 0; i < 13; i++) {
    attributes[i].coord.x = coords[i][0];
    attributes[i].coord.y = coords[i][1];
  }  
  
}

igraph_t *create_graph_for_tile(igraph_t *graph, int id_in_graph, struct tile_t t){
  if (id_in_graph == 0){
    initialize_coordinates_of_middle();
  }
  for (int i = 0; i < 13; ++i){
    for (int j = i-1; j >= 0; --j){
      if (t.t[i] == t.t[j]) {
	igraph_add_edge(graph,id_in_graph +  i, 
			id_in_graph + j);
	break;
      }
    }
  }
  return graph; 
}

//adding a tile to a graph functions

void initialize_new_tile(struct tile_t t,int id_in_graph){
  for(int i = id_in_graph ; i < id_in_graph + 13; ++i){
    attributes[i].does_vertex_exist_in_renault = 1;
    attributes[i].color = t.c[i-id_in_graph];
    attributes[i].vertex_is_open = 1;
    attributes[i].is_there_meeple[0] = 0;
    attributes[i].is_there_meeple[1] = 0;
    attributes[i].there_is_meeple = 0;            
  }
}

void change__coord_attribute(int id_in_graph, int neighbour_id, int k){
  int t[4][2] = {{0, -5}, {-5, 0}, {0, 5}, {5, 0}};
  for (int i = 0; i < 13; ++i){
    attributes[i + id_in_graph].coord.x = attributes[neighbour_id + i].coord.x+t[k][0];
    attributes[i + id_in_graph].coord.y = attributes[neighbour_id + i].coord.y+t[k][1];    
  }
}

void add_meeples_to_new_component(igraph_t *graph, int vertex_in_graph){
  //    printf("%d\n",attributes[vertex_in_graph].is_there_meeple[player_id]    );
  if (attributes[vertex_in_graph].is_there_meeple[0] || attributes[vertex_in_graph].is_there_meeple[1]){
    igraph_vector_int_t *result = malloc(sizeof(igraph_t));
    igraph_vector_int_init(result, 0);
    igraph_subcomponent(graph, result, vertex_in_graph, IGRAPH_ALL);
    int k = igraph_vector_int_size(result);
    for (int i = 0 ; i < k; i++){
      attributes[VECTOR(*result)[i]].there_is_meeple = 1;	  
    }
    igraph_vector_int_destroy(result) ;    
    free(result);
  
  }
}

void add_vertices_between_edges(igraph_t *graph, int id_in_graph, int neighbours_ids[4], int i){
  int t_neighb[4]= { 6, 9, 0, 3};
  int t_[4]= { 0, 3, 6, 9};  
  int neighbour_id = 13 * neighbours_ids[i];
  for (int j = 0; j < 3; j++) {
    igraph_add_edge(graph, id_in_graph + t_[i] + j, neighbour_id + t_neighb[i]+2-j);
    attributes[neighbour_id + t_neighb[i]+2-j].does_vertex_exist_in_renault = 0;
    attributes[neighbour_id + t_neighb[i]+2-j].vertex_is_open = 0;
    attributes[id_in_graph + t_[i] + j].vertex_is_open = 0;
    //   add_meeples_to_new_component(graph, neighbour_id + t_neighb[i]+2-j);
    change__coord_attribute(id_in_graph, neighbour_id, i);
  }
}


void add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) {
  int id_in_graph = 13 * id_in_deck;  
  initialize_new_tile(t,id_in_graph);
  attributes[id_in_graph + 12].vertex_is_open = 0;
  igraph_add_vertices(graph, 13, NULL);
  igraph_t *g= create_graph_for_tile(graph, id_in_graph, t);
  for (int i = 0; i < 4; i++) {
    if (neighbours_ids[i] != -1) {
      add_vertices_between_edges(graph, id_in_graph, neighbours_ids, i);
    }
  }
}


//displaying graph function



//functions to calculate the new finished connected components after adding a tile to a graph


igraph_vector_int_t * does_adding_ends_a_certain_component(igraph_t *graph, int id_in_graph, int direction, int vertex){
  int _t[4] = { 0, 3 , 6, 9};
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(graph, result, id_in_graph + _t[direction] + vertex, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);
  for (int i = 0 ; i < k; i++){
    if (attributes[VECTOR(*result)[i]].vertex_is_open == 1) {
      igraph_vector_int_destroy(result) ;    
      free(result);
      return NULL;
    }
  }
  return result;
}


igraph_vector_ptr_t * set_of_new_finished(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck){
  int d[4] ={0, 3, 6, 9,};
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  igraph_vector_ptr_t * components = malloc(sizeof(igraph_vector_ptr_t));
  igraph_vector_ptr_init(components, 0);  // size = 0
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);
  int id_in_graph = 13 * id_in_deck;
  for (int i = 0; i < 4; ++i){
    for (int j = 0; j < 3; ++j){
      if (attributes[id_in_graph + d[i] + j].already_added_to_a_component == 0){
	igraph_vector_int_t *component = does_adding_ends_a_certain_component(graph,id_in_graph, i, j);
	if (component != NULL){
	  int k = igraph_vector_int_size(component);
	  for (int l = 0 ; l < k; l++){
	    if (VECTOR(*component)[l] >= id_in_graph)
	      attributes[VECTOR(*component)[l]].already_added_to_a_component = 1;
	  }
	  igraph_vector_ptr_push_back(components, component);
	}
      }
    }
  }
  igraph_integer_t degree;
  igraph_degree_1(graph, &degree, id_in_graph + 12, IGRAPH_ALL, 0);
  
  if (attributes[id_in_graph + 12].already_added_to_a_component == 0 && degree == 0){
    attributes[id_in_graph + 12].already_added_to_a_component = 1;    
    igraph_vector_int_t *middle = malloc(sizeof(igraph_t));
    igraph_vector_int_init(middle, 0);
    igraph_vector_int_push_back(middle, id_in_graph + 12);
    igraph_vector_ptr_push_back(components, middle);        
  }
  for (int i = id_in_graph; i < id_in_graph + 13; ++i){
    attributes[i].already_added_to_a_component = 0;
  }
  int t_neighb[4]= { 6, 9, 0, 3};
  int t_[4]= { 0, 3, 6, 9};
  for (int i = 0; i < 4; i++) {
    if (neighbours_ids[i] != -1) {
      int neighbour_id = 13 * neighbours_ids[i];
      for (int j = 0; j < 3; j++) {
	
	attributes[neighbour_id + t_neighb[i]+2-j].vertex_is_open = 1;
	attributes[id_in_graph + t_[i] + j].vertex_is_open = 0;
      }
    }
  }
    
  igraph_destroy(graph);
  free(graph);
  return components;
}

int calculate_score_in_a_component(igraph_vector_int_t *component) {
  int s = 0;
  for (int i = 0; i < igraph_vector_int_size(component); ++i) {
    enum color_t color = attributes[VECTOR(*component)[i]].color;
    if (color == BROWN && attributes[VECTOR(*component)[i]].does_vertex_exist_in_renault == 1)
      s += 8;

    if (color == GRAY && attributes[VECTOR(*component)[i]].does_vertex_exist_in_renault == 1)
      s += 4;

    if (color == GREEN && attributes[VECTOR(*component)[i]].does_vertex_exist_in_renault == 1)
      s += 1;
  }
  return s;
}

void free_components(igraph_vector_ptr_t *components) {
  for (int i = 0; i < igraph_vector_ptr_size(components); i++) {
    igraph_vector_int_t *component = (igraph_vector_int_t *)igraph_vector_ptr_e(components, i);
    igraph_vector_int_destroy(component); 
    free(component); 
  }
  igraph_vector_ptr_destroy(components); 
  free(components); 
}



int added_score(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck){
  int s = 0;
  igraph_vector_int_t *components = set_of_new_finished(g, t, neighbours_ids, id_in_deck);
  
  for (int i = 0; i < igraph_vector_ptr_size(components); i++) {
    igraph_vector_int_t *component = (igraph_vector_int_t *)igraph_vector_ptr_e(components, i);
    s += calculate_score_in_a_component(component);  
  }
  free_components(components);
  return s;
}

//players strategies

int number_of_vertices_in_new_component(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck, int direction, int vertex){
  int _t[4] ={ 0, 3, 6, 9};
  int id_in_graph = id_in_deck * 13 ;  
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);  
  igraph_vector_int_t *result = malloc(sizeof(igraph_vector_int_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(graph, result, id_in_graph + _t[direction] + vertex, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);
  igraph_vector_int_destroy(result) ;    	
  free(result);
  igraph_destroy(graph);
  free(graph);  
  return k;
}

void does_tile_contain_open_color_vertex(struct tile_t t, enum color_t color){
  for (int i = 0; i < 12; ++i){
    if (t.c[i] == color) return 1;
  }
  return 0;
}

igraph_vector_int_t * get_biggest_component_of_player_in_a_position(igraph_t *g, struct tile_t t, int neighbours_ids[4],  int id_in_deck , int player_id, enum color_t color, enum gamemode_t mode, int n_meeples){
  int id_in_graph = 13 * id_in_deck;
  int _t[4] ={ 0, 3, 6, 9};
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  igraph_vector_int_t *result = malloc(sizeof(igraph_vector_int_t));
  igraph_vector_int_init(result, 0);  
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);
  int size =0;
  for (int i = 0; i < 4; ++i){
    for (int j =0; j < 3; ++j){
      igraph_vector_int_t *result_test = does_adding_ends_a_certain_component(graph, id_in_graph, i, j);
      if (result_test != NULL){
	if (mode == INFINITE_MEEPLE || ( mode == FINITE_MEEPLE && n_meeples >= 1 )) add_meeple(graph, id_in_graph + _t[i] + j, player_id);
	int size_test = igraph_vector_int_size(result_test);
	if (attributes[id_in_graph + _t[i] + j].color == color && (size_test > size) && (which_player_has_more_meeples_in_component(graph, id_in_graph + _t[i] + j) == player_id || mode == NO_MEEPLE)){
	  size = size_test;
	  result = result_test;
	}
      }
    }
  }
  igraph_destroy(graph);
  free(graph);  
  return result;
}

/* void get_biggest_road_component_of_adversary(igraph_t *g, struct tile_t t, int neighbours_ids[4], int player_id){  */
  
/* } */

/* void finish_biggest_road_component_of_adversary(igraph_t *g, ); */

//meeple functions

int meeple_can_be_added(igraph_t *g, int vertex_in_graph){
  int id_in_graph = vertex_in_graph - vertex_in_graph%13;
  for (int i = id_in_graph; i < id_in_graph + 13; ++i){
    if (attributes[i].is_there_meeple[0] || attributes[i].is_there_meeple[1]) return 0;
  }
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(g, result, vertex_in_graph, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);
  for (int i = 0 ; i < k; i++){
    if (attributes[VECTOR(*result)[i]].is_there_meeple[0] || attributes[VECTOR(*result)[i]].is_there_meeple[1]) return 0;
  }    
  return 1;
}

int which_player_has_more_meeples_in_component(igraph_t *g, int vertex_in_graph){
  int player_0_number = 0;
  int player_1_number = 0;
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(g, result, vertex_in_graph, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);
  for (int i = 0 ; i < k; i++){
    if (attributes[VECTOR(*result)[i]].is_there_meeple[0]) player_0_number++;
    if (attributes[VECTOR(*result)[i]].is_there_meeple[1]) player_1_number++;  
  }
  if (player_1_number == player_0_number) return -1 ;
  return (player_1_number > player_0_number);
}


void add_meeple(igraph_t *g, int vertex_in_graph, int player_id){
  if (meeple_can_be_added(g,vertex_in_graph)) {
    attributes[vertex_in_graph].is_there_meeple[player_id] = 1;
  }
}


int meeple_can_be_added_in_a_position(igraph_t *g, struct tile_t t, int id_in_deck, int neighbours_ids[4]){
  int id_in_graph = id_in_deck * 13 ;  
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);
  for (int i = id_in_graph; i < id_in_graph + 13; ++i){
    if (meeple_can_be_added(graph, i)) return i;
  }
  return -1;
}

int retrieve_meeples(igraph_t *g, int id_in_deck, int player_id){  
  int s = 0;
  int d[4] = {0, 3, 6, 9};
  int id_in_graph = 13 * id_in_deck;
  for (int i = 0; i < 4; ++i){
    for (int j = 0; j < 3; ++j){
      if (attributes[id_in_graph + d[i] + j].already_added_to_a_component == 0){
	igraph_vector_int_t *component = does_adding_ends_a_certain_component(g,id_in_graph, i, j);
	if (component != NULL){
	  int k = igraph_vector_int_size(component);
	  for (int l = 0 ; l < k; l++){
	    if (VECTOR(*component)[l] >= id_in_graph)
	      attributes[VECTOR(*component)[l]].already_added_to_a_component = 1;
	    if (attributes[VECTOR(*component)[l]].is_there_meeple[player_id]){
	      s++;
	      attributes[VECTOR(*component)[l]].is_there_meeple[player_id] = 0;	
	    }
	    if (attributes[VECTOR(*component)[l]].is_there_meeple[1-player_id])
	      attributes[VECTOR(*component)[l]].is_there_meeple[1-player_id] = 0;
	  }
	}
      }
    }
  }
    for (int i = id_in_graph; i < id_in_graph + 13; ++i){
    attributes[i].already_added_to_a_component = 0;
  }
  return s;
}

void display_graph(igraph_t *graph, const char *filename) {
  FILE *outfile;
  char *colors[] = {"greenyellow", "gray70", "blue", "saddlebrown", "webpurple"};
  outfile = fopen(filename, "w");
  fprintf(outfile, "graph {\n");
  fprintf(outfile, "graph [pad=\"0.212,0.055\" bgcolor=lightgray ]\n");   
  fprintf(outfile, "  node [shape = circle, width=0.6]\n");

  for (igraph_integer_t i = 0; i < igraph_vcount(graph); i++) {
    double x = 0.0, y = 0.0;
    x = attributes[i].coord.x;
    y = attributes[i].coord.y;
    fprintf(outfile, "  %ld [pos = \"%f, %f!\", label = \"%ld\", width = 0.6, style = filled, fillcolor=%s, fontcolor=",
	    (long)i, x, y, (long)i, colors[attributes[i].color]);

    // Set font color based on conditions
    if (attributes[i].is_there_meeple[0] == 1)
      fprintf(outfile, "red");
    else if (attributes[i].is_there_meeple[1] == 1)
      fprintf(outfile, "blue");
    else if (meeple_can_be_added(graph,i) == 0 )
      fprintf(outfile, "white");    
    else
      fprintf(outfile, "black"); // Default font color

    fprintf(outfile, "]\n");
  }
  for (igraph_integer_t i = 0; i < igraph_ecount(graph); i++) {
    igraph_integer_t from, to;
    igraph_edge(graph, i, &from, &to);
    double x1 = attributes[from].coord.x;
    double y1 = attributes[from].coord.y;
    double x2 = attributes[to].coord.x;
    double y2 = attributes[to].coord.y;
    double len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    fprintf(outfile, "  %ld -- %ld [len=%.2f];\n", (long)from, (long)to, len);    }
  fprintf(outfile, "}\n");
  fclose(outfile);
}
