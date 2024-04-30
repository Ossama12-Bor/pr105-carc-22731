#include <igraph.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_TILES 72
#include "graph.h"

  
struct attribute attributes[NUM_TILES*13];

  
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

igraph_t *create_graph_for_tile(igraph_t *graph, int id_in_graph, struct tile_t t){
attributes[0].coord.x = -1;
attributes[0].coord.y = 2;
attributes[1].coord.x = 0;
attributes[1].coord.y = 2;
attributes[2].coord.x = 1;
attributes[2].coord.y = 2;
attributes[3].coord.x = 2;
attributes[3].coord.y = 1;
attributes[4].coord.x = 2;
attributes[4].coord.y = 0;
attributes[5].coord.x = 2;
attributes[5].coord.y = -1;
attributes[6].coord.x = 1;
attributes[6].coord.y = -2;
attributes[7].coord.x = 0;
attributes[7].coord.y = -2;
attributes[8].coord.x = -1;
attributes[8].coord.y = -2;
attributes[9].coord.x = -2;
attributes[9].coord.y = -1;
attributes[10].coord.x = -2;
attributes[10].coord.y = 0;
attributes[11].coord.x = -2;
attributes[11].coord.y = 1;
attributes[12].coord.x = 0;
attributes[12].coord.y = 0;  
  struct components_t *components = get_connected_components(t);
//  printf("%d\n\n",components->size);
//  igraph_t* graph = malloc(sizeof(igraph_t));
//  igraph_empty(graph,13,IGRAPH_UNDIRECTED);
   for (int i = 0; i < components->size; ++i){
        // Iterate over vertices in the current component
        for (int j = 0; j < components->components[i].number; ++j){
            // Add edges between adjacent vertices in the component
            if (j < components->components[i].number - 1) {
                igraph_add_edge(graph,id_in_graph +  components->components[i].vertices[j], 
                                id_in_graph + components->components[i].vertices[j+1]);
            }
        }
    }
  for (int i = 0; i < components->size; ++i){
    free(components->components[i].vertices);
  }
  free(components->components);
  free(components);
  return graph; 
}
void initialize_new_tile(struct tile_t t,int id_in_graph){
  for(int i = id_in_graph ; i < id_in_graph + 13; ++i){
      attributes[i].does_vertex_exist_in_renault = 1;
      attributes[i].color = t.c[i];
      attributes[i].vertex_is_open = 1;
      attributes[i].is_there_meeple = 0;
  }
}

void change__coord_attribute(int id_in_graph, int neighbour_id, int k){
  int t[4][2] = {{0, -5}, {-5, 0}, {0, 5}, {5, 0}};
  for (int i = 0; i < 13; ++i){
    attributes[i + id_in_graph].coord.x = attributes[neighbour_id + i].coord.x+t[k][0];
    attributes[i + id_in_graph].coord.y = attributes[neighbour_id + i].coord.y+t[k][1];    
  }
}
igraph_t *add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) {
  int t_neighb[4]= { 6, 9, 0, 3};
  int t_[4]= { 0, 3, 6, 9};
    int id_in_graph = 13 * id_in_deck;  
  for(int i = id_in_graph ; i < id_in_graph + 13; ++i){
      attributes[i].does_vertex_exist_in_renault = 1;
      attributes[i].color = t.c[i-id_in_graph];
      attributes[i].vertex_is_open = 1;
      attributes[i].is_there_meeple = 0;
}
  attributes[id_in_graph + 12].vertex_is_open = 0;
  igraph_add_vertices(graph, 13, NULL);
  graph = create_graph_for_tile(graph, id_in_graph, t);
    for (int i = 0; i < 4; i++) {
        if (neighbours_ids[i] != -1) {
            int neighbour_id = 13 * neighbours_ids[i];
            for (int j = 0; j < 3; j++) {
	      igraph_add_edge(graph, id_in_graph + t_[i] + j, neighbour_id + t_neighb[i]+2-j);
	      attributes[neighbour_id + t_neighb[i]+2-j].does_vertex_exist_in_renault = 0;
	      attributes[neighbour_id + t_neighb[i]+2-j].vertex_is_open = 0;
	      attributes[id_in_graph + t_[i] + j].vertex_is_open = 0;
	      change__coord_attribute(id_in_graph, neighbour_id, i);
            }
        }
    }
    return graph;
}
void display_graph(igraph_t *graph, const char *filename) {
    FILE *outfile;
    char *colors[] = {"greenyellow", "gray70", "blue", "saddlebrown", "webpurple"};
    outfile = fopen(filename, "w");
    fprintf(outfile, "graph {\n");
//    fprintf(outfile, "  graph [layout = fdp , overlap = false, outputorder = edgesfirst, splines=true]\n");
    fprintf(outfile, "graph [pad=\"0.212,0.055\" bgcolor=lightgray ]\n");   
    fprintf(outfile, "  node [shape = circle, width=0.6]\n");
//    fprintf(outfile, "edge [fontsize=40] ");

    for (igraph_integer_t i = 0; i < igraph_vcount(graph); i++) {
        double x = 0.0, y = 0.0;
	x = attributes[i].coord.x;
	y = attributes[i].coord.y;
        fprintf(outfile, "  %ld [pos = \"%f, %f!\", label = \"%ld\", width = 0.6, style = filled, fillcolor=", 
                (long)i, x, y, (long)i);
	fprintf(outfile, "%s",colors[attributes[i].color]);
        fprintf(outfile, "]\n");
    }
    for (igraph_integer_t i = 0; i < igraph_ecount(graph); i++) {
        igraph_integer_t from, to;
        igraph_edge(graph, i, &from, &to);
        // Calculate the Euclidean distance between the two nodes
        double x1 = attributes[from].coord.x;
        double y1 = attributes[from].coord.y;
        double x2 = attributes[to].coord.x;
        double y2 = attributes[to].coord.y;
        double len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        fprintf(outfile, "  %ld -- %ld [len=%.2f];\n", (long)from, (long)to, len);    }
    fprintf(outfile, "}\n");
    fclose(outfile);
}

struct connected_components * get_components(igraph_t *graph){
  struct connected_components *con = malloc(sizeof(struct connected_components));
  igraph_vector_int_t *csize = malloc(sizeof(igraph_vector_int_t));
  igraph_vector_int_t *membership = malloc(sizeof(igraph_vector_int_t));  
  igraph_integer_t *no = malloc(sizeof(igraph_integer_t));
//  igraph_int_init(no, 0);  
  igraph_vector_int_init(csize, 0);
  igraph_vector_int_init(membership, 0);
  VECTOR(*csize)[0] = 0;
  VECTOR(*membership)[0] = 0;
  igraph_connected_components(graph, membership, csize, no,  IGRAPH_WEAK);
  con->csize = csize;
  con->membership = membership;
  con->no = no;
  return con;
}


igraph_vector_int_t * does_adding_ends_a_certain_component(igraph_t *graph, int id_in_graph, int direction, int vertex){
  int _t[4] = { 0, 3 , 6, 9};
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(graph, result, id_in_graph + _t[direction] + vertex, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);
  for (int i = 0 ; i < k; i++){
    if (attributes[VECTOR(*result)[i]].vertex_is_open == 1) return NULL;    
  }
  return result;
}


igraph_vector_ptr_t * does_adding_ends_at_least_a_component(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck){
  int d[4] ={0, 3, 6, 9,};
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  igraph_vector_ptr_t * components = malloc(sizeof(igraph_vector_ptr_t));
  igraph_vector_ptr_init(components, 0);  // size = 0
  graph = add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);
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

int added_score(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck){
  int s = 0;
  igraph_vector_int_t *components = does_adding_ends_at_least_a_component(g, t, neighbours_ids, id_in_deck);
  
  for (int i = 0; i < igraph_vector_ptr_size(components); i++) {
    igraph_vector_int_t *component = (igraph_vector_int_t *)igraph_vector_ptr_e(components, i);
    s += calculate_score_in_a_component(component);  
  }
  return s;
}

/*/players strategies


struct connected_components * find_least_component_from_one_side(igraph_t *g, struct tile_t t, int direction, int vertex){
  int _t[4] = {0, 3, 6, 9};
  enum color_t color = t.c[_t[direction] + vertex];
  igraph_graph_list_t *complist = malloc(sizeof(igraph_graph_list_t));
  igraph_t *component = malloc(sizeof(igraph_t));
  igraph_graph_list_init(&complist, 0);  
  igraph_decompose(g, complist, IGRAPH_WEAK, -1, 0);
  igraph_t * m = NULL;
  int i;
  int n = igraph_graph_list_size(complist);
  for (i = 0 ; i < n; ++i){
    component = igraph_graph_list_get_ptr(complist, i);
    if (attributes[VECTOR(*component)[i]].color == color){
      m = component;
      break;
    }
  }
  if (m == NULL) return NULL;
  for (int j = i; j < n; ++i){
    component = igraph_graph_list_get_ptr(complist, j);
    if ((attributes[VECTOR(*component)[j]].color == color) && (igraph_vcount(component) > igraph_vcounn(m))){
      m = component;
      break;
    }
  }
  return m;
}



//meeple functions


//int meeple_can_be_added(igraph_t *g, int vertex_in_graph)
void add_meeple(igraph_t *g, int vertex_in_graph){
  if (attributes[vertex_in_graph].is_there_meeple == 0) {
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(g, result, vertex_in_graph, IGRAPH_ALL);      
  int k = igraph_vector_int_size(result);
  for (int i = 0 ; i < k; i++){
  attributes[VECTOR(*result)[i]].is_there_meeple = 1;      
  }
  int id_in_graph = 13 * vertex_in_graph;
  for (int i =id_in_graph; i < 13; ++i){
    attributes[i].is_there_meeple = 1;
  }
  }
}

*/
