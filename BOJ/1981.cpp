#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

const int delta[] = {1, -1, 0, 0};

int n;
int arr[111][111];

bool canPass(int lo, int hi) {
    if (arr[1][1] < lo or arr[1][1] > hi)
        return false;

    vector<vector<bool>> visited(n + 1, vector(n + 1, false));
    queue<pair<int, int>> q;

    visited[1][1] = true;
    q.emplace(1, 1);

    while (not q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == n and c == n)
            return true;

        for (int k = 0; k < 4; k++) {
            int nr = r + delta[k], nc = c + delta[3 - k];

            if (nr <= 0 or nr > n or nc <= 0 or nc > n)
                continue;
            if (arr[nr][nc] < lo or arr[nr][nc] > hi)
                continue;
            if (visited[nr][nc])
                continue;

            visited[nr][nc] = true;
            q.emplace(nr, nc);
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    int minValue = INT_MAX, maxValue = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];

            minValue = min(minValue, arr[i][j]);
            maxValue = max(maxValue, arr[i][j]);
        }
    }

    int lo, hi;
    lo = hi = minValue;
    int ans = INT_MAX;
    while (lo <= hi and hi <= maxValue) {
        if (canPass(lo, hi)) {
            ans = min(ans, hi - lo);
            lo++;
        } else {
            hi++;
        }
    }

    cout << ans;

    return 0;
}