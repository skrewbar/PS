#include <bits/stdc++.h>
#include <cmath>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

struct Point {
    ll x, y;

    auto operator<=>(const Point& p) const = default;

    ll dist(const Point& p) const {
        ll dx = x - p.x, dy = y - p.y;
        return dx * dx + dy * dy;
    }

    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    ll crossProduct(const Point& p) const { return x * p.y - y * p.x; }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2 - p1).crossProduct(p3 - p1);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> points(N);
    for (auto& [x, y] : points)
        cin >> x >> y;

    swap(points.front(), *ranges::min_element(points));
    const Point p0 = points.front();
    sort(points.begin() + 1, points.end(),
         [&](const Point& p1, const Point& p2) {
             int ccw = getCCW(p0, p1, p2);

             if (ccw == 0)
                 return p0.dist(p1) < p0.dist(p2);

             return ccw > 0;
         });

    vector<Point> hull;
    for (Point p : points) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    double length = 0;
    int hullSize = hull.size();
    hull.push_back(hull.front());
    for (int i = 0; i < hullSize; i++)
        length += sqrt(hull[i].dist(hull[i + 1]));

    cout << fixed;
    cout.precision(2);
    cout << length;

    return 0;
}