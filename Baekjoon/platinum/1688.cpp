#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

constexpr ll INF = 1e9;

struct Point {
    ll x, y;

    auto operator<=>(const Point& p) const = default;
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ll product = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

Point shield[10101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
        cin >> shield[i].x >> shield[i].y;
    shield[N] = shield[0];

    auto isProtected = [&](const Point& p) -> bool {
        for (int i = 0; i < N; i++) {
            const Point &p1 = shield[i], p2 = shield[i + 1];

            if (getCCW(p1, p2, p) == 0 and
                (min(p1.x, p2.x) <= p.x and p.x <= max(p1.x, p2.x)) and
                (min(p1.y, p2.y) <= p.y and p.y <= max(p1.y, p2.y)))
                return true;
        }

        int intersectCnt = 0;

        for (int i = 0; i < N; i++) {
            Point p1 = shield[i], p2 = shield[i + 1];
            if (p1.y > p2.y)
                swap(p1, p2);

            if ((p1.y <= p.y and p.y < p2.y) and
                (p2.x - p1.x) * (p.y - p1.y) > (p.x - p1.x) * (p2.y - p1.y))
                intersectCnt++;
        }

        return intersectCnt % 2 == 1;
    };

    for (int i = 0; i < 3; i++) {
        Point p;
        cin >> p.x >> p.y;

        println("{}", isProtected(p) ? 1 : 0);
    }

    return 0;
}