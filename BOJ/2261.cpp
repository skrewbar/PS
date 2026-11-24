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

    ll dist(const Point& p) { return square(x - p.x) + square(y - p.y); }
};
bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}
bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

vector<Point> points;

ll getMinDist(int lo, int hi) {
    if (hi - lo + 1 <= 3) {
        ll minDist = LLONG_MAX;
        for (int i = lo; i <= hi; i++)
            for (int j = i + 1; j <= hi; j++)
                minDist = min(minDist, points[i].dist(points[j]));
        return minDist;
    }

    int mid = (lo + hi) / 2;
    ll minDist = min(getMinDist(lo, mid), getMinDist(mid + 1, hi));

    ll midX = (points[mid].x + points[mid + 1].x + 1) / 2;
    vector<Point> midPoints;
    for (int i = lo; i <= hi; i++) {
        if (square(midX - points[i].x) <= minDist)
            midPoints.push_back(points[i]);
    }

    ranges::sort(midPoints, compareY);
    for (int i = 0; i < (int)midPoints.size(); i++) {
        for (int j = i + 1; j < (int)midPoints.size(); j++) {
            if (square(midPoints[i].y - midPoints[j].y) >= minDist)
                break;
            minDist = min(minDist, midPoints[i].dist(midPoints[j]));
        }
    }

    return minDist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    points = vector<Point>(n);
    for (auto& [x, y] : points)
        cin >> x >> y;
    ranges::sort(points, compareX);

    cout << getMinDist(0, n - 1);
}