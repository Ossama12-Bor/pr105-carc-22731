
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
    for (int i = 0; i < 3; ++i){
                assert(does_adding_ends_a_certain_component(test, 0,0,i) == NULL);
    
	  assert(does_adding_ends_a_certain_component(test, 0,1,i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 0,2,i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 0,3,i) == NULL);
    }
        tests[2] = 0;
    add_tile_to_graph(test , CARC_TILE_TINI, tests, 1);
    for (int i =0; i < 3; ++i){
      igraph_vector_int_t *result = does_adding_ends_a_certain_component(test, 13, 2, i);
	assert( result != NULL);
      igraph_vector_int_destroy(result) ;    	
      free(result);
      
    }
    printf("\n\n");
      igraph_vector_int_t *result = does_adding_ends_a_certain_component(test, 13, 2, 0);
      igraph_vector_int_print(result);      
	assert( result != NULL);
      igraph_vector_int_destroy(result) ;    	
      free(result);
    

      printf("\n\n");
    for (int i =0; i < 3; ++i){
    assert(does_adding_ends_a_certain_component(test, 13, 3, i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 13, 1, i) == NULL);
    assert(does_adding_ends_a_certain_component(test, 13, 0, i) == NULL);      

    }
       
    tests[2] = 1;
    add_tile_to_graph(test , CARC_TILE_INIT, tests, 2);
    assert(does_adding_ends_a_certain_component(test, 26, 2, 0) == NULL);
        tests[2] = -1;
    tests[3] = 2;
    add_tile_to_graph(test, CARC_TILE_XROAD, tests, 3);
    tests[3] = -1;
    tests[1] = 2;
    add_tile_to_graph(test, CARC_TILE_XROAD, tests, 4);    
    assert(does_adding_ends_a_certain_component(test, 39, 3, 0) == NULL);
    igraph_vector_int_t *result1 = does_adding_ends_a_certain_component(test, 39, 3, 1);
      igraph_vector_int_print(result1);      
	assert( result != NULL);
      igraph_vector_int_destroy(result1) ;    	
      free(result1);
    
      //    assert(does_adding_ends_a_certain_component(test, 39, 3, 1) != NULL);
    //      igraph_vector_int_print(does_adding_ends_a_certain_component(test, 39, 3, 1));    
    
    //tests for the second
      tests[0] = 3;
    tests[1] = -1;
    tests[2] = -1;
    tests[3] = 1;
   igraph_vector_ptr_t *components = set_of_new_finished(test, CARC_TILE_XROAD, tests, 5);
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
      igraph_vector_ptr_t *components_2 = set_of_new_finished(test, CARC_TILE_XROAD, tests, 5);
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
    igraph_vector_ptr_t *   components_3 = set_of_new_finished(test, CARC_TILE_XROAD, tests, 6);

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
    assert(number_of_vertices_in_new_component(graph,CARC_TILE_XROAD,tests,3,1,1) == 4);   
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
    assert(meeple_can_be_added(graph, 98) == 0);
    assert(which_player_placed_the_meeple(graph, 98) == 0);                        
    assert(meeple_can_be_added(graph, 42));
    add_meeple(graph,42,1);
    add_meeple(graph,62,1);    
    assert(which_player_placed_the_meeple(graph, 42) == 1);                            
    tests[1] = 4;
    tests[2] = 5;
    tests[3] = -1;
    igraph_vector_int_t *result = get_biggest_road_component_of_adversary_in_a_position(graph,CARC_TILE_XROAD,tests,8,0);
    igraph_vector_int_print(result);
    tests[1] = -1;
    tests[2] = 2;
    tests[3] = 0;
    add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,8);
    tests[1] = -1;
    tests[2] = 8;
    tests[3] = 7;
    add_meeple(graph,95,1);
    result = get_biggest_road_component_of_adversary_in_a_position(graph,CARC_TILE_XROAD,tests,9,0);
    igraph_vector_int_print(result);
    add_meeple(graph,105,0);
    add_tile_to_graph(graph, CARC_TILE_XROAD,tests ,9);    
    assert(meeple_can_be_added(graph,124) == 0);
    assert(meeple_can_be_added(graph,104) == 0);
    assert(meeple_can_be_added(graph,106) == 0);
    assert(meeple_can_be_added(graph,120));
    assert(meeple_can_be_added(graph,119));
    assert(meeple_can_be_added(graph,126) == 0);                
    display_graph(graph,"test.dot");        
    igraph_destroy(graph);
    free(graph);
    
    
    }
int main() {    
//        test_graph_add();
//   test_components();  
  test_score();
    return 0;
}
