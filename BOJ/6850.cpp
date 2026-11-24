#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct Vector {
    int x, y;

    auto operator<=>(const Vector& v) const = default;

    int dist(const Vector& p) const {
        int dx = x - p.x, dy = y - p.y;
        return dx * dx + dy * dy;
    }

    Vector operator-(const Vector& v) const { return Vector(x - v.x, y - v.y); }
    int crossProduct(const Vector& v) const { return x * v.y - y * v.x; }
};

int getCCW(const Vector& v1, const Vector& v2, const Vector& v3) {
    int product = (v2 - v1).crossProduct(v3 - v1);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Vector> trees(n);
    for (auto& [x, y] : trees)
        cin >> x >> y;
    swap(trees.front(), *ranges::min_element(trees));
    const Vector v0 = trees.front();
    sort(trees.begin() + 1, trees.end(),
         [&](const Vector& v1, const Vector& v2) {
             int ccw = getCCW(v0, v1, v2);

             if (ccw == 0)
                 return v0.dist(v1) < v0.dist(v2);
             return ccw > 0;
         });

    vector<Vector> hull;
    for (const Vector& v : trees) {
        while (hull.size() >= 2 and
               getCCW(hull[hull.size() - 2], hull.back(), v) <= 0)
            hull.pop_back();
        hull.push_back(v);
    }

    int hullSize = hull.size();
    int area = 0;
    for (int i = 1; i + 1 < hullSize; i++)
        area += (hull[i] - hull[0]).crossProduct(hull[i + 1] - hull[0]);

    cout << area / 100;
    return 0;
}