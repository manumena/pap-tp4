#ifndef PAP_TP4_EJ4_H
#define PAP_TP4_EJ4_H

#include "../main.h"

/*
**  Exercise 4
*/

#define BIG_PRIME 1000000007

// Here go declarations of functions which are exported by the problem solver,
// global variables, etc.

int pow_mod(const int b, const int e);

std::vector<int> get_cycle_sizes(std::vector<int>& permutation);
int get_posible_tournaments_count(const std::vector<int>& cycle_sizes);

#endif // PAP_TP4_EJ4_H
