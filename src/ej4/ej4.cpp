#include "./ej4.h"

using namespace std;

/*
**  Exercise 4
**  Problem solver
*/

int min(int a, int b) {
    return a < b ? a : b;
}

int pow_mod(const int b, const int e) {
    long long ret = 1;
    if (e > 0) {
        long long root = pow_mod(b, e / 2);
        ret = (root * root) % BIG_PRIME;
        if (e % 2 == 1) {
            ret = (ret * b) % BIG_PRIME;
        }
    }
    return ret;
}

vector<int> get_cycle_sizes(vector<int>& permutation) {
    vector<int> cycle_sizes;
    int n = (int) permutation.size();

    int cycle_size;
    int next_index;
    int current_index;
    for (int i = 0; i < n; i++) {
        if (permutation[i] != 0) {
            cycle_size = 1;
            current_index = i;
            next_index = permutation[current_index] - 1;
            permutation[current_index] = 0;
            // as long as we haven't gone back to the beginning
            while (next_index != i) {
                current_index = next_index;
                next_index = permutation[current_index] - 1;
                permutation[current_index] = 0;
                cycle_size++;
            }
            cycle_sizes.push_back(cycle_size);
        }
    }

    return cycle_sizes;
}

int get_permutations_between_cycles(
        const vector<int>& cycle_sizes, const int i, const int j) {
    long long total_permutations = 1;
    map<int, int> left_half_cycles;
    map<int, int> right_half_cycles;

    for (int l = i; l < (i + j) / 2; l++) {
        if (left_half_cycles.find(cycle_sizes[l]) != left_half_cycles.end()) {
            left_half_cycles[cycle_sizes[l]]++;
        } else {
            left_half_cycles[cycle_sizes[l]] = 1;
        }
    }

    for (int r = (i + j) / 2; r < j; r++) {
        if (right_half_cycles.find(cycle_sizes[r]) != right_half_cycles.end()) {
            right_half_cycles[cycle_sizes[r]]++;
        } else {
            right_half_cycles[cycle_sizes[r]] = 1;
        }
    }

    map<int, int>::iterator left_half_cycles_iterator;
    map<int, int>::iterator right_half_cycles_iterator;
    int min_cycle_size;
    long long cycle_permutations;
    for (left_half_cycles_iterator = left_half_cycles.begin();
        left_half_cycles_iterator != left_half_cycles.end();
        left_half_cycles_iterator++) {

        for (right_half_cycles_iterator = right_half_cycles.begin();
            right_half_cycles_iterator != right_half_cycles.end();
            right_half_cycles_iterator++) {

            min_cycle_size = min(left_half_cycles_iterator->first,
                    right_half_cycles_iterator->first);

            cycle_permutations =
                pow_mod(
                    pow_mod(
                        pow_mod(2, min_cycle_size),
                        right_half_cycles_iterator->second
                    ),
                    left_half_cycles_iterator->second
                );

            total_permutations =
                (total_permutations * cycle_permutations) % BIG_PRIME;
        }
    }

    return total_permutations;
}

int get_partial_posible_tournaments_count(
         const vector<int>& cycle_sizes, const int i, const int j) {
    if (j - i == 0) {
        return 1;
    } else if (j - i == 1) {
        return (cycle_sizes[i] % 2 == 0) ? 0 : pow_mod(2, (cycle_sizes[i] - 1) / 2);
    } else {
        long long left_half_count =
            get_partial_posible_tournaments_count(cycle_sizes, i, (i + j) / 2);
        long long right_half_count =
            get_partial_posible_tournaments_count(cycle_sizes, (i + j) / 2, j);

        long long tournament_count =
            (left_half_count * right_half_count) % BIG_PRIME;

        tournament_count =
            (tournament_count *
            get_permutations_between_cycles(cycle_sizes, i, j)) % BIG_PRIME;

        return tournament_count;
    }
}

int get_posible_tournaments_count(const std::vector<int>& cycle_sizes) {
    return get_partial_posible_tournaments_count(cycle_sizes, 0, cycle_sizes.size());
}

void run_solver() {
    int n;
    cin >> n;

    vector<int> permutation(n);
    for (int i = 0; i < n; i++) {
        cin >> permutation[i];
    }

    vector<int> cycle_sizes = get_cycle_sizes(permutation);

    cout << get_posible_tournaments_count(cycle_sizes) << endl;
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
