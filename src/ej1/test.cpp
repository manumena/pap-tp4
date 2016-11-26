#include "./ej1.h"
#include "../mini_test.h"

/*
**  Exercise 1
**  Unit tests
*/

string CASE_DIR = "cases/";

vector<test_case_input> cases_filenames = {
    {CASE_DIR + "ejemplo1.dat", CASE_DIR + "ejemplo1.exp"},
    {CASE_DIR + "ejemplo2.dat", CASE_DIR + "ejemplo2.exp"},
    {CASE_DIR + "ejemplo3.dat", CASE_DIR + "ejemplo3.exp"},
};

vector<point> read_expected(size_t n, istream& f) {
	point p;
    vector<point> result;
    for (size_t i = 0; i < n; ++i) {
        f >> p.x >> p.y;
        result.push_back(p);
    }

    return result;
}

void load_test() {
	cout << " (falta implementar) ";
	ASSERT(1 == 2);
}

void run_unit_tests() {
	for (test_case_input& c : cases_filenames) {
        auto file_case = [&c] () {
            ifstream input_file(c.input_filename);
            ifstream expected_file(c.expected_filename);

            size_t n;
            input_file >> n;
            multiset<edge> es = read_triangulation_graph(n, input_file);

            adj_map cn = get_border_subgraph(es);

            vector<point> obtained = sequence_border_vertices_clockwise(cn);

            ASSERT(obtained == read_expected(n, expected_file));
        };
        RUN_TEST(file_case);
    }

    RUN_TEST(load_test);
}
