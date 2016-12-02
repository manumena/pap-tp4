#ifndef PAP_TP4_EJ3_H
#define PAP_TP4_EJ3_H

#include "../main.h"
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

/*
**  Exercise 3
*/

// --------------- Classes ----------------

#define epsilon 1e-8
#define finfinity numeric_limits<float>::infinity()

class Point {
public:
	double x, y;
	Point() {}
	Point(double i, double j) : x(i), y(j) {}
	~Point() {}
	inline Point operator+(Point p) { return Point(x+p.x,y+p.y); }
    inline Point operator-(Point p) { return Point(x-p.x,y-p.y); }
    double cross_product(Point p) { return x*p.y-p.x*y; }
    inline bool operator==(Point p) { return x == p.x && y == p.y; }
    inline bool operator!=(Point p) { return x != p.x || y != p.y; }
};

class Segment {
public:
	Point a, b;
	Segment() {}
	Segment(Point i, Point j) : a(i), b(j) {}
	~Segment() {}
	bool contains(Point p) {
		return fabs((b-p).cross_product(p-a)) < epsilon && 
			min(a.x,b.x) - epsilon <= p.x && p.x <= max(a.x, b.x) + epsilon &&
			min(a.y,b.y) - epsilon <= p.y && p.y <= max(a.y, b.y) + epsilon;
	}
	bool intersects(Segment s) {
		Point intersection = this->intersection(s);
		return intersection.x != finfinity && intersection.y != finfinity;
	}
	Point intersection(Segment s) {
		Point v1 = b - a;
		Point v2 = s.b - s.a;
		bool parallel = v1.cross_product(v2) == 0;
		Point ans = Point(finfinity, finfinity);
		if (!parallel) {
			double alpha = (s.a-a).cross_product(v2) / v1.cross_product(v2);
			Point intersection = a + Point(alpha*v1.x,alpha*v1.y);
			if (this->contains(intersection) && s.contains(intersection))
				ans = intersection;
		} else {
			if (this->contains(s.a)) ans = s.a;
			if (this->contains(s.b)) ans = s.b;
			if (s.contains(a)) ans = a;
			if (s.contains(b)) ans = b;
		}
		return ans;
	}
};

class Triangle {
public:
	Point a, b, c;
	Triangle() {}
	Triangle(Point i, Point j, Point k) : a(i), b(j), c(k) {}
	~Triangle() {}
	bool contains(Point p){
		double leftmost_x = min(a.x, min(b.x, c.x));
		Segment ray = Segment(Point(leftmost_x-1,p.y),p);
		int intersections = 0;
		Segment ab = Segment(a, b);
		Segment bc = Segment(b, c);
		Segment ca = Segment(c, a);
		if (ray.intersects(ab)) intersections++;
		if (ray.intersects(bc)) intersections++;
		if (ray.intersects(ca)) intersections++;
		if (ray.contains(a)){
			if (b.y < p.y) intersections--;
			if (c.y < p.y) intersections--;
		}
		if (ray.contains(b)){
			if (a.y < p.y) intersections--;
			if (c.y < p.y) intersections--;
		}
		if (ray.contains(c)){
			if (a.y < p.y) intersections--;
			if (b.y < p.y) intersections--;
		}
		if ((ray.contains(a) && ray.contains(b)) || (ray.contains(a) && ray.contains(c)) || (ray.contains(c) && ray.contains(b))) {
			intersections = 0;
		}
		return intersections == 1 || ab.contains(p) || bc.contains(p) || ca.contains(p);
	}
};

// --------------- Functions --------------

void calculate_places_triangles();
int calculate_max_historical_places(int leftmost_inferior_point_index);
bool compare_points_by_angle_with_reference(int i, int j);
bool has_closed_orientation(Point r, Point p, Point q);

#endif // PAP_TP4_EJ3_H
