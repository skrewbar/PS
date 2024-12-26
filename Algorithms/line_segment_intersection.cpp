#include <bits/stdc++.h>
using namespace std;


class Point {
public:
    int x, y;
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator<=(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y <= p.y;
    }

    int ccw(const Point &p1, const Point &p2) const {
        int cross_product = (p1.x - x) * (p2.y - y) - (p2.x - x) * (p1.y - y);
        if (cross_product > 0) return 1;
        if (cross_product < 0) return -1;
        return 0;
    }
};

class Line {
public:
    Point start, end;
    Line() = default;
    Line(Point _start, Point _end) : start(_start), end(_end) {
        if (end < start) swap(start, end);
    }

    int ccw(const Point &p) const {
        return start.ccw(end, p);
    }

    bool is_intersect(const Line &l) {
        int product1 = ccw(l.start) * ccw(l.end);
        int product2 = l.ccw(start) * l.ccw(end);

        if (product1 == 0 and product2 == 0) return start <= l.end and l.start <= end;
        return product1 <= 0 and product2 <= 0;
    }
};