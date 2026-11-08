#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

constexpr int OFFSET = 1010101;
vector<pair<int, int>> diag[2][2020202];

bool visitedXAxis[2][1010101], visitedYAxis[2][1010101];
pair<int, int> balls[101010];

void solve(int a, int b, int x, int y, int n) {
    fill(balls, balls + n + 1, pair(0, 0));

    auto visited = [&](int xi, int yi) -> bool& {
        if (xi == 0) return visitedYAxis[0][yi];
        if (xi == a) return visitedYAxis[1][yi];
        if (yi == 0) return visitedXAxis[0][xi];
        return visitedXAxis[1][xi];
    };
    visited(0, 0) = visited(0, b) = visited(a, 0) = visited(a, b) = true;
    vector<pair<int, int>> visitList = {{0, 0}, {0, b}, {a, 0}, {a, b}};

    for (int i = 1; i <= n; i++) {
        auto &[xi, yi] = balls[i];
        cin >> xi >> yi;
    }

    vector<pair<int, int>> pts(balls + 1, balls + n + 1);
    pts.emplace_back(x, y);
    sort(all(pts));
    for (auto [xi, yi] : pts) {
        diag[0][xi - yi + OFFSET].emplace_back(xi, yi);
        diag[1][xi + yi].emplace_back(xi, yi);
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        auto [xi, yi] = balls[i];

        int dx = 1, dy = 1;

        while (true) {
            int add = (dx + dy == 0);

            int diagId;
            if (add) diagId = xi + yi;
            else diagId = xi - yi + OFFSET;

            const auto &vec = diag[add][diagId];
            int lb = lower_bound(all(vec), pair(xi, yi)) - vec.begin();

            int counts[] = {lb, (int)vec.size() - lb};

            int selfDiag;
            if (add) selfDiag = balls[i].first + balls[i].second;
            else selfDiag = balls[i].first - balls[i].second + OFFSET;

            if (diagId == selfDiag) {
                if (tie(xi, yi) <= balls[i]) counts[1]--;
                else counts[0]--;
            }

            if (dx < 0) {
                lb--;
                if (lb > 0 and vec[lb] == balls[i]) lb--;
            } else if (lb < vec.size() and vec[lb] == balls[i]) lb++;

            if (0 <= lb and lb < vec.size() and vec[lb] == pair(x, y)) {
                ans.push_back(i);
                break;
            }

            int cnt = counts[dx > 0];
            if (cnt > 0) break;

            int slope = dy / dx;
            int xdest = (dx > 0 ? a : 0);
            int ydest = (dy > 0 ? b : 0);

            int ny = yi + (xdest - xi) * slope;
            if (ny < 0 or ny > b) {
                tie(xi, yi) = pair(xi + (ydest - yi) * slope, ydest);
                dy = -dy;
            } else {
                tie(xi, yi) = pair(xdest, ny);
                dx = -dx;
            }

            if (visited(xi, yi)) break;
            visited(xi, yi) = true;
            visitList.emplace_back(xi, yi);
        }
    }

    if (ans.empty()) {
        cout << "No\n";
    } else {
        for (int i : ans) cout << i << ' ';
        cout << '\n';
    }

    diag[0][x - y + OFFSET].clear();
    diag[1][x + y].clear();
    for (int i = 1; i <= n; i++) {
        auto [xi, yi] = balls[i];
        diag[0][xi - yi + OFFSET].clear();
        diag[1][xi + yi].clear();
    }
    for (auto [xi, yi] : visitList) visited(xi, yi) = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int a, b, x, y, n;
        cin >> a >> b >> x >> y >> n;

        if (a == 0) break;

        solve(a, b, x, y, n);
    }

    return 0;
}
