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
        ll dx = x - p.x, dy = y - p.y;
        return dx * dx + dy * dy;
    }

    ll crossProduct(const Point& p) const { return x * p.y - y * p.x; }

    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2 - p1).crossProduct(p3 - p1);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

vector<Point> getConvexHull(vector<Point> points) {
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

    return hull;
}

bool isHullContainsPoint(const vector<Point>& hull, const Point& p) {
    if (hull.size() == 2) {
        auto [minX, maxX] = minmax(hull[0].x, hull[0].y);
        auto [minY, maxY] = minmax(hull[0].y, hull[1].y);

        return getCCW(hull[0], hull[1], p) == 0 and
               (minX <= p.x and p.x <= maxX) and (minY <= p.y and p.y <= maxY);
    }

    const Point& p0 = hull.front();

    int lo = 1, hi = hull.size() - 1;
    if (getCCW(p0, hull[1], p) < 0)
        return false;
    if (getCCW(p0, hull.back(), p) > 0)
        return false;

    while (lo < hi) {
        int mid = (lo + hi) >> 1;

        if (getCCW(p0, hull[mid], p) < 0)
            hi = mid;
        else
            lo = mid + 1;
    }

    const Point &p1 = hull[lo - 1], &p2 = hull[lo];
    return getCCW(p1, p2, p) >= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> A(N), B(N);
    for (auto& [x, y] : A)
        cin >> x >> y;
    for (auto& [x, y] : B)
        cin >> x >> y;

    vector<Point> AHull = getConvexHull(A), BHull = getConvexHull(B);

    int AScore = 0, BScore = 0;
    for (Point p : B)
        if (isHullContainsPoint(AHull, p))
            AScore++;
    for (Point p : A)
        if (isHullContainsPoint(BHull, p))
            BScore++;

    cout << AScore << ' ' << BScore;
    return 0;
}