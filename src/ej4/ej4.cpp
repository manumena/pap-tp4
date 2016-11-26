#include "./ej4.h"

using namespace std;

/*
**  Exercise 4
**  Problem solver
*/

vector<point> sequence_border_vertices_clockwise(adj_map& cn) {
    map<point, bool> visited;
    vector<point> result;
    result.reserve(cn.size());

    // initialize visited with every node having value false
    for (auto it = cn.cbegin(); it != cn.cend(); ++it) {
        visited[it->first] = false;
    }

    // identify and sequence starting node "start"
    const point& start = cn.cbegin()->first;

    result.push_back(start);
    visited[start] = true;

    // choose following node, one of two neighbors of "start", in clocwkise fashion
    // since "start" is the "minimum" point in the graph by the "<" ordering for edges and points, it is guaranteed to be a leftmost point. Thus, both its neighbors in the border graph are either to its right or vertically aligned with it. Therefore, the following node in clockwise ordering is the uppermost of both neighbors.
    point following_node_clockwise = cn[start][0].y > cn[start][1].y ? cn[start][0] : cn[start][1];

    // walk the circuit in the direction determined by start --> following_node_clockwise
    point current = following_node_clockwise;
    for (size_t i = 0; i < cn.size()-1; ++i) {
        result.push_back(current);
        visited[current] = true;
        if (!visited[cn[current][0]]) {
            current = cn[current][0];
        } else {
            current = cn[current][1];
        }
    }

    return result;
}

adj_map get_border_subgraph(const multiset<edge>& es) {
    adj_map result;
    for (auto it = es.cbegin(); it != es.cend(); ++it) {
        if (es.count(*it) == 1) {
            result[it->u].push_back(it->v);
            result[it->v].push_back(it->u);
        }
    }
    return result;
}

multiset<edge> read_triangulation_graph(size_t n, istream& in) {
    multiset<edge> result;

    point p1, p2, p3;
    for (size_t i = 0; i < n-2; ++i) {
        in >> p1.x >> p1.y;
        in >> p2.x >> p2.y;
        in >> p3.x >> p3.y;

        edge new_edges[] = {edge(p1,p2), edge(p1,p3), edge(p2,p3)};
        
        result.insert(new_edges, new_edges + 3);
    }

    return result;
}

void print_border_vertex_sequence(const vector<point>& vs, ostream& o) {
    for_each(vs.cbegin(), vs.cend(), [&o] (const point& p) {o << p << " ";});
    o << endl;
}

void run_solver() {
    size_t n;
    cin >> n;

    multiset<edge> es = read_triangulation_graph(n, cin);
    // cout << es << endl;
    adj_map cn = get_border_subgraph(es);

    // Sequence border nodes in clockwise order starting with "lowest" point.
    // Lowest point is determined by the "<" ordering defined for edges and points.
    // Since this ordering is the same used to build the multiset "es", this point is field "u" of "es's" minimum edge, which is lower than v by construction invariant (a)
    vector<point> border_vertices = sequence_border_vertices_clockwise(cn);

    // Print border nodes sequence
    print_border_vertex_sequence(border_vertices, cout);
}

bool operator==(const point& p1, const point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

/* p1 is considered "less than" p2 if p1 is to the left of v, and in case of being vertically aligned, beneath it. */
bool operator<(const point& p1, const point& p2) {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

ostream& operator<<(ostream& o, const point& p) {
    o << p.x << " " << p.y;
    return o;
}

bool operator<(const edge& e1, const edge& e2) {
    return e1.u < e2.u || (e1.u == e2.u && e1.v < e2.v);
}

// MAIN

enum mode {solver, test};

int main (int argc, char* argv[]) {
    // Configuración de la ejecución
    mode exec_mode = solver;

    // Parsea las opciones recibidas
    char opt;
    while ((opt = getopt(argc, argv, "ht")) != -1) {
        switch (opt) {
            case 'h': { // mostrar ayuda
                show_help(argv[0]);
                exit(0);
                break;
            }
            case 't': { // correr tests unitarios
                exec_mode = test;
                break;
            }
            default: { // si las opciones son inválidas
                show_help(argv[0]);
                exit(1);
                break;
            }
        }
    }

    if (exec_mode == solver) {
        run_solver();
    }
    else if (exec_mode == test) {
        run_unit_tests();
    }
}

// Imprime por pantalla un texto de ayuda
void show_help(char* bin_path) {
    cout << "  Modo de uso: " << setw(12) << bin_path << endl;
    cout << endl;
    cout << "  Los parámetros se reciben a través de la entrada estándar." << endl;
    cout << endl;
    cout << "  Opciones:" << endl;
    cout << "    -h          Muestra este texto de ayuda" << endl;
    cout << "    -t          Ejecuta los tests unitarios provistos para el algoritmo" << endl;
}
