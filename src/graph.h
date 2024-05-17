#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "deck.h"
#include "move.h"
#include <igraph.h>

/* 
 * Structure representing the coordinates of a node in a graph, primarily useful for visualization purposes.
 */

struct coord{
  int x,y;
};

/* 
 * Structure describing attributes/information about nodes in a graph.
 */
 
struct attribute {
    int is_there_meeple[2]; // Array indicating if player 0 or 1 has a meeple on this node
    int does_vertex_exist_in_renault; // Flag indicating if the vertex exists in Renault
    enum color_t color; // Color of the node
    int vertex_is_open; // Flag indicating if another edge can be added to this node when adding other tiles
    struct coord coord; // Coordinates of this node for display purposes
    int already_added_to_a_component; // Flag indicating if the node has already been visited in another component
};

/* Section 1 : adding a Tile to graph functions */

/* Function to add edges between nodes to represent the tile given as a parameter, where its id in the graph of the board is id_in_graph */

igraph_t *create_graph_for_tile(igraph_t *graph, int id_in_graph, struct tile_t t);

/* 
 * After creating a graph for a tile, this function adds edges between the tile and its neighbor.
 * The neighbour_id is the ID of the neighbor in the deck, and direction specifies the position of this neighbor relative to the new tile placement (0 for up, 1 for right, 2 for down, 3 for left).
 */


void add_tile_to_graph(igraph_t *graph, struct tile_t t, int neighbours_ids[4], int id_in_deck) ;

/* Section 2 : Score Functions */

/* 
 * Function to determine if adding a tile will complete a connected component represented by the vertex at the index specified by the enum conn_t vertex in the tile. 
 * Returns NULL if the connected component represented by vertex is not completed, otherwise returns the connected component.
 */



igraph_vector_int_t * does_adding_ends_a_certain_component(igraph_t *g, int id_in_graph, enum conn_t vertex);

/* 
 * Function that returns a set (in the form of a pointer) containing all the components that will be completed  if a tile is added in a specific position, without modifiying g.
 * This function adds the specified tile to a copied graph and computes the connected components
 */


igraph_vector_ptr_t * set_of_new_finished_components_after_adding(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck);

/* Function to calculate the score of a completed component according to Carcassonne rules */

int calculate_score_in_a_component(igraph_vector_int_t *component);

/* Function to calculate the additional score if a specific tile is added to the graph g in a certain position, without modifying graph g */

int added_score(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck);

void free_components(igraph_vector_ptr_t *components) ;

/* Section 3 : Player Strategies */

/* 
 * Function to calculate the number of vertices represented by a specific vertex (of type enum conn_t) in a tile after being added to the graph. The tile is identified by id_in_deck.
 */

int number_of_vertices_in_new_component(igraph_t *g, struct tile_t t, int neighbours_ids[4], int id_in_deck, enum conn_t vertex);

/* 
 * Function to calculate the largest finished connected component that will be completed after adding a tile 
 * (identified by id_in_deck) to a specific position. The cmode parameter denotes the game mode. 
 * The player_id parameter is used for modes involving meeples (finite or infinite). 
 * The n_meeples parameter indicates the number of meeples the player possesses, relevant only in finite mode.
 */

igraph_vector_int_t * get_biggest_component_of_player_in_a_position(igraph_t *g, struct tile_t t, int neighbours_ids[4],  int id_in_deck , int player_id, enum color_t color, enum gamemode_t mode, int n_meeples);

/*  Section 4 : Meeple functions*/

/* 
 * Given an index in the graph, this function returns whether a meeple can be added. 
 * A meeple can be added if the component represented by this meeple does not already contain a meeple 
 * and the tile containing this vertex does not contain a meeple.
 */



int meeple_can_be_added(igraph_t *g, int index_in_graph);

/* 
 * Function that calculates the number of meeples each player has in a component represented by the node of index index_in_graph and returns the ID of the player 
 * with the most meeples. Returns -1 in case of a tie.
 */


int which_player_has_more_meeples_in_component(igraph_t *g, int index_in_graph);

/* 
 * Function to determine if a meeple can be added when a tile of id id_in_deck is added to a specific position.
 * Returns the index where a meeple can be added if possible, otherwise returns -1.
 */

int meeple_can_be_added_in_a_position(igraph_t *g, struct tile_t t, int id_in_deck, int neighbours_ids[4]);

void add_meeple(igraph_t *g, int index_in_graph, int player_id);

/* 
 * When finishing a component after adding a tile of id id_in_deck, the players retrieve their meeples from the component. 
 * This function facilitates this process and returns the number of meeples retrieved by the player with ID player_id.
 */


int retrieve_meeples(igraph_t *g, int id_in_deck, int player_id);

/* Section 4 : Displaying Function*/

/* 
 * This function generates a .dot file representing the graph for visualization purposes after executing. 
 * To compile the generated .dot file, execute the following command:
 * dot -Kfdp -n -Tpng -o test.png test.dot
 * If the graph is not compiled using this command, the result may not be visually pleasant.
 */


void display_graph(igraph_t *graph, const char *filename);


#endif
