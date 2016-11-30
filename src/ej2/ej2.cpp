#include "./ej2.h"
#include <math.h>

using namespace std;

/*
**  Exercise 2
**  Problem solver
*/

int minCount(vector<int> vec) {
	int min = vec[0];
	int count = 1;
	for(int i = 1; i < vec.size(); i++) {
		if(vec[i] < min) {
			min = vec[i];
			count = 1;
		}
		else if(vec[i] == min)
			count++;
	}
	return count;
}

double expectedValue(vector<int> vec) {
	double mean = 0.0;
	mean = (double) vec.size() / (double) minCount(vec);
	for(int i = 1; i < vec.size(); i++) {
		vector<int> subVec(vec.begin() + i, vec.end());
		mean = mean + (double) subVec.size() / (double) minCount(subVec) - 1.0;
	}

	return mean;
}

void run_solver() {
	int n;
	cin >> n;

	vector<int> vec;
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		vec.push_back(num);
	}

	cout << setprecision(7) << expectedValue(vec) << endl;
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
