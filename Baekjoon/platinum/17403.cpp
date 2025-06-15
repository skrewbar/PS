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
    int index;

    bool operator<(const Point& p) const {
        if (x != p.x)
            return x < p.x;
        return y < p.y;
    }

    ll dist(const Point& p) const {
        ll dx = x - p.x, dy = y - p.y;
        return dx * dx + dy * dy;
    }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

vector<int> answer;
int floorNum;

bool popConvexHull(vector<Point>& points) {
    swap(points.front(), *min_element(points.begin(), points.end()));

    const Point p0 = points.front();
    auto angleCompare = [&](const Point& p1, const Point& p2) {
        int ccw = getCCW(p0, p1, p2);

        if (ccw == 0)
            return p0.dist(p1) < p0.dist(p2);

        return ccw > 0;
    };

    sort(points.begin() + 1, points.end(), angleCompare);

    vector<Point> remainder, hull;
    for (int i = 0; i < (int)points.size(); i++) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
            remainder.push_back(hull.back());
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    swap(points, remainder);
    if (hull.size() < 3)
        return false;
    for (Point p : hull) {
        answer[p.index] = floorNum;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        auto& [x, y, index] = points[i];
        index = i;
        cin >> x >> y;
    }

    answer = vector<int>(n);
    floorNum = 1;
    while (points.size() >= 3 and popConvexHull(points))
        floorNum++;

    for (int i = 0; i < n; i++)
        cout << answer[i] << ' ';

    return 0;
}