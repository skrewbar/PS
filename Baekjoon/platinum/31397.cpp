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

    ll getOuterProduct(const Point& p) const { return x * p.y - y * p.x; }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

ll getArea(const vector<Point>& points) {
    ll ret = 0;

    for (int i = 1; i + 1 < points.size(); i++)
        ret += points[i].getOuterProduct(points[i + 1]);

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}