#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

enum Verdict {
    NOT_INTERSECT = 0,
    ONE_END_INTERSECT = 1,
    ONE_MIDDLE_INTERSECT = 2,
    INF_INTERSECT = 3
};

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

struct Line {
    Point s, e;

    Line() = default;
    Line(const Point& start, const Point& end) : s(start), e(end) {
        if (s > e)
            swap(s, e);
    }

    bool operator==(const Line& l) const { return s == l.s and e == l.e; }

    Verdict isIntersect(const Line& l) {
        int ccw1 = getCCW(s, e, l.s) * getCCW(s, e, l.e),
            ccw2 = getCCW(l.s, l.e, s) * getCCW(l.s, l.e, e);

        if (ccw1 == 0 and ccw2 == 0) {
            if (s <= l.e and l.s <= e) {
                if (e == l.s or l.e == s)
                    return ONE_END_INTERSECT;

                if ((e.y - s.y) * (l.e.x - l.s.x) ==
                    (l.e.y - l.s.y) * (e.x - s.x))
                    return INF_INTERSECT;

                return ONE_END_INTERSECT;
            } else
                return NOT_INTERSECT;
        }

        if (ccw1 <= 0 and ccw2 <= 0) {
            if (ccw1 == 0 or ccw2 == 0)
                return ONE_END_INTERSECT;
            return ONE_MIDDLE_INTERSECT;
        }
        return NOT_INTERSECT;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Line> lines(n);
    for (int i = 0; i < n; i++) {
        Point s, e;
        cin >> s.x >> s.y >> e.x >> e.y;
        lines[i] = Line(s, e);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << lines[i].isIntersect(lines[j]);
        }
        cout << '\n';
    }
}