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
    struct case_t elem1_data = {1, 1, -1, 0};
    struct case_t elem2_data = {2, 2, -1, 0};

    // Add an element to the set
    assert(set__add_head(test_set, &elem1_data) == 0);
    assert(set_size(test_set) == 1);
    assert(test_set->l->head != NULL);
    assert(test_set->l->head->data == &elem1_data);

    // Add another element to the set
    assert(set__add_head(test_set, &elem2_data) == 0);
    assert(set_size(test_set) == 2);
    assert(test_set->l->head != NULL);
    assert(test_set->l->head->data == &elem2_data);

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
