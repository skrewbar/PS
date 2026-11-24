#include <bits/stdc++.h>
using namespace std;

class Point {
public:
    int x, y;
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}

    int ccw(const Point &p2, const Point &p3) const {
        const Point &p1 = *this;
        int cross_product = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
        if (cross_product > 0) return 1;
        if (cross_product < 0) return -1;
        return 0;
    }

    int squared_dist(const Point &p) const {
        auto square = [](int x) { return x * x; };
        return square(p.x - x) + square(p.y - y);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p;
    cin >> p;
    while (p--) {
        int n;
        cin >> n;

        vector<Point> points(n);
        for (auto &[x, y] : points) {
            cin >> x >> y;
        }

        swap(points[0], *min_element(points.begin(), points.end(),
            [](const Point &p1, const Point &p2) {
                if (p1.y != p2.y) return p1.y > p2.y;
                return p1.x < p2.x;
            })
        );

        sort(points.begin()+1, points.end(),
            [&points](const Point &p1, const Point &p2) {
                int ccw = points[0].ccw(p1, p2);

                if (ccw == 0) return points[0].squared_dist(p1) < points[0].squared_dist(p2);
                return ccw < 0;
            }
        );

        stack<Point> convex_hull;
        for (const Point &p : points) {
            while (convex_hull.size() >= 2) {
                const Point &p2 = convex_hull.top();
                convex_hull.pop();
                const Point &p1 = convex_hull.top();

                if (p1.ccw(p2, p) < 0) {
                    convex_hull.push(p2);
                    break;
                }
            }
            convex_hull.push(p);
        }

        cout << convex_hull.size() << '\n';
        stack<Point> reversed_hull;
        while (not convex_hull.empty()) {
            reversed_hull.push(convex_hull.top());
            convex_hull.pop();
        }
        
        convex_hull.swap(reversed_hull);
        while (not convex_hull.empty()) {
            const Point &p = convex_hull.top();
            cout << p.x << ' ' << p.y << '\n';
            convex_hull.pop();
        }
    }
}