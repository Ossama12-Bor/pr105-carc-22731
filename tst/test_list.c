#include "liste.h"
#include <stdio.h>
#include <assert.h>


int main(){
  struct link test_link = lnk__empty();
  assert(test_link.head == NULL);
  assert(test_link.size ==0);
  struct lelement *elem1 = malloc(sizeof(struct lelement));
  assert(elem1 != NULL);
  struct case_t elem1_data = {1,1,-1,0};
  elem1->data = &elem1_data;  
  elem1->next = NULL;
  elem1->prev = NULL;
  lnk__add_head(&test_link, elem1);
  assert(test_link.size == 1);  
  assert(test_link.head == elem1);
  struct lelement *elem2 = malloc(sizeof(struct lelement));
  assert(elem2 != NULL);
  struct case_t elem2_data = {2,2,-1,0};
  elem2->data = &elem2_data;  
  elem2->next = NULL;
  elem2->prev = NULL;
  lnk__add_head(&test_link, elem2);
  assert(test_link.size == 2);  
  assert(test_link.head == elem2);
  assert(test_link.head->next == elem1);
  lnk_remove(&test_link,elem1);
  assert(test_link.size == 1);  
  assert(test_link.head == elem2);    
  assert(test_link.head->next == NULL);
  free_list(&test_link);
  printf("All tests passed!\n");
  return 0;  
}
