#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Point {
    ll x, y;

    ll dist(const Point &p) const {
        ll dx = x - p.x;
        ll dy = y - p.y;

        return dx * dx + dy * dy;
    }

    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }

    ll cross(const Point &p) const { return x * p.y - y * p.x; }
};
int getCCW(const Point &p1, const Point &p2, const Point &p3) {
    ll product = (p2 - p1).cross(p3 - p1);

    if (product > 0) return 1;
    if (product < 0) return -1;
    return 0;
}

Point points[505050];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        auto &[x, y] = points[i];
        cin >> x >> y;
    }

    sort(points + 1, points + N + 1,
         [&](auto a, auto b) { return tie(a.x, a.y) < tie(b.x, b.y); });
    sort(points + 2, points + N + 1, [&](auto a, auto b) {
        auto p = points[1];

        int ccw = getCCW(p, a, b);
        if (ccw == 0) return p.dist(a) < p.dist(b);
        return ccw > 0;
    });

    vector<Point> hull;
    for (int i = 1; i <= N; i++) {
        auto p = points[i];

        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    ll ans = 0;
    for (int i = 0, j = 0; i + 1 < hull.size(); i++) {
        while (j + 1 < hull.size() and getCCW({0, 0}, hull[i + 1] - hull[i],
                                              hull[j + 1] - hull[j]) >= 0)
            ans = max(ans, hull[i].dist(hull[j++]));
        ans = max(ans, hull[i].dist(hull[j]));
    }

    cout << ans;

    return 0;
}
