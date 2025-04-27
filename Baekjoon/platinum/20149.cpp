#include <bits/stdc++.h>
#include <cmath>
using namespace std;

using ll = long long;

template <typename T>
class Point {
public:
    T x, y;
    Point() = default;
    Point(T x, T y): x(x), y(y) {}

    template<typename U>
    Point(const Point<U> &p): x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {}

    bool operator<=(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y <= p.y;
    }
    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator==(const Point &p) const {
        return x == p.x and y == p.y;
    }

    int ccw(const Point &p2, const Point &p3) const {
        const Point &p1 = *this;
        T product = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
        if (product < 0) return -1;
        else if (product > 0) return 1;
        else return 0;
    }
};

template<typename T>
class Line {
public:
    Point<T> s, e;
    double grad, yIntercept;
    Line() = default;
    Line(Point<T> start, Point<T> end): s(start), e(end) {
        if (e <= s) swap(s, e);
        grad = static_cast<double>(e.y - s.y) / (e.x - s.x);
        yIntercept = s.y - grad * s.x;
    }

    int ccw(const Point<T> &p) const {
        return s.ccw(e, p);
    }

    bool isIntersect(const Line &l2) const {
        const Line &l1 = *this;
        int ccw1 = l1.ccw(l2.s) * l1.ccw(l2.e);
        int ccw2 = l2.ccw(l1.s) * l2.ccw(l1.e);

        if (ccw1 == 0 and ccw2 == 0) {
            return l1.s <= l2.e and l2.s <= l1.e;
        }
        return ccw1 <= 0 and ccw2 <= 0;
    }

    Point<double> getIntersection(const Line &l2) const {
        const Line &l1 = *this;
        int ccw1 = l1.ccw(l2.s) * l1.ccw(l2.e);
        int ccw2 = l2.ccw(l1.s) * l2.ccw(l1.e);

        if (ccw1 == 0 and ccw2 == 0) {
            if (l1.s <= l2.e and l2.s <= l1.e) {
                if (l1.s == l2.e) return l1.s;
                if (l2.s == l1.e) return l2.s;
            }
            if (l1.grad == l2.grad) return Point(1.0 / 0, 1.0 / 0);
        }
        
        if (l1.s.x == l1.e.x) return Point<double>(l1.s.x, l2.getValue(l1.s.x));
        else if (l2.s.x == l2.e.x) return Point<double>(l2.s.x, l1.getValue(l2.s.x));

        double x = (l2.yIntercept - l1.yIntercept) / (l1.grad - l2.grad);
        return Point(x, l1.getValue(x));
    }

    double getValue(double x) const {  // regard a line as a linear function
        return grad * x + yIntercept;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Point<ll> p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    cin >> p3.x >> p3.y >> p4.x >> p4.y;

    Line l1(p1, p2), l2(p3, p4);

    bool isIntersect = l1.isIntersect(l2);
    cout << isIntersect << '\n';

    if (isIntersect) {
        Point intersection = l1.getIntersection(l2);
        if (isfinite(intersection.x) and isfinite(intersection.y)) {
            cout << fixed;
            cout.precision(15);
            cout << intersection.x << ' ' << intersection.y;
        }
    }
}