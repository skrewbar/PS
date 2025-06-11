#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

ll square(ll x) {
    return x * x;
}

struct Point {
    ll x, y;

    auto operator<=>(const Point& p) const = default;

    int ccw(const Point& p1, const Point& p2) const {
        ll crossProduct = (p1.x - x) * (p2.y - y) - (p1.y - y) * (p2.x - x);

        if (crossProduct > 0)
            return 1;
        if (crossProduct < 0)
            return -1;
        return 0;
    }

    ll squaredDist(const Point& p) const {
        return square(x - p.x) + square(y - p.y);
    }
};

struct Vector {
    ll x, y;

    Vector(const Point& p1, const Point& p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

    int ccw(const Vector& v) {
        ll crossProduct = x * v.y - y * v.x;

        if (crossProduct > 0)
            return 1;
        if (crossProduct < 0)
            return -1;
        return 0;
    }
};

vector<Point> points;

bool angleCompare(const Point& p1, const Point& p2) {
    const Point& p = points.front();

    int ccw = p.ccw(p1, p2);
    if (ccw == 0)
        return p.squaredDist(p1) < p.squaredDist(p2);

    return ccw > 0;
}

struct Answer {
    Point p1, p2;
    ll dist;

    Answer(const Point& p1, const Point& p2)
        : p1(p1), p2(p2), dist(p1.squaredDist(p2)) {}

    bool operator<(const Answer& a) const { return dist < a.dist; }
};

void solve() {
    int n;
    cin >> n;

    points = vector<Point>(n);
    for (auto& [x, y] : points)
        cin >> x >> y;

    swap(points.front(), *ranges::min_element(points));
    sort(points.begin() + 1, points.end(), angleCompare);

    vector<Point> hull;
    hull.reserve(n + 1);
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 and
               hull[hull.size() - 2].ccw(hull.back(), points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    int hullSize = hull.size();
    hull.push_back(hull.front());
    Answer answer(hull[0], hull[1]);
    for (int i = 0, j = 0; i < hullSize; i++) {
        Vector v1(hull[i], hull[i + 1]), v2(hull[j], hull[j + 1]);

        while (j + 1 < hullSize and v1.ccw(v2) >= 0) {
            answer = max(answer, Answer(hull[i], hull[j]));
            j++; 
            v2 = Vector(hull[j], hull[j + 1]);
        }

        answer = max(answer, Answer(hull[i], hull[j]));
    }

    cout << answer.p1.x << ' ' << answer.p1.y << ' ' << answer.p2.x << ' '
         << answer.p2.y << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}