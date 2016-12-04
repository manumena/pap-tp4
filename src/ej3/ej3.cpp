#include "./ej3.h"

using namespace std;

/*
**  Exercise 3
**  Problem solver
*/

// --------------- Global Variables ----------------

int H, E;
vector<Point> historical_places, enemy_places;
vector< vector <vector<int> > > historical_places_in_triangle;
vector< vector <vector<int> > > enemy_places_in_triangle;
Point reference_sorting_point;

// --------------------- Code ----------------------

void run_solver() {
    // Data input (H, E)
    cin >> H >> E;

    // Global variable initialization
    historical_places = vector<Point>(H, Point(0,0));
    enemy_places = vector<Point>(E, Point(0,0));
    historical_places_in_triangle = vector< vector <vector<int> > >(H, vector< vector<int> >(H, vector<int>(H, 0)));
    enemy_places_in_triangle = vector< vector <vector<int> > >(H, vector< vector<int> >(H, vector<int>(H, 0)));
    
    // Data input (historical_places, enemy_places)
    for (int i = 0; i < H; ++i)
        cin >> historical_places[i].x >> historical_places[i].y;
    for (int i = 0; i < E; ++i)
        cin >> enemy_places[i].x >> enemy_places[i].y;

    // Calculate places in each triangle
    calculate_places_triangles();

    // Calculate max historical places in convex polygon for each leftmost inferior point
    int ans = min(2, H);
    for (int i = 0; i < H; ++i)
        ans = max(ans, calculate_max_historical_places(i));

    // Print answer
    cout << ans << endl;
}

void calculate_places_triangles() {
    // For each triangle calculate historical and enemy places
    // not counting triangle nodes
    for (int i = 0; i < H; ++i) {
        Point pi = historical_places[i];
        for (int j = 0; j < H; ++j) {
            if (i==j) continue;
            Point pj = historical_places[j];
            for (int k = 0; k < H; ++k) {
                if (i==k || j==k) continue;
                Point pk = historical_places[k];
                // Previously checked i,j,k are all different
                // Calculate historical places
                for (int l = 0; l < H; ++l) {
                    if (i==l || j==l || k==l) continue;
                    Point pl = historical_places[l];
                    if(Triangle(pi,pj,pk).contains(pl))
                        historical_places_in_triangle[i][j][k]++;
                }
                // Calculate enemy places
                for (int l = 0; l < E; ++l) {
                    Point pl = enemy_places[l];
                    if(Triangle(pi,pj,pk).contains(pl))
                        enemy_places_in_triangle[i][j][k]++;
                }
            }
        }
    }
}

int calculate_max_historical_places(int ref_point) {
    // Reference point, only consider other points upper and to the right of it
    Point p = historical_places[ref_point];

    // Only consider points upper and to the right of p
    vector<int> valid_historical_places = vector<int>();
    valid_historical_places.reserve(H);
    for (int i = 0; i < H; ++i)
        if (historical_places[i].y > p.y || (historical_places[i].y == p.y && historical_places[i].x > p.x))
            valid_historical_places.push_back(i);

    // Sort valid points by angle from p
    reference_sorting_point = p;
    sort(valid_historical_places.begin(), valid_historical_places.end(), compare_points_by_angle_with_reference);
    
    // Dynamic programming vector
    int V = valid_historical_places.size();
    vector< vector<int> > dp = vector< vector<int> >(V, vector<int>(V, 0));

    // For each i,j calculate max historical places if first triangle is <ref_point,i,j>
    // and triangles are added in clockwise order
    for (int i = 0; i < V; ++i) {
        int hi = valid_historical_places[i];
        for (int j = 0; j < i; ++j) {
            int hj = valid_historical_places[j];
            if (enemy_places_in_triangle[ref_point][hi][hj] > 0) continue;
            int h_places = 3 + historical_places_in_triangle[ref_point][hi][hj];
            dp[i][j] = h_places;
            for (int k = 0; k < j; ++k) {
                int hk = valid_historical_places[k];
                Point r = historical_places[hj];
                Point s = historical_places[hi];
                Point q = historical_places[hk];
                bool keeps_convex = has_closed_orientation(r, s, q);
                bool no_enemies = enemy_places_in_triangle[ref_point][hj][hk] == 0;
                if (keeps_convex && no_enemies)
                    dp[i][j] = max(dp[i][j], h_places + dp[j][k] - 2);
            }
        }
    }

    // Calculate answer
    int ans = 0;
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            ans = max(ans, dp[i][j]);

    return ans;
}

bool compare_points_by_angle_with_reference(int i, int j) {
    Point p = historical_places[i];
    Point q = historical_places[j];
    return has_closed_orientation(reference_sorting_point, p, q);
}

bool has_closed_orientation(Point r, Point p, Point q) {
    // Return true iff segments rp and rq create an angle
    // with closed orientation (if rp lower than rq)
    return (p-r).cross_product(q-r) > 0;
}

// --------------------- Main ----------------------

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
