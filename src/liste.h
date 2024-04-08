#ifndef __LISTE_H__
#define __LISTE_H__

#include "board.h"
struct set;

struct case_t *get_case_array(struct set *se);

// Return a struct set representing the empty set
struct set * set__empty();

int set_size(const struct set*se);

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se);

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, struct case_t box);

// Returns the number of elements in se
int set__size(const struct set *se);

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
void set__add(struct set *se,struct case_t box);

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
void set__remove(struct set *se, int n);

// Frees the dynamically allocated contents of the set se
// Does *not* free the pointer se
void set__free(struct set* se);

//helper function for debugging : display all elements in se
//void set__print(const struct set * se, void (*print)(void *));
void set__print(struct set*se);

#endif
