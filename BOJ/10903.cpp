#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

struct Point {
    ll x, y;

    ll squaredDist(const Point& p) const {
        ll dx = x - p.x;
        ll dy = y - p.y;
        return dx * dx + dy * dy;
    }

    auto operator<=>(const Point& p) const = default;

    double abs() const { return sqrt(x * x + y * y); }
    ll dot(const Point& p) const { return x * p.x + y * p.y; }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};
int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;

    vector<Point> points(N);
    for (auto& [x, y] : points)
        cin >> x >> y;

    swap(points.front(), *ranges::min_element(points));
    sort(points.begin() + 1, points.end(),
         [&points](const Point& p1, const Point& p2) {
             int ccw = getCCW(points.front(), p1, p2);

             if (ccw == 0)
                 return points.front().squaredDist(p1) <
                        points.front().squaredDist(p2);

             return ccw > 0;
         });

    vector<Point> hull;
    for (const Point& p : points) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    double ans = 0;
    for (int i = 0; i < hull.size(); i++)
        ans += (hull[i] - hull[(i + 1) % hull.size()]).abs();
    ans += 2 * acos(-1) * R;

    println("{:.10f}", ans);

    return 0;
}