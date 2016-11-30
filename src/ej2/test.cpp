#include "./ej2.h"
#include "../mini_test.h"

using namespace std;

/*
**  Exercise 2
**  Unit tests
*/

void test_example_1() {
	int arr[] = {1};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	ASSERT(1.0 == expectedValue(vec));
}

void test_example_2() {
	int arr[] = {1, 2};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	ASSERT(2.0 == expectedValue(vec));
}

void test_example_3() {
	int arr[] = {2, 3, 1};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	ASSERT(4.0 == expectedValue(vec));
}

void test_example_4() {
	int arr[] = {15, 16, 4, 8, 42, 23};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	ASSERT(16.0 == expectedValue(vec));
}

void test_example_5() {
	int arr[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	ASSERT(1.0 == expectedValue(vec));
}

void test_example_6() {
	int arr[] = {1, 2, 2, 2, 2, 3};
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	// cout << setprecision(7) << expectedValue(vec) << endl;
	ASSERT(8.083333 <= expectedValue(vec));
	ASSERT(8.083334 > expectedValue(vec));

}

void run_unit_tests() {
	RUN_TEST(test_example_1);
	RUN_TEST(test_example_2);
	RUN_TEST(test_example_3);
	RUN_TEST(test_example_4);
	RUN_TEST(test_example_5);
	RUN_TEST(test_example_6);
}
