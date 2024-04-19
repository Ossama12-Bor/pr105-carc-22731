
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <assert.h>
int main() {
  igraph_bool_t are_adjacent;
    igraph_t *graph_1 = create_graph_for_tile(CARC_TILE_INIT);
    assert(igraph_vcount(graph_1) == 13);
    assert(igraph_ecount(graph_1) == 9);
    igraph_are_adjacent(graph_1, 0 , 1, &are_adjacent);
    assert(are_adjacent);
    igraph_are_adjacent(graph_1, 11 , 3, &are_adjacent);
    assert(are_adjacent);    
    igraph_are_adjacent(graph_1, 11 , 1, &are_adjacent);
    assert( ! are_adjacent);        
    igraph_t *graph_2 = create_graph_for_tile(CARC_TILE_GREEN);
    int neighbours_ids[4]={0,-1,-1,-1};
    igraph_t *graph = add_tile_to_graph(graph_1, CARC_TILE_GREEN, neighbours_ids,1);      
    neighbours_ids[0] = -1;
    neighbours_ids[3] = 1;        
    graph = add_tile_to_graph(graph, CARC_TILE_GREEN, neighbours_ids,2);    
    igraph_are_adjacent(graph, 13 , 8, &are_adjacent);
    assert(are_adjacent);
    igraph_are_adjacent(graph, 14 , 7, &are_adjacent);
        assert(are_adjacent);    
    igraph_are_adjacent(graph, 15 , 6, &are_adjacent);
        assert(are_adjacent);    
    igraph_are_adjacent(graph, 16 , 37, &are_adjacent);
     assert(are_adjacent);    
    igraph_are_adjacent(graph, 17 , 36, &are_adjacent);
    assert(are_adjacent);    
    igraph_are_adjacent(graph, 18 , 35, &are_adjacent);
     assert(are_adjacent);
    igraph_are_adjacent(graph, 19 , 34, &are_adjacent);
    assert(! are_adjacent);    
    FILE *dot_file = fopen("graph.dot", "w");
    igraph_write_graph_dot(graph, dot_file);

    fclose(dot_file);

    igraph_destroy(graph);

    return 0;
}
