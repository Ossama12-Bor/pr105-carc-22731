#include "liste.h"
#include <stdio.h>

int main(){

    struct set *empty = set__empty();
    set__print(empty);
    struct case_t box1={1,1,1,1};
    struct case_t box2={1,2,1,3};
    struct case_t box3={2,2,2,3};
    struct case_t box4={3,3,3,3};
    struct case_t box5={5,2,5,5};
    set__add(empty,box1);
    set__add(empty,box2);
    set__add(empty,box3);
    set__add(empty,box4);
    set__add(empty,box5);
    set__print(empty);
    set__remove(empty,2);
    set__remove(empty,0);
    set__remove(empty,1);
    set__remove(empty,1);
    set__print(empty);
    set__remove(empty,0);
    set__print(empty);
    set__add(empty,box5);
    set__print(empty);
    set__free(empty);

    return 0;

}