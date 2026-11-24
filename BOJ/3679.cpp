#include <bits/stdc++.h>
using namespace std;

class Point {
public:
    int x, y, idx;
    Point(int x, int y, int idx) : x(x), y(y), idx(idx) {}
    Point() = default;

    int squared_dist(const Point &p) const {
        auto square = [](int x) {return x * x;};
        return square(x - p.x) + square(y - p.y);
    }

    int ccw(const Point &p2, const Point &p3) const {
        const Point &p1 = *this;
        int p = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);

        if (p > 0) return 1;
        if (p < 0) return -1;
        return 0;
    }

    bool operator<(const Point &p) {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;

        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
            points[i].idx = i;
        }

        swap(points[0], *min_element(points.begin(), points.end()));
        sort(points.begin()+1, points.end(),
            [&points](const Point &p1, const Point &p2) {
                int p = points[0].ccw(p1, p2);

                if (p == 0) {
                    return points[0].squared_dist(p1) < points[0].squared_dist(p2);
                }
                return p < 0;
            }
        );

        auto iter = points.end()-2;
        auto last = points.end()-1;
        while (points[0].ccw(*last, *iter) == 0) iter--;
        reverse(iter+1, points.end());
        for (Point p : points) cout << p.idx << ' ';
        cout << '\n';
    }
}