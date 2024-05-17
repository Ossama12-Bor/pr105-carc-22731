#include "graph.h"
#define NUM_TILES 72


  
struct attribute attributes[13*NUM_TILES];


/* Section 1 : adding a Tile to graph functions */

/* Function to initialize the coordinates of the first tile (Tile with id = 0) */

void initialize_coordinates_of_first_tile(){
  int coords[13][2] = {
    {-1, 2}, {0, 2}, {1, 2}, {2, 1}, {2, 0}, {2, -1},
    {1, -2}, {0, -2}, {-1, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {0, 0}
  };

  for (int i = 0; i < 13; i++) {
    attributes[i].coord.x = coords[i][0];
    attributes[i].coord.y = coords[i][1];
  }  
  
}


/* Function to add edges between nodes to represent the tile given as a parameter, where its id in the graph of the board is id_in_graph */

igraph_t *create_graph_for_tile(igraph_t *graph, int id_in_graph, struct tile_t t){
  if (id_in_graph == 0){
    initialize_coordinates_of_first_tile(); //Treating the First tile of id = 0 separately to initialize it's Coordinates
  }
  for (int i = 0; i < 13; ++i){
    for (int j = i-1; j >= 0; --j){
      if (t.t[i] == t.t[j]) {
	igraph_add_edge(graph,id_in_graph +  i, id_in_graph + j);  //adding edges
	break;
      }
    }
  }
  return graph; 
}

/* Function to initialize attributes for the new 13 vertices of the graph */


void initialize_new_tile(struct tile_t t,int id_in_graph){
  for(int i = id_in_graph ; i < id_in_graph + 13; ++i){
    attributes[i].does_vertex_exist_in_renault = 1;
    attributes[i].color = t.c[i-id_in_graph];
    attributes[i].vertex_is_open = 1;
    attributes[i].is_there_meeple[0] = 0;
    attributes[i].is_there_meeple[1] = 0;
  }
}

/* Update the coordinates of the new tile added to the graph.  */
/* The new tile will be placed 5 units away from its neighbor on either the x-axis or y-axis. */

void change__coord_attribute(int id_in_graph, int neighbour_id, int k){
  int t[4][2] = {{0, -5}, {-5, 0}, {0, 5}, {5, 0}};
  for (int i = 0; i < 13; ++i){
    attributes[i + id_in_graph].coord.x = attributes[neighbour_id + i].coord.x+t[k][0];
    attributes[i + id_in_graph].coord.y = attributes[neighbour_id + i].coord.y+t[k][1];    
  }
}


/* 
 * After creating a graph for a tile, this function adds edges between the tile and its neighbor.
 * The neighbour_id is the ID of the neighbor in the deck, and direction specifies the position of this neighbor relative to the new tile placement (0 for up, 1 for right, 2 for down, 3 for left).
 */


void add_edges_between_vertices(igraph_t *graph, int id_in_graph, int neighbour_id, int direction){
  int t_neighb[4]= { 6, 9, 0, 3};
  int t_[4]= { 0, 3, 6, 9};  
//  int neighbour_id = 13 * neighbours_ids[direction];
  for (int j = 0; j < 3; j++) {
    igraph_add_edge(graph, id_in_graph + t_[direction] + j, neighbour_id + t_neighb[direction]+2-j);
    attributes[neighbour_id + t_neighb[direction]+2-j].does_vertex_exist_in_renault = 0;
    attributes[neighbour_id + t_neighb[direction]+2-j].vertex_is_open = 0;
    attributes[id_in_graph + t_[direction] + j].vertex_is_open = 0;
    change__coord_attribute(id_in_graph, neighbour_id, direction);
  }
}

/*
 * Function to add a tile to the board graph. 
 * The neighbours_ids array provides the IDs of the neighboring tiles in the following order: up, right, down, and left.
 * The id_in_deck integer is the ID of the tile we want to add in the deck.
 */

void add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) {
  int id_in_graph = 13 * id_in_deck;  
  initialize_new_tile(t,id_in_graph);
  attributes[id_in_graph + 12].vertex_is_open = 0;
  igraph_add_vertices(graph, 13, NULL);
  create_graph_for_tile(graph, id_in_graph, t);  
  for (int direction = 0; direction < 4; direction++) {
    if (neighbours_ids[direction] != -1) {
      add_edges_between_vertices(graph, id_in_graph, 13 * neighbours_ids[direction], direction);
    }
  }
}




/* Section 2 : Score Functions */


/* 
 * Function to determine if adding a tile will complete a connected component represented by the vertex at the index specified by the enum conn_t vertex in the tile. 
 * Returns NULL if the connected component represented by vertex is not completed, otherwise returns the connected component.
 */

igraph_vector_int_t * does_adding_ends_a_certain_component(igraph_t *graph, int id_in_graph, enum conn_t vertex){
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(graph, result, id_in_graph + vertex, IGRAPH_ALL);
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

/* 
 * Function that returns a set (in the form of a pointer) containing all the components that will be completed  if a tile is added in a specific position, without modifiying g.
 * This function adds the specified tile to a copied graph and computes the connected components
 */

igraph_vector_ptr_t * set_of_new_finished_components_after_adding(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck){
  int d[4] ={0, 3, 6, 9,};
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  igraph_vector_ptr_t * components = malloc(sizeof(igraph_vector_ptr_t));
  igraph_vector_ptr_init(components, 0); 
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);
  int id_in_graph = 13 * id_in_deck;
  for (int i = 0; i < 13; ++i){
    
    // No need to recalculate the component of the index if it's already been calculated
    
    if (attributes[id_in_graph + i].already_added_to_a_component == 0){
      igraph_vector_int_t *component = does_adding_ends_a_certain_component(graph,id_in_graph, i);
      if (component != NULL){ // Verifiying if the component represented by the node of index id_in_graph + i in the graph is finished
	int k = igraph_vector_int_size(component);
	
	// Mark nodes in the component as already added to a component
	
	for (int l = 0 ; l < k; l++){
	  if (VECTOR(*component)[l] >= id_in_graph)
	    attributes[VECTOR(*component)[l]].already_added_to_a_component = 1;
	}
	  
	/* Adding component to components if it's finished*/
	
	igraph_vector_ptr_push_back(components, component);
      }
    }
  }

   /* 
     * Handle the special case for the middle node (enum conn_t 12). 
     * If it forms a connected component by itself (e.g., the middle node in XROAD), add it separately.
     */
  igraph_integer_t degree;
  igraph_degree_1(graph, &degree, id_in_graph + 12, IGRAPH_ALL, 0);
  
  if (attributes[id_in_graph + 12].already_added_to_a_component == 0 && degree == 0){
    attributes[id_in_graph + 12].already_added_to_a_component = 1;    
    igraph_vector_int_t *middle = malloc(sizeof(igraph_t));
    igraph_vector_int_init(middle, 0);
    igraph_vector_int_push_back(middle, id_in_graph + 12);
    igraph_vector_ptr_push_back(components, middle);        
  }
  
  //Reset used attributes to their initial state for future use
  
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

/* Function to calculate the score of a completed component according to Carcassonne rules */

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

/* Function to calculate the additional score if a specific tile is added to the graph g, without modifying graph g */

int added_score(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck){
  int s = 0;
  igraph_vector_int_t *components = set_of_new_finished_components_after_adding(g, t, neighbours_ids, id_in_deck);
  
  for (int i = 0; i < igraph_vector_ptr_size(components); i++) {
    igraph_vector_int_t *component = (igraph_vector_int_t *)igraph_vector_ptr_e(components, i);
    s += calculate_score_in_a_component(component);  
  }
  free_components(components);
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


/* Section 3 : Player Strategies */

/* 
 * Function to calculate the number of vertices represented by a specific vertex (of type enum conn_t) in a tile after being added to the graph. The tile is identified by id_in_deck.
 */


int number_of_vertices_in_new_component(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck, enum conn_t vertex){
  int id_in_graph = id_in_deck * 13 ;  
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);  
  igraph_vector_int_t *result = malloc(sizeof(igraph_vector_int_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(graph, result, id_in_graph + vertex, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);
  igraph_vector_int_destroy(result) ;    	
  free(result);
  igraph_destroy(graph);
  free(graph);  
  return k;
}

/* 
 * Function to calculate the largest finished connected component that will be completed after adding a tile 
 * (identified by id_in_deck) to a specific position. The cmode parameter denotes the game mode. 
 * The player_id parameter is used for modes involving meeples (finite or infinite). 
 * The n_meeples parameter indicates the number of meeples the player possesses, relevant only in finite mode.
 */


igraph_vector_int_t * get_biggest_component_of_player_in_a_position(igraph_t *g, struct tile_t t, int neighbours_ids[4],  int id_in_deck , int player_id, enum color_t color, enum gamemode_t mode, int n_meeples){
  int id_in_graph = 13 * id_in_deck;
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  igraph_vector_int_t *result = malloc(sizeof(igraph_vector_int_t));
  igraph_vector_int_init(result, 0);  
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);
  int size =0;
  for (int i = 0; i < 13; ++i){
      igraph_vector_int_t *result_test = does_adding_ends_a_certain_component(graph, id_in_graph, i);
      if (result_test != NULL){
	int size_test = igraph_vector_int_size(result_test);
	if (attributes[id_in_graph + i].color == color && (size_test > size) && (which_player_has_more_meeples_in_component(graph, id_in_graph + i) == player_id || mode == NO_MEEPLE)){
	  size = size_test;
	  if (size_test > 0) {
	    igraph_vector_int_destroy(result);
	    free(result);
	  }
	  result = result_test;
	
	} else {
	  igraph_vector_int_destroy(result_test);
	  free(result_test);
	}
      }
  }  
  igraph_destroy(graph);
  free(graph);  
  return result;
}


/*  Section 4 : Meeple functions*/

/* 
 * Given an index in the graph, this function returns whether a meeple can be added. 
 * A meeple can be added if the component represented by this meeple does not already contain a meeple 
 * and the tile containing this vertex does not contain a meeple.
 */

int meeple_can_be_added(igraph_t *g, int index_in_graph){
  int id_in_graph = index_in_graph - index_in_graph%13;
  
  // Check if there is a meeple in any part of the tile
  
  for (int i = id_in_graph; i < id_in_graph + 13; ++i){
    if (attributes[i].is_there_meeple[0] || attributes[i].is_there_meeple[1]) return 0;
  }
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(g, result, index_in_graph, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);

  // Check if there is a meeple in the component
  
  for (int i = 0 ; i < k; i++){
    if (attributes[VECTOR(*result)[i]].is_there_meeple[0] || attributes[VECTOR(*result)[i]].is_there_meeple[1]) {
      igraph_vector_int_destroy(result) ;    	
      free(result);
      return 0;
  }}
  igraph_vector_int_destroy(result) ;    	
  free(result);    
  return 1;
}

/* 
 * Function that calculates the number of meeples each player has in a component represented by the node of index index_in_graph and returns the ID of the player 
 * with the most meeples. Returns -1 in case of a tie.
 */

int which_player_has_more_meeples_in_component(igraph_t *g, int index_in_graph){
  int player_0_number = 0;
  int player_1_number = 0;
  igraph_vector_int_t *result = malloc(sizeof(igraph_t));
  igraph_vector_int_init(result, 0);
  igraph_subcomponent(g, result, index_in_graph, IGRAPH_ALL);
  int k = igraph_vector_int_size(result);
  for (int i = 0 ; i < k; i++){
    if (attributes[VECTOR(*result)[i]].is_there_meeple[0]) player_0_number++;
    if (attributes[VECTOR(*result)[i]].is_there_meeple[1]) player_1_number++;  
  }
  igraph_vector_int_destroy(result) ;    	
  free(result);      
  if (player_1_number == player_0_number) return -1 ;
  return (player_1_number > player_0_number);
}


void add_meeple(igraph_t *g, int index_in_graph, int player_id){
  if (meeple_can_be_added(g,index_in_graph)) {
    attributes[index_in_graph].is_there_meeple[player_id] = 1;
  }
}

/* 
 * Function to determine if a meeple can be added when a tile of id id_in_deck is added to a specific position.
 * Returns the index where a meeple can be added if possible, otherwise returns -1.
 */


int meeple_can_be_added_in_a_position(igraph_t *g, struct tile_t t, int id_in_deck, int neighbours_ids[4]){
  int id_in_graph = id_in_deck * 13 ;  
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_copy(graph,g);
  add_tile_to_graph(graph, t, neighbours_ids, id_in_deck);
  for (int i = id_in_graph; i < id_in_graph + 13; ++i){
    if (meeple_can_be_added(graph, i)) {
      igraph_destroy(graph);
      free(graph);
      return i;
  }
    }
    igraph_destroy(graph);
    free(graph);
    
  return -1;
}

/* 
 * When finishing a component after adding a tile of id id_in_deck, the players retrieve their meeples from the component. 
 * This function facilitates this process and returns the number of meeples retrieved by the player with ID player_id.
 */

int retrieve_meeples(igraph_t *g, int id_in_deck, int player_id){  
  int s = 0;
  int id_in_graph = 13 * id_in_deck;
  for (int i = 0; i < 13; ++i){
      if (attributes[id_in_graph + i].already_added_to_a_component == 0){
	igraph_vector_int_t *component = does_adding_ends_a_certain_component(g,id_in_graph, i);
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
	  igraph_vector_int_destroy(component) ;    	
	  free(component);    
	  
	}
      }
  }
    for (int i = id_in_graph; i < id_in_graph + 13; ++i){
    attributes[i].already_added_to_a_component = 0;
  }
  return s;
}

/* Section 4 : Displaying Function*/

/* 
 * This function generates a .dot file representing the graph for visualization purposes after executing. 
 * To compile the generated .dot file, execute the following command:
 * dot -Kfdp -n -Tpng -o test.png test.dot
 * If the graph is not compiled using this command, the result may not be visually pleasant.
 */

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
      fprintf(outfile, "black"); 

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
