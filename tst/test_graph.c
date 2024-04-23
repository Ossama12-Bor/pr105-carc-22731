
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <assert.h>
void test_graph_add(void){
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_empty(graph,0,IGRAPH_UNDIRECTED);
    int neighbours_ids[4]={-1,-1,-1,-1};  
    igraph_t *graph_1 = add_tile_to_graph(graph,CARC_TILE_INIT,neighbours_ids,0);
    assert(igraph_vcount(graph_1) == 13);
    assert(igraph_ecount(graph_1) == 9);
    neighbours_ids[0] = 0;
    graph = add_tile_to_graph(graph_1, CARC_TILE_XROAD, neighbours_ids,1);      
    neighbours_ids[0] = -1; 
    neighbours_ids[3] = 1;
    graph = add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,2);
    neighbours_ids[3] = 0;
    neighbours_ids[2] = 2;        
    graph = add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,3);
    neighbours_ids[2] = 3;
    neighbours_ids[3] = -1;                
    graph = add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,4);
    neighbours_ids[2] = 0;
    graph = add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,5);
    display_graph(graph,"graph.dot");
  igraph_destroy(graph);
}
void test_components(void){

   igraph_t *test = malloc(sizeof(igraph_t));
    igraph_empty(test, 0, IGRAPH_UNDIRECTED);
    int tests[4] ={-1, -1, -1, -1};
    igraph_t *test_1 = add_tile_to_graph(test, CARC_TILE_INIT, tests, 0);

    //tests for the first function
    for (int i = 0; i < 3; ++i){
    assert(does_adding_ends_a_certain_component(test, 0,0,i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 0,1,i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 0,2,i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 0,3,i) == NULL);
    }
    tests[2] = 0;
    test = add_tile_to_graph(test , CARC_TILE_TINI, tests, 1);
    for (int i =0; i < 3; ++i){
    assert(does_adding_ends_a_certain_component(test, 13, 2, i) != NULL);
    }
    printf("\n\n");
      igraph_vector_int_print(does_adding_ends_a_certain_component(test, 13, 2, 0));
      printf("\n\n");
    for (int i =0; i < 3; ++i){
    assert(does_adding_ends_a_certain_component(test, 13, 3, i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 13, 1, i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 13, 0, i) == NULL);      

    }
    
    tests[2] = 1;
    test = add_tile_to_graph(test , CARC_TILE_INIT, tests, 2);
    assert(does_adding_ends_a_certain_component(test, 26, 2, 0) == NULL);
    tests[2] = -1;
    tests[3] = 2;
    test = add_tile_to_graph(test, CARC_TILE_XROAD, tests, 3);
    tests[3] = -1;
    tests[1] = 2;
    test = add_tile_to_graph(test, CARC_TILE_XROAD, tests, 4);    
    assert(does_adding_ends_a_certain_component(test, 39, 3, 0) == NULL);
    assert(does_adding_ends_a_certain_component(test, 39, 3, 1) != NULL);
      igraph_vector_int_print(does_adding_ends_a_certain_component(test, 39, 3, 1));    
    
    //tests for the second function
    tests[0] = 3;
    tests[1] = -1;
    tests[2] = -1;
    tests[3] = 1;
   igraph_vector_ptr_t *components = does_adding_ends_at_least_a_component(test, CARC_TILE_XROAD, tests, 5);
//    test = add_tile_to_graph(test,CARC_TILE_XROAD, tests, 5);
    assert(igraph_vector_ptr_size(components) != 0);
      for (int i = 0; i < igraph_vector_ptr_size(components); i++) {
        igraph_vector_int_t *vec = (igraph_vector_int_t *)igraph_vector_ptr_e(components, i);
        printf("Vector %d: ", i);
        igraph_vector_int_print(vec);
    }
      printf("\n%ld\n",igraph_vector_ptr_size(components));

//    assert(compo->size != 0);
      tests[0] = 4;
      tests[1] = 1;
      tests[3] = -1;
      igraph_vector_ptr_t *components_2 = does_adding_ends_at_least_a_component(test, CARC_TILE_XROAD, tests, 5);
      for (int i = 0; i < igraph_vector_ptr_size(components_2); i++) {
        igraph_vector_int_t *vec = (igraph_vector_int_t *)igraph_vector_ptr_e(components_2, i);
        printf("Vector %d: ", i);
        igraph_vector_int_print(vec);
      }

    test = add_tile_to_graph(test, CARC_TILE_XROAD, tests, 5);

    tests[0] = 3;
    tests[1] = -1;
    tests[2] = -1;
    tests[3] = 1;    
    components = does_adding_ends_at_least_a_component(test, CARC_TILE_XROAD, tests, 6);

      for (int i = 0; i < igraph_vector_ptr_size(components); i++) {
        igraph_vector_int_t *vec = (igraph_vector_int_t *)igraph_vector_ptr_e(components, i);
        printf("Vector %d: ", i);
        igraph_vector_int_print(vec);
    }
      printf("\n%ld\n",igraph_vector_ptr_size(components));
    

    display_graph(test,"test.dot");

}

void test_score(void){
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_empty(graph,0,IGRAPH_UNDIRECTED);
    int tests[4]={-1,-1,-1,-1};  
    igraph_t *graph_1 = add_tile_to_graph(graph,CARC_TILE_INIT,tests,0);
  tests[0] = 0;
    int s = added_score(graph_1, CARC_TILE_GREEN,tests ,1);
    assert(s == 0);
    graph = add_tile_to_graph(graph, CARC_TILE_GREEN,tests ,1);
    tests[0] = -1;
    tests[3] = 1;
    s += added_score(graph, CARC_TILE_GREEN,tests ,2);
    assert(s == 0);
    graph = add_tile_to_graph(graph, CARC_TILE_GREEN,tests ,2);
    tests[3] = -1;
    tests[1] = 0;
    s += added_score(graph, CARC_TILE_XROAD,tests ,3);
    assert(s == 8);
    graph = add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,3);
    tests[1] = -1;
    tests[2] = 3;    
    s += added_score(graph, CARC_TILE_XROAD,tests ,4);
    assert(s == 20);
    graph = add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,4);
    tests[2] = -1;
    tests[1] = 3;
    s += added_score(graph, CARC_TILE_TINI,tests ,5);
    assert(s == 20);
    graph = add_tile_to_graph(graph, CARC_TILE_TINI,tests ,5);
    
    
    
    display_graph(graph,"test.dot");    
    }
int main() {    
//  test_graph_add();
//  test_components();  
  test_score();
    return 0;
}
