#include <igraph.h>
#include <stdio.h>
#include <stdlib.h>
int main() {

    igraph_t *graph = create_graph_for_tile(CARC_TILE_INIT);
    

    FILE *dot_file = fopen("graph.dot", "w");
    igraph_write_graph_dot(graph, dot_file);

    fclose(dot_file);

    igraph_destroy(graph);

    return 0;
}
