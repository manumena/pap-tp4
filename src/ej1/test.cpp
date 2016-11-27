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

// Tower of (MAX_INPUT_SIZE-2)/2 squares, each divided into two triangles
void load_test() {
    /******* Creat input *******/
    string test_file_path = CASE_DIR + "temp_load_case.dat";
	ofstream data(test_file_path);
    data << MAX_INPUT_SIZE << endl;

    vector<int> current_square = {0,0,1,0,1,1,0,0,0,1,1,1};

    size_t total_squares = (MAX_INPUT_SIZE-2)/2;

    // at the beginning of an iteration, current_square holds the points for
    // two triangles that form a square to be printed. The iteration prints
    // them and increments values of y.
    for (size_t i = 0; i < total_squares; ++i) {
        for (size_t j = 0; j < 6; ++j) {
            data << current_square[2*j] << " " << current_square[2*j+1] << " ";
            current_square[2*j+1]++;
            if (j == 2 || j == 5)
                data << endl;
        }
    }

    /******* Create expected result *******/
    // print left side of tower
    vector<point> expected;
    point p;
    for (int i = 0; i <= total_squares; ++i) {
        p = {0,i};
        expected.push_back(p);
    }

    // print right side of tower
    for (int i = total_squares; i >= 0; --i) {
        p = {1,i};
        expected.push_back(p);
    }

    /******* Solve and test *******/
    ifstream input_load_case(test_file_path);

    multiset<edge> es = read_triangulation_graph(MAX_INPUT_SIZE, input_load_case);
    adj_map cn = get_border_subgraph(es);
    vector<point> obtained = sequence_border_vertices_clockwise(cn);

    remove(test_file_path.c_str());

    // cout << endl;
    // print_border_vertex_sequence(obtained, cout);
    // print_border_vertex_sequence(expected, cout);

    ASSERT(obtained == expected);
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
