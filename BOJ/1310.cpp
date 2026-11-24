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
    auto operator<=>(const Point& p) const = default;

    ll dist(const Point& p) const {
        ll dx = p.x - x, dy = p.y - y;
        return dx * dx + dy * dy;
    }

    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

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

    vector<Point> pillars(N);
    for (auto& [x, y] : pillars)
        cin >> x >> y;
    swap(pillars.front(), *ranges::min_element(pillars));
    const Point p0 = pillars.front();
    sort(pillars.begin() + 1, pillars.end(),
         [&](const Point& p1, const Point& p2) {
             int ccw = getCCW(p0, p1, p2);

             if (ccw == 0)
                 return p0.dist(p1) < p0.dist(p2);
             return ccw > 0;
         });

    vector<Point> hull;
    for (Point p : pillars) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    int hullSize = hull.size();
    ASSERT(hullSize >= 2);
    ll dist = hull[0].dist(hull[1]);
    for (int i = 0, j = 0; i + 1 < hullSize; i++) {
        while (j + 1 < hullSize and getCCW(Point(0, 0), hull[i + 1] - hull[i],
                                           hull[j + 1] - hull[j]) >= 0)
            dist = max(dist, hull[i].dist(hull[j++]));
        dist = max(dist, hull[i].dist(hull[j]));
    }

    cout << dist;
    return 0;
}