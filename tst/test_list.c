#include "liste.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    // Initialize an empty linked list
    struct set *test_set = set__empty();
    assert(test_set != NULL);
    assert(set_size(test_set) == 0);

    // Create some data elements
    int t[]={-1,-1,-1,-1};
    int v[]={-1,-1,-1,-1};
    int u[]={-1,-1,-1,-1};
    struct case_t elem1_data = {0, 1,t};
    struct case_t elem2_data = {1, 0,v};
    struct case_t elem3_data = {0, 1,u};

    // Add an element to the set
    assert(set__add_head(test_set, &elem1_data,S,0) == 0);
    assert(set_size(test_set) == 1);
    set_print(test_set,"set:");

    // Add another element to the set
    assert(set__add_head(test_set, &elem2_data,W,0) == 0);
    assert(set_size(test_set) == 2);
    set_print(test_set,"set:");
    


    assert(set__add_head(test_set, &elem3_data,N,1) == 1);
    assert(set_size(test_set) == 2);
    set_print(test_set,"set:");
    struct lelement*elt=get_lelement_from_empty(test_set,1);
    print_case(elt->data);
    printf("\n");

    // Remove an element from the set
    assert(set__remove(test_set, test_set->l->head) == 0);
    assert(set_size(test_set) == 1);
    assert(test_set->l->head != NULL);
    assert(test_set->l->head->data == &elem1_data);
    assert(test_set->l->head->next == NULL);

    // Free the memory allocated for the set
    free_set(test_set);

    printf("All tests passed!\n");
    return 0;
}
