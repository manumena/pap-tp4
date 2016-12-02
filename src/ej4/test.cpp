#include "./ej4.h"
#include "../mini_test.h"

using namespace std;

/*
**  Exercise 4
**  Unit tests
*/

void test_get_single_element_cycle() {
    vector<int> permutation = {1, 2, 3, 4, 5};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);
    ASSERT_EQ(cycle_sizes.size(), 5);
    ASSERT_EQ(cycle_sizes[0], 1);
    ASSERT_EQ(cycle_sizes[1], 1);
    ASSERT_EQ(cycle_sizes[2], 1);
    ASSERT_EQ(cycle_sizes[3], 1);
    ASSERT_EQ(cycle_sizes[4], 1);
}

void test_get_single_cycle_size_five() {
    vector<int> permutation = {5, 1, 2, 3, 4};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);
    ASSERT_EQ(cycle_sizes.size(), 1);
    ASSERT_EQ(cycle_sizes[0], 5);

    permutation = {2, 3, 1};
    cycle_sizes = get_cycle_sizes(permutation);
    ASSERT_EQ(cycle_sizes.size(), 1);
    ASSERT_EQ(cycle_sizes[0], 3);
}

void test_get_two_cycles() {
    vector<int> permutation = {3, 1, 2, 4};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);
    ASSERT_EQ(cycle_sizes.size(), 2);
    ASSERT_EQ(cycle_sizes[0], 3);
    ASSERT_EQ(cycle_sizes[1], 1);

    permutation = {2, 3, 1, 6, 4, 5};
    cycle_sizes = get_cycle_sizes(permutation);
    ASSERT_EQ(cycle_sizes.size(), 2);
    ASSERT_EQ(cycle_sizes[0], 3);
    ASSERT_EQ(cycle_sizes[1], 3);
}

void test_pow_mod_small_values() {
    ASSERT_EQ(pow_mod(2, 0), 1);
    ASSERT_EQ(pow_mod(2, 1), 2);
    ASSERT_EQ(pow_mod(2, 3), 8);
    ASSERT_EQ(pow_mod(2, 10), 1024);
}

void test_pow_mod_big_values() {
    ASSERT_EQ(pow_mod(BIG_PRIME, 2), 0);
    ASSERT_EQ(pow_mod(BIG_PRIME - 1, 2), 1);
    ASSERT_EQ(pow_mod(BIG_PRIME - 5, 2), 25);
}

void test_get_posible_tournaments_count_single_element() {
    vector<int> permutation = {1};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 1);
}

void test_get_posible_tournaments_count_single_cycle_size_three() {
    vector<int> permutation = {3, 1, 2};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 2);
}

void run_unit_tests() {
    RUN_TEST(test_get_single_element_cycle);
    RUN_TEST(test_get_single_cycle_size_five);
    RUN_TEST(test_get_two_cycles);
    RUN_TEST(test_pow_mod_small_values);
    RUN_TEST(test_pow_mod_big_values);
    RUN_TEST(test_get_posible_tournaments_count_single_element);
    RUN_TEST(test_get_posible_tournaments_count_single_cycle_size_three);
}
