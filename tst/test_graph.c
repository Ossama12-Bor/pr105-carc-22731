
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <assert.h>
int main() {
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

  igraph_bool_t are_adjacent;
    igraph_t *graph_1 = create_graph_for_tile(CARC_TILE_INIT);
    assert(igraph_vcount(graph_1) == 13);
    assert(igraph_ecount(graph_1) == 9);
    igraph_are_adjacent(graph_1, 0 , 1, &are_adjacent);
    assert(are_adjacent);
    igraph_are_adjacent(graph_1, 11 , 3, &are_adjacent);
    assert(are_adjacent);
    igraph_are_adjacent(graph_1, 12 , 4, &are_adjacent);
//    assert( are_adjacent);            
    igraph_are_adjacent(graph_1, 11 , 1, &are_adjacent);
    assert( ! are_adjacent);        
    igraph_t *graph_2 = create_graph_for_tile(CARC_TILE_GREEN);
    int neighbours_ids[4]={0,-1,-1,-1};
    igraph_t *graph = add_tile_to_graph(graph_1, CARC_TILE_XROAD, neighbours_ids,1);      
    neighbours_ids[0] = -1; 
    neighbours_ids[3] = 1;
    graph = add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,2);
    for (int i = 0 ; i < 25; ++i){
//      attributes[i]
      printf("%d\n",attributes[i].color);
    }
    neighbours_ids[3] = 0;
    neighbours_ids[2] = 2;        
    graph = add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,3);    
    /* igraph_are_adjacent(graph, 13 , 8, &are_adjacent); */
    /* assert(are_adjacent); */
    /* igraph_are_adjacent(graph, 14 , 7, &are_adjacent); */
    /*     assert(are_adjacent);     */
    /* igraph_are_adjacent(graph, 15 , 6, &are_adjacent); */
    /*     assert(are_adjacent);     */
    /* igraph_are_adjacent(graph, 16 , 37, &are_adjacent); */
    /*  assert(are_adjacent);     */
    /* igraph_are_adjacent(graph, 17 , 36, &are_adjacent); */
    /* assert(are_adjacent);     */
    /* igraph_are_adjacent(graph, 18 , 35, &are_adjacent); */
    /*  assert(are_adjacent); */
    /* igraph_are_adjacent(graph, 19 , 34, &are_adjacent); */
    /* assert(! are_adjacent);     */

    display_graph(graph,"graph.dot");

    igraph_destroy(graph);


    igraph_destroy(graph);

    return 0;
}
