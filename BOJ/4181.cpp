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
        ll dx = p.x - x;
        ll dy = p.y - y;
        return dx * dx + dy * dy;
    }
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

    int n;
    cin >> n;
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        Point p;
        char c;
        cin >> p.x >> p.y >> c;
        if (c == 'Y')
            points.push_back(p);
    }
    swap(points.front(), *min_element(points.begin(), points.end()));
    const Point& p0 = points[0];
    sort(points.begin() + 1, points.end(),
         [&](const Point& p1, const Point& p2) {
             int ccw = getCCW(p0, p1, p2);

             if (ccw == 0)
                 return p0.dist(p1) < p0.dist(p2);
             return ccw > 0;
         });

    int i = (int)points.size() - 1;
    while (getCCW(p0, points[i], points[i - 1]) == 0)
        i--;
    reverse(points.begin() + i, points.end());

    print("{}\n", points.size());
    for (const Point& p : points)
        print("{} {}\n", p.x, p.y);

    return 0;
}