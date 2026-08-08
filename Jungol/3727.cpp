#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Point {
    ll x, y;
};

int getCCW(const Point &p1, const Point &p2, const Point &p3) {
    ll product = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);

    if (product > 0) return 1;
    if (product < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> points(N);
    for (auto &[x, y] : points) cin >> x >> y;

    int ans = 1;
    for (int i = 0; i < N; i++) {
        vector<Point> sorted = points;
        swap(sorted[0], sorted[i]);

        const Point &p0 = sorted[0];
        for (int j = N - 1; j >= 0; j--) {
            sorted[j].x -= p0.x;
            sorted[j].y -= p0.y;

            if (sorted[j].y < 0) sorted[j] = {-sorted[j].x, -sorted[j].y};
        }

        sort(sorted.begin() + 1, sorted.end(),
             [&](const Point &p1, const Point &p2) {
                 return getCCW(p0, p1, p2) > 0;
             });

        int cnt = 1;
        for (int j = 1; j < N; j++) {
            if (getCCW(p0, sorted[j - 1], sorted[j]) != 0) cnt = 1;
            cnt++;

            ans = max(ans, cnt);
        }
    }

    cout << ans;

    return 0;
}
