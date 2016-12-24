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

void test_get_permutations_between_cycles_single_elements() {
    vector<int> cycle_sizes = {1, 1, 1, 1};
    ASSERT_EQ(get_permutations_between_cycles(cycle_sizes, 0, 4), 16);

    cycle_sizes = {1, 1, 1};
    ASSERT_EQ(get_permutations_between_cycles(cycle_sizes, 0, 3), 4);
}

void test_get_permutations_between_cycles_mixed_sizes() {
    vector<int> cycle_sizes = {3, 1, 1, 1};
    ASSERT_EQ(get_permutations_between_cycles(cycle_sizes, 0, 4), 16);

    cycle_sizes = {3, 3, 5, 7};
    ASSERT_EQ(get_permutations_between_cycles(cycle_sizes, 0, 4), 16);
}

void test_sample_inputs() {
    vector<int> permutation = {2, 4, 3, 1};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 4);

    permutation = {2, 3, 1};
    cycle_sizes = get_cycle_sizes(permutation);

    tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 2);
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

void test_get_posible_tournaments_count_two_cycles() {
    vector<int> permutation = {3, 1, 2, 5, 6, 4};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 32);
}

void test_get_posible_tournaments_count_three_cycles() {
    vector<int> permutation = {3, 1, 2, 5, 6, 4, 7};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 128);
}

void test_get_posible_tournaments_count_four_single_element_cycles() {
    vector<int> permutation = {1, 2, 3, 4};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 64);
}

void test_get_posible_tournaments_count_even_cycles() {
    vector<int> permutation = {2, 1};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 0);

    permutation = {5, 1, 2, 3, 4, 7, 6};
    cycle_sizes = get_cycle_sizes(permutation);
    ASSERT_EQ(tournament_count, 0);

    permutation = {5, 1, 2, 3, 4, 7, 6, 8, 9};
    cycle_sizes = get_cycle_sizes(permutation);
    ASSERT_EQ(tournament_count, 0);
}

void test_get_posible_tournaments_big_count_values() {
    vector<int> permutation = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 268435456);

    permutation = {1, 2, 3, 4, 5, 6, 7, 10, 8, 9};
    cycle_sizes = get_cycle_sizes(permutation);
    tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 536870912);

    permutation = {1, 2, 3, 4, 5, 6, 7, 8, 11, 9, 10};
    cycle_sizes = get_cycle_sizes(permutation); tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 438952513);
}

void test_get_posible_tournaments_big_input() {
    vector<int> permutation;
    for (int i = 1; i < 100001; i++) {
        permutation.push_back(i);
    }
    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 298208567);
}

void test_get_posible_tournaments_cycles_nine_fifteen() {
    vector<int> permutation = {2, 3, 4, 5, 6, 7, 8, 9, 1,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 10};
    vector<int> cycle_sizes = get_cycle_sizes(permutation);
    int tournament_count = get_posible_tournaments_count(cycle_sizes);
    ASSERT_EQ(tournament_count, 16384);
}

void run_unit_tests() {
    RUN_TEST(test_get_single_element_cycle);
    RUN_TEST(test_get_single_cycle_size_five);
    RUN_TEST(test_get_two_cycles);
    RUN_TEST(test_pow_mod_small_values);
    RUN_TEST(test_pow_mod_big_values);
    RUN_TEST(test_get_permutations_between_cycles_single_elements);
    RUN_TEST(test_get_permutations_between_cycles_mixed_sizes);
    RUN_TEST(test_sample_inputs);
    RUN_TEST(test_get_posible_tournaments_count_single_element);
    RUN_TEST(test_get_posible_tournaments_count_single_cycle_size_three);
    RUN_TEST(test_get_posible_tournaments_count_two_cycles);
    RUN_TEST(test_get_posible_tournaments_count_three_cycles);
    RUN_TEST(test_get_posible_tournaments_count_four_single_element_cycles);
    RUN_TEST(test_get_posible_tournaments_count_even_cycles);
    RUN_TEST(test_get_posible_tournaments_big_count_values);
    RUN_TEST(test_get_posible_tournaments_big_input);
    RUN_TEST(test_get_posible_tournaments_cycles_nine_fifteen);
}
