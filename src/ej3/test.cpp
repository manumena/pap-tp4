#include "./ej3.h"
#include "../mini_test.h"

/*
**  Exercise 3
**  Unit tests
*/

void check(int a, int b) {
    cout << (a == b ? "OK" : "ERROR") << endl;
}

void run_unit_tests() {
	cout << "----------Segment Tests1----------" << endl;
    Point a = Point(0,0);
    Point b = Point(4,0);
    Point c = Point(2,2);
    Point d = Point(1,1);
    Point e = Point(3,3);
    Segment s1 = Segment(a,c);
    check(s1.contains(d), true);
    check(s1.contains(a), true);
    check(s1.contains(c), true);
    check(s1.contains(b), false);
    check(s1.contains(e), false);

    cout << "----------Segment Tests2----------" << endl;
    Segment s2 = Segment(a, b);
    Segment s3 = Segment(b, a);
    Segment s4 = Segment(b, e);
    Segment s5 = Segment(Point(-1,0),Point(2,1));
    Segment s6 = Segment(Point(4,0),Point(0,0));
    Segment s7 = Segment(Point(0,0),Point(2,2));
    Segment s8 = Segment(Point(-1,0),Point(4,2));
    Segment s9 = Segment(Point(-1,0),Point(4,1));
    check(s1.intersects(s2), true);
    check(s1.intersects(s3), true);
    check(s1.intersects(s4), false);
    check(s7.intersects(s5), true);
    check(s8.intersects(s6), false);
    check(Segment(a,b).intersects(s9), false);
    check(Segment(b,c).intersects(s9), true);
    check(Segment(c,a).intersects(s9), true);

    cout << "----------Triangle Tests----------" << endl;
    Triangle t = Triangle(a,b,c);
    Triangle t2 = Triangle(Point(0,0),Point(2,-1),Point(2,1));
    Triangle t3 = Triangle(Point(0,0),Point(0,10), Point(10,10));
    Triangle t4 = Triangle(Point(0,0),Point(4,0),Point(4,4));
    check(t.contains(Point(2,0)), true);
    check(t.contains(Point(2,1)), true);
    check(t.contains(Point(2,2)), true);
    check(t.contains(Point(1,1)), true);
    check(t.contains(Point(4,1)), false);
    check(t2.contains(Point(1,0)), true);
    check(t3.contains(Point(10,0)), false);
    check(t4.contains(Point(7,0)), false);
}
