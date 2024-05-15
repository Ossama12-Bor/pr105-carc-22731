
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <assert.h>
void test_graph_add(void){
  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_empty(graph,0,IGRAPH_UNDIRECTED);
  int neighbours_ids[4]={-1,-1,-1,-1};  
  add_tile_to_graph(graph,CARC_TILE_INIT,neighbours_ids,0);
  assert(igraph_vcount(graph) == 13);
  assert(igraph_ecount(graph) == 9);
  neighbours_ids[0] = 0;
  add_tile_to_graph(graph, CARC_TILE_XROAD, neighbours_ids,1);      
  neighbours_ids[0] = -1; 
  neighbours_ids[3] = 1;
  add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,2);
  neighbours_ids[3] = 0;
  neighbours_ids[2] = 2;        
  add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,3);
  neighbours_ids[2] = 3;
  neighbours_ids[3] = -1;                
  add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,4);
  neighbours_ids[2] = 0;
  add_tile_to_graph(graph, CARC_TILE_INIT, neighbours_ids,5);
  display_graph(graph,"graph.dot");
  igraph_destroy(graph);
  free(graph);
}
void test_components(void) {

  igraph_t *test = malloc(sizeof(igraph_t));
  igraph_empty(test, 0, IGRAPH_UNDIRECTED);
  int tests[4] ={-1, -1, -1, -1};
  add_tile_to_graph(test, CARC_TILE_INIT, tests, 0);

  //tests for the first function
  for (int i = 0; i < 13; ++i){
    assert(does_adding_ends_a_certain_component(test, 0,i) == NULL);
      }
  tests[2] = 0;
  add_tile_to_graph(test , CARC_TILE_TINI, tests, 1);
  for (int i =6; i < 9; ++i){

    igraph_vector_int_t *result = does_adding_ends_a_certain_component(test, 13, i);    
    assert( result != NULL);
    igraph_vector_int_destroy(result) ;    	
    free(result);
      
  }
  printf("\n\n");
  igraph_vector_int_t *result = does_adding_ends_a_certain_component(test, 13, 6);
  igraph_vector_int_print(result);      
  assert( result != NULL);
  igraph_vector_int_destroy(result) ;    	
  free(result);
    

  printf("\n\n");
  for (int i =0; i < 3; ++i){
    assert(does_adding_ends_a_certain_component(test, 13, i + 9) == NULL);
    assert(does_adding_ends_a_certain_component(test, 13, i + 3) == NULL);
    assert(does_adding_ends_a_certain_component(test, 13, i) == NULL);      

  }
       
  tests[2] = 1;
  add_tile_to_graph(test , CARC_TILE_INIT, tests, 2);
  assert(does_adding_ends_a_certain_component(test, 26, 6) == NULL);
  tests[2] = -1;
  tests[3] = 2;
  add_tile_to_graph(test, CARC_TILE_XROAD, tests, 3);
  tests[3] = -1;
  tests[1] = 2;
  add_tile_to_graph(test, CARC_TILE_XROAD, tests, 4);    
  assert(does_adding_ends_a_certain_component(test, 39, 9) == NULL);
  igraph_vector_int_t *result1 = does_adding_ends_a_certain_component(test, 39, 10);
  igraph_vector_int_print(result1);      
  assert( result != NULL);
  igraph_vector_int_destroy(result1) ;    	
  free(result1);
    
  //tests for the second
  tests[0] = 3;
  tests[1] = -1;
  tests[2] = -1;
  tests[3] = 1;
  igraph_vector_ptr_t *components = set_of_new_finished_components_after_adding(test, CARC_TILE_XROAD, tests, 5);
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
  igraph_vector_ptr_t *components_2 = set_of_new_finished_components_after_adding(test, CARC_TILE_XROAD, tests, 5);
  for (int i = 0; i < igraph_vector_ptr_size(components_2); i++) {
    igraph_vector_int_t *vec = (igraph_vector_int_t *)igraph_vector_ptr_e(components_2, i);
    printf("Vector %d: ", i);
    igraph_vector_int_print(vec);
  }

  add_tile_to_graph(test, CARC_TILE_XROAD, tests, 5);

  tests[0] = 3;
  tests[1] = -1;
  tests[2] = -1;
  tests[3] = 1;    
  igraph_vector_ptr_t *   components_3 = set_of_new_finished_components_after_adding(test, CARC_TILE_XROAD, tests, 6);

  for (int i = 0; i < igraph_vector_ptr_size(components_3); i++) {
    igraph_vector_int_t *vec = (igraph_vector_int_t *)igraph_vector_ptr_e(components_3, i);
    printf("Vector %d: ", i);
    igraph_vector_int_print(vec);
  }
  printf("\n%ld\n",igraph_vector_ptr_size(components));
    

  display_graph(test,"test.dot");
  free_components(components);
  free_components(components_2);
  free_components(components_3);            
  igraph_destroy(test);
  free(test);

}

void test_score(void){

  igraph_t *graph = malloc(sizeof(igraph_t));
  igraph_empty(graph,0,IGRAPH_UNDIRECTED);
  int tests[4]={-1,-1,-1,-1};  
  add_tile_to_graph(graph,CARC_TILE_INIT,tests,0);
  tests[0] = 0;
  int s = added_score(graph, CARC_TILE_GREEN,tests ,1);
  assert(s == 0);

  add_tile_to_graph(graph, CARC_TILE_GREEN,tests ,1);
  tests[0] = -1;
  tests[3] = 1;
  s += added_score(graph, CARC_TILE_GREEN,tests ,2);
  assert(s == 0);
  add_tile_to_graph(graph, CARC_TILE_GREEN,tests ,2);
  tests[3] = -1;
  tests[1] = 0;
  s += added_score(graph, CARC_TILE_XROAD,tests ,3);
  assert(s == 0);
  assert(number_of_vertices_in_new_component(graph,CARC_TILE_XROAD,tests,3,4) == 4);   
  add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,3);
  tests[1] = -1;
  tests[2] = 3;    
  s += added_score(graph, CARC_TILE_XROAD,tests ,4);
  assert(s == 4);
  add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,4);
  tests[2] = -1;
  tests[1] = 3;
  s += added_score(graph, CARC_TILE_TINI,tests ,5);
  assert(s == 4);
  add_tile_to_graph(graph, CARC_TILE_TINI,tests ,5);
  tests[0] = 5;
  tests[1] = -1;
  s += added_score(graph, CARC_TILE_INIT,tests ,6);
  assert(s == 28);
  add_tile_to_graph(graph, CARC_TILE_INIT,tests ,6);
  tests[0] = -1;    
  tests[2] = 0;
  tests[3] = 4;
  s += added_score(graph, CARC_TILE_TINI,tests ,7);
  assert(s == 52);
  add_tile_to_graph(graph, CARC_TILE_TINI,tests ,7);

  //meeple functions

   
  assert(meeple_can_be_added(graph, 0));
  add_meeple(graph,0,0);
  for (int i = 0 ; i < 13; ++i){
    assert(meeple_can_be_added(graph, i) == 0);
  }
  assert(which_player_has_more_meeples_in_component(graph, 98) == 0);
  assert(meeple_can_be_added(graph, 42));
  add_meeple(graph,42,1);
  add_meeple(graph,62,1);
  assert(which_player_has_more_meeples_in_component(graph, 42) == 1);
  assert(which_player_has_more_meeples_in_component(graph, 46) == -1);
  tests[1] = 4;
  tests[2] = 5;
  tests[3] = -1;
  enum color_t brown = BROWN;
  igraph_vector_int_t *result2 = get_biggest_component_of_player_in_a_position(graph,CARC_TILE_XROAD,tests,8,0,brown,INFINITE_MEEPLE, 7);
  igraph_vector_int_print(result2);
  igraph_vector_int_print(result2);
  igraph_vector_int_destroy(result2) ;
  free(result2);
  tests[1] = -1;
  tests[2] = 2;
  tests[3] = 0;
  add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,8);
  tests[1] = -1;
  tests[2] = 8;
  tests[3] = 7;
  igraph_vector_int_t *result3 = get_biggest_component_of_player_in_a_position(graph,CARC_TILE_XROAD,tests,9,1,1,INFINITE_MEEPLE, -1);
  igraph_vector_int_print(result3);
  igraph_vector_int_print(result3);
  igraph_vector_int_destroy(result3) ;
  free(result3);
  add_meeple(graph,105,0);
  add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,9);
  assert(meeple_can_be_added(graph,124) == 0);
  assert(meeple_can_be_added(graph,104) == 0);
  assert(meeple_can_be_added(graph,106) == 0);
  assert(meeple_can_be_added(graph,120));
  assert(meeple_can_be_added(graph,119));
  assert(meeple_can_be_added(graph,126) == 0);
  tests[0] = 3;
  tests[1] = 1;
  tests [2] = -1;
  tests[3] = 6;
  igraph_vector_int_t *result4 = get_biggest_component_of_player_in_a_position(graph,CARC_TILE_XROAD,tests,10,0,1,NO_MEEPLE, -1);
  igraph_vector_int_print(result4);
  igraph_vector_int_destroy(result4) ;
  free(result4);
  
  add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,10);
  tests[0] = -1;
  tests[1] = 4;
  tests[2] = 5;
  tests[3] = -1;
  int position = meeple_can_be_added_in_a_position(graph, CARC_TILE_INIT, 11,tests );
  assert(meeple_can_be_added(graph, 105) == 0);
  assert(retrieve_meeples(graph, 104/13, 0) == 1);
  assert(meeple_can_be_added(graph, 105));
  add_meeple(graph, 43, 1);
  assert(meeple_can_be_added(graph, 10) == 0);
  assert(retrieve_meeples(graph, 0, 0) == 1);
  assert(retrieve_meeples(graph, 0, 1) == 0);
  display_graph(graph,"test.dot");
    
  igraph_destroy(graph);
  free(graph);
}
int main() {    
//          test_graph_add();
//     test_components();  
  test_score();
  return 0;
}
