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

    int ccw(const Point &p1, const Point &p2) const {
        int cross_product = (p1.x - x) * (p2.y - y) - (p2.x - x) * (p1.y - y);

        if (cross_product > 0) return 1;
        if (cross_product < 0) return -1;
        return 0;
    }
};

int main() {
    Point p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;

    cout << (p1.ccw(p2, p3) * p1.ccw(p2, p4) < 0 and p3.ccw(p4, p1) * p3.ccw(p4, p2) < 0);
}