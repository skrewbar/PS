#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

struct Point {
    int x, y;

    bool operator<(const Point &p) { return tie(x, y) < tie(p.x, p.y); }

    int cross(const Point &p) const { return x * p.y - y * p.x; }

    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }

    int dist(const Point &p) const {
        int dx = x - p.x;
        int dy = y - p.y;

        return dx * dx + dy * dy;
    }
};

int getCCW(const Point &p1, const Point &p2, const Point &p3) {
    int cross = (p2 - p1).cross(p3 - p1);

    if (cross > 0) return 1;
    if (cross < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> points(N);
    for (auto &[x, y] : points) cin >> x >> y;

    sort(all(points));

    const Point &p0 = points.front();
    sort(points.begin() + 1, points.end(),
         [&](const Point &p1, const Point &p2) {
             int ccw = getCCW(p0, p1, p2);

             if (ccw == 0) return p0.dist(p1) < p0.dist(p2);

             return ccw > 0;
         });

    vector<Point> hull;
    for (const Point& p : points) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    int area = 0;
    for (int i = 1; i + 1 < hull.size(); i++)
        area += (hull[i] - p0).cross(hull[i + 1] - p0);

    cout << area / 2;

    if (area & 1)
        cout << ".5";

    return 0;
}
