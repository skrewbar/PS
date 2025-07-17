#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

#define index first
#define value second

using namespace std;

using ll = long long;

int dungeon[1010][1010], maxExp[1010][1010];

int n;
ll r;

ll getTotalExp(int k) {
    for (int i = 1; i <= n; i++) {
        deque<pair<int, int>> dq;
        for (int j = 1; j < k; j++) {
            while (not dq.empty() and dq.front().index < j - k + 1)
                dq.pop_front();

            while (not dq.empty() and dq.back().value < dungeon[i][j])
                dq.pop_back();
            dq.emplace_back(j, dungeon[i][j]);
        }
        for (int j = k; j <= n; j++) {
            while (not dq.empty() and dq.front().index < j - k + 1)
                dq.pop_front();

            while (not dq.empty() and dq.back().value < dungeon[i][j])
                dq.pop_back();
            dq.emplace_back(j, dungeon[i][j]);

            maxExp[i][j - k + 1] = dq.front().value;
        }
        for (int j = n + 1; j < n + k; j++) {
            while (not dq.empty() and dq.front().index < j - k + 1)
                dq.pop_front();

            maxExp[i][j - k + 1] = dq.front().value;
        }
    }

    ll totalExp = 0;
    for (int j = 1; j <= n; j++) {
        deque<pair<int, int>> dq;
        for (int i = 1; i < k; i++) {
            while (not dq.empty() and dq.front().index < i - k + 1)
                dq.pop_front();

            while (not dq.empty() and dq.back().value < maxExp[i][j])
                dq.pop_back();
            dq.emplace_back(i, maxExp[i][j]);
        }
        for (int i = k; i <= n; i++) {
            while (not dq.empty() and dq.front().index < i - k + 1)
                dq.pop_front();

            while (not dq.empty() and dq.back().value < maxExp[i][j])
                dq.pop_back();
            dq.emplace_back(i, maxExp[i][j]);

            totalExp += dq.front().value;
        }
        for (int i = n + 1; i < n + k; i++) {
            while (not dq.empty() and dq.front().index < i - k + 1)
                dq.pop_front();

            totalExp += dq.front().value;
        }
    }

    return totalExp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> dungeon[i][j];

    int lo = 1, hi = n + 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (getTotalExp(mid) < r)
            lo = mid + 1;
        else
            hi = mid;
    }
    print("{}\n", lo == n + 1 ? -1 : lo);

    return 0;
}