#include "test_board.h"
#include "test_graph.h"
#include "test_list.h"
#include "test_player_functions.h"
#include "test_tile.h"


int main(){
    test_board();
    second_test_board();
    test_graph_add();
    test_components();
    test_score();
    list_test();
    test_player();
    test_tile();
    return 0;

}