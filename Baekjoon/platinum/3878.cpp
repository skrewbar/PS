#include <bits/stdc++.h>
#include <algorithm>

#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int square(int x) {
    return x * x;
}

struct Point {
    int x, y;

    int squaredDist(const Point& p) const {
        return square(x - p.x) + square(y - p.y);
    }

    bool operator<(const Point& p) const {
        if (x != p.x)
            return x < p.x;
        return y < p.y;
    }
    bool operator<=(const Point& p) const {
        if (x != p.x)
            return x <= p.x;
        return y <= p.y;
    }
};

int ccw(const Point& p1, const Point& p2, const Point& p3) {
    int product = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if (product > 0)
        return 1;
    else if (product < 0)
        return -1;
    return 0;
}

struct Line {
    Point start, end;
    Line(const Point& p1, const Point& p2) : start(p1), end(p2) {
        if (end <= start)
            swap(start, end);
    }

    bool isIntersect(const Line& l) {
        const Point &p1 = start, &p2 = end, &p3 = l.start, &p4 = l.end;

        int ccw1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
        int ccw2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

        if (ccw1 == 0 and ccw2 == 0)
            return p1 <= p4 and p3 <= p2;
        return ccw1 <= 0 and ccw2 <= 0;
    }
};

struct ConvexHull {
    vector<Point> hull;
    ConvexHull(vector<Point>& points) {
        swap(points.front(), *min_element(points.begin(), points.end()));
        auto angleCompare = [&](const Point& p1, const Point& p2) {
            int prod = ccw(points.front(), p1, p2);

            if (prod == 0)
                return points.front().squaredDist(p1) <
                       points.front().squaredDist(p2);

            return prod > 0;
        };
        sort(points.begin() + 1, points.end(), angleCompare);

        hull.reserve(points.size());
        for (int i = 0; i < (int)points.size(); i++) {
            while (hull.size() >= 2 and
                   ccw(*next(hull.rbegin(), 1), hull.back(), points[i]) <= 0)
                hull.pop_back();
            hull.push_back(points[i]);
        }
    }

    bool contains(const Point& p) {
        int n = hull.size();
        for (int i = 0; i < n; i++)
            if (ccw(hull[i], hull[(i + 1) % n], p) < 0)
                return false;
        return true;
    }

    bool isIntersect(const ConvexHull& ch) {
        int n = hull.size();
        int m = ch.hull.size();

        for (int i = 0; i < n; i++) {
            Line l1(hull[i], hull[(i + 1) % n]);
            for (int j = 0; j < m; j++) {
                Line l2(ch.hull[j], ch.hull[(j + 1) % m]);
                if (l1.isIntersect(l2))
                    return true;
            }
        }
        return false;
    }

    bool isIntersect(const Line& l) {
        int n = hull.size();
        for (int i = 0; i < n; i++)
            if (Line(hull[i], hull[(i + 1) % n]).isIntersect(l))
                return true;
        return false;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Point> blackPoints(n);
    vector<Point> whitePoints(m);

    for (int i = 0; i < n; i++)
        cin >> blackPoints[i].x >> blackPoints[i].y;
    for (int i = 0; i < m; i++)
        cin >> whitePoints[i].x >> whitePoints[i].y;

    while (blackPoints.size() < 3)
        blackPoints.push_back(blackPoints.back());
    while (whitePoints.size() < 3)
        whitePoints.push_back(whitePoints.back());

    ConvexHull blackHull(blackPoints);
    ConvexHull whiteHull(whitePoints);

    bool seperable = true;

    if (blackHull.isIntersect(whiteHull))
        seperable = false;
    if (n >= 3 and blackHull.contains(whiteHull.hull[0]))
        seperable = false;
    if (m >= 3 and whiteHull.contains(blackHull.hull[0]))
        seperable = false;

    cout << (seperable ? "YES" : "NO") << '\n';
    return;
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