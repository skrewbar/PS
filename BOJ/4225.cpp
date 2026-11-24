#include <bits/stdc++.h>
using namespace std;

int pow(int base, int exp) {
    int ret = 1;
    while (exp) {
        if (exp & 1)
            ret *= base;
        base *= base;
        exp >>= 1;
    }
    return ret;
}

class Point {
   public:
    int x, y;

    Point() = default;
    Point(int x, int y) : x(x), y(y) {}

    int ccw(const Point& p2, const Point& p3) const {
        const Point& p1 = *this;

        int product =
            (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);

        if (product > 0)
            return 1;
        else if (product < 0)
            return -1;
        return 0;
    }

    int squaredDistance(const Point& p) const {
        return pow(p.x - x, 2) + pow(p.y - y, 2);
    }

    bool operator<(const Point& p) const {
        if (y != p.y)
            return y < p.y;
        else
            return x < p.x;
    }

    bool operator==(const Point& p) const { return x == p.x and y == p.y; }
};

class Vector {
   public:
    int x, y;

    Vector() = default;
    Vector(const Point& p1, const Point& p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

    int operator*(const Vector& v) { return v.x * y - v.y * x; }

    double magnitude() { return sqrt(x * x + y * y); }
};

vector<Point> trash;

bool ccwCompare(const Point& p1, const Point& p2) {
    int ccw = trash[0].ccw(p1, p2);

    if (ccw == 0)
        return trash[0].squaredDistance(p1) < trash[0].squaredDistance(p2);

    return ccw > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(2);
    cout << fixed;

    for (int caseNum = 1;; caseNum++) {
        int n;
        cin >> n;

        if (n == 0)
            break;

        trash = vector<Point>(n);
        for (auto& [x, y] : trash) {
            cin >> x >> y;
        }

        sort(trash.begin(), trash.end());
        sort(trash.begin() + 1, trash.end(), ccwCompare);

        vector<Point> convexHull(trash.begin(), trash.begin() + 2);
        for (int i = 2; i < n; i++) {
            while (convexHull.size() >= 2) {
                const Point a = *(convexHull.end() - 2), b = convexHull.back();

                if (a.ccw(b, trash[i]) > 0)
                    break;
                convexHull.pop_back();
            }
            convexHull.push_back(trash[i]);
        }

        convexHull.push_back(convexHull.front());
        double answer = 1e9;
        for (int i = 0; i + 1 < convexHull.size(); i++) {
            double maxBreadth = 0;
            const Point &p1 = convexHull[i], &p2 = convexHull[i + 1];
            Vector v(p1, p2);

            for (Point p : convexHull) {
                if (p == p1 or p == p2)
                    continue;

                maxBreadth = max(maxBreadth, v * Vector(p, p1) / v.magnitude());
            }
            answer = min(answer, maxBreadth);
        }

        cout << format("Case {}: ", caseNum) << ceil(answer * 100) / 100
             << '\n';
    }
}