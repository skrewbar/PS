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

    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }

    ll getCrossProduct(const Point& p) const { return x * p.y - y * p.x; }

    ll squaredDist(const Point& p) const {
        ll dx = x - p.x;
        ll dy = y - p.y;

        return dx * dx + dy * dy;
    }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2 - p1).getCrossProduct(p3 - p1);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

Point A[1010], B[1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++)
        cin >> A[i].x >> A[i].y;
    for (int i = 0; i < M; i++)
        cin >> B[i].x >> B[i].y;

    vector<Point> minkowski;
    minkowski.reserve(N * M);
    for (int i = 0; i < N; i++) {
        const Point& p1 = A[i];
        for (int j = 0; j < M; j++) {
            const Point& p2 = B[j];

            minkowski.emplace_back(p1.x + p2.x, p1.y + p2.y);
        }
    }

    sort(minkowski.begin(), minkowski.end());
    minkowski.erase(unique(minkowski.begin(), minkowski.end()),
                    minkowski.end());

    sort(minkowski.begin() + 1, minkowski.end(),
         [&](const Point& p1, const Point& p2) {
             static const Point& p0 = minkowski.front();

             int ccw = getCCW(p0, p1, p2);
             if (ccw == 0)
                 return p0.squaredDist(p1) < p0.squaredDist(p2);
             return ccw > 0;
         });

    vector<Point> hull;
    hull.reserve(minkowski.size());

    for (auto& p : minkowski) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    println("{}", hull.size());
    for (auto& [x, y] : hull)
        println("{} {}", x, y);

    return 0;
}