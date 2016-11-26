#ifndef PAP_TP4_EJ1_H
#define PAP_TP4_EJ1_H

#include "../main.h"
#include <algorithm>
#include <set>
#include <map>

using namespace std;

/*
**  Exercise 1
*/

// Here go declarations of functions which are exported by the problem solver,
// global variables, etc.

/******* Point stuff ********/
struct point {
	int x, y;
};

bool operator==(const point&, const point&);

/* p1 is considered "less than" p2 if p1 is to the left of v, and in case of being vertically aligned, beneath it. */
bool operator<(const point&, const point&);

ostream& operator<<(ostream&, const point&);
/*--------------------------*/

/******* Edge stuff ********/
/*
	(a) An edge connects two points, u and v, and is oriented such that u < v (construction invariant).
	- An edge u1->v1 is "less than" another u2->v2 if bla
	- Conceptually, an edge u1->v1 equals both u1->v1 and v1->u1. Here default struct equality is sufficient since edge construction is restricted by the construction invariant (a).
*/
struct edge {
	point u, v;
	edge(const point& p1, const point& p2) {
		u = min(p1, p2);
		v = max(p1, p2);
	}
};

// static bool operator==(const edge& e1, const edge& e2) {
// 	return e1.u == e2.u && e1.v == e2.v;
// }

bool operator<(const edge&, const edge&);

// static ostream& operator<<(ostream& o, const edge& e) {
// 	o << e.u << "-->" << e.v;
// 	return o;
// }
/*--------------------------*/

/******* Graph stuff ********/
typedef map<point, vector<point>> adj_map;

// ostream& operator<<(ostream& o, const adj_map& g) {
// 	for (auto it = g.cbegin(); it != g.cend(); ++it) {
// 		o << it->first << " --> ";
// 		o << (it->second)[0] << ", " << (it->second)[1];
// 		o << endl;
// 	}
// 	return o;
// }
/*--------------------------*/

/******* Solver stuff ********/
void print_border_vertex_sequence(const vector<point>& vs, ostream& o);

// build a multiset containing all edges in input polygon triangulation
// edges of count 1 in the resulting multiset conform polygon's border
// ordering for multiset construction is defined by "<" for edges and points
multiset<edge> read_triangulation_graph(size_t n, istream& in);

// build an adjacency map representing the subgraph that is the polygon border
// this subgraph is a Cn (simple circuit of size n)
adj_map get_border_subgraph(const multiset<edge>& es);

vector<point> sequence_border_vertices_clockwise(adj_map& cn);
/*--------------------------*/

/******* Multiset stuff ********/
template <class T>
ostream& operator<<(ostream& o, const multiset<T>& m) {
	for (auto it = m.cbegin(); it != m.cend(); ++it)
		o << "key " << *it << ", count " << m.count(*it) << endl;
	return o;
}
/*--------------------------*/

/******* Test stuff ********/
struct test_case_input {
    string input_filename;
    string expected_filename;
};
/*--------------------------*/

#endif // PAP_TP4_EJ1_H
