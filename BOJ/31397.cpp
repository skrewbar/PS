#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ldouble = long double;

struct Point {
    ldouble x, y;

    ldouble getOuterProduct(const Point& p) const { return x * p.y - y * p.x; }
    ldouble getDist(const Point& p) const {
        ldouble dx = x - p.x;
        ldouble dy = y - p.y;

        return sqrtl(dx * dx + dy * dy);
    }

    Point sub(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    void addLen(ldouble len, const Point direction) {
        ldouble hypotenus = sqrtl(direction.x*direction.x + direction.y*direction.y);
        ldouble cosine = direction.x / hypotenus;
        ldouble sine = direction.y / hypotenus;

        x += cosine * len;
        y += sine * len;
    }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    ldouble product =
        (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

ldouble getArea(const vector<Point>& points) {
    ldouble ret = 0;

    for (int i = 1; i + 1 < points.size(); i++)
        ret += (points[i].sub(points[0])).getOuterProduct(points[i + 1].sub(points[0]));

    return ret / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> polygon(N);
    for (auto& p : polygon)
        cin >> p.x >> p.y;

    ldouble area = getArea(polygon);
    ldouble perimeter = 0;
    for (int i = 0; i < N; i++)
        perimeter += polygon[i].getDist(polygon[(i + 1) % N]);

    auto getAreaOfHalfPiece = [&](ldouble len) {
        vector<Point> piece;
        int i = 0;

        while (len - polygon[i].getDist(polygon[(i + 1) % N]) > 0) {
            len -= polygon[i].getDist(polygon[(i + 1) % N]);
            i = (i + 1) % N;
        }
        Point pivot = polygon[i];
        pivot.addLen(len, polygon[(i + 1) % N].sub(polygon[i]));
        piece.push_back(pivot);

        len += perimeter / 2;
        while (len - polygon[i].getDist(polygon[(i + 1) % N]) > 0) {
            len -= polygon[i].getDist(polygon[(i + 1) % N]);
            i = (i + 1) % N;
            piece.push_back(polygon[i]);
        }
        Point antipode = polygon[i];
        antipode.addLen(len, polygon[(i + 1) % N].sub(polygon[i]));
        piece.push_back(antipode);

        return getArea(piece);
    };

    bool increasing = getAreaOfHalfPiece(0) < area / 2;
    ldouble lo = 0, hi = perimeter / 2;

    for (int epochs = 0; epochs < 100; epochs++) {
        ldouble mid = (lo + hi) / 2;
        ldouble halfArea = getAreaOfHalfPiece(mid);

        if ((increasing and halfArea < area / 2) or
            (not increasing and halfArea > area / 2))
            lo = mid;
        else
            hi = mid;
    }

    println("YES");

    int i = 0;
    ldouble len = lo;
    while (len - polygon[i].getDist(polygon[(i + 1) % N]) > 0) {
        len -= polygon[i].getDist(polygon[(i + 1) % N]);
        i = (i + 1) % N;
    }
    println("{} {}", i + 1, len / (polygon[i].getDist(polygon[(i + 1) % N])));

    len += perimeter / 2;
    while (len - polygon[i].getDist(polygon[(i + 1) % N]) > 0) {
        len -= polygon[i].getDist(polygon[(i + 1) % N]);
        i = (i + 1) % N;
    }
    println("{} {}", i + 1, len / (polygon[i].getDist(polygon[(i + 1) % N])));

    return 0;
}