#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

struct Fraction {
    ll numer, denom;

    Fraction(ll _numer, ll _denom) : numer(_numer), denom(_denom) { reduce(); }

    void reduce() {
        if (denom < 0) {
            numer = -numer;
            denom = -denom;
        }

        bool negative = numer < 0;

        if (negative)
            numer = -numer;

        ll g = gcd(numer, denom);
        numer /= g, denom /= g;

        if (negative)
            numer = -numer;
    }
};

struct Point {
    ll x, y;

    bool operator<(const Point& p) const {
        return y < p.y or (y == p.y and x > p.x);
    }

    ll dist(const Point& p) const {
        ll dx = x - p.x, dy = y - p.y;
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

    int N, M, k;
    cin >> N >> M >> k;

    vector<Point> points(N);
    for (auto& [x, y] : points)
        cin >> x >> y;

    swap(points.front(), *min_element(points.begin(), points.end()));

    const Point& p0 = points.front();
    sort(points.begin() + 1, points.end(),
         [&p0](const Point& p1, const Point& p2) {
             int ccw = getCCW(p0, p1, p2);

             if (ccw == 0)
                 return p0.dist(p1) < p0.dist(p2);

             return ccw > 0;
         });

    vector<Point> hull;
    for (const Point& p : points) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    int i = 0;
    while (i + 1 < (int)hull.size() and getCCW(Point(0, 0), hull[i], hull[i + 1]) <= 0)
        i++;
    while (i + 1 < (int)hull.size() and getCCW(Point(0, 0), hull[i], hull[i + 1]) >= 0)
        i++;

    for (int x = 1; x <= M; x++) {
        const Point p(-k * x, k * x);
        while (i - 1 >= 0 and getCCW(p, hull[i], hull[i - 1]) >= 0)
            i--;

        Fraction ans(hull[i].y - p.y, hull[i].x - p.x);

        if (ans.numer == 0)
            cout << "0/0\n";
        else
            cout << ans.numer << '/' << ans.denom << '\n';
    }

    return 0;
}