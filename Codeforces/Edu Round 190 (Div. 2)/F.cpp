#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

vector<int> childs[202020], maxDp3[202020];
int dp[202020], rangeEnd[202020];

int calc(int limit) {
    fill(dp, dp + limit + 1, 0);
    for (int i = 1; i <= limit; i++) maxDp3[i].clear();

    auto setupDp = [&](auto &&self, int cur) -> void {
        for (int child : childs[cur]) {
            if (child > limit) continue;

            self(self, child);
            maxDp3[cur].push_back(dp[child]);
        }

        sort(all(maxDp3[cur]), greater<>());
        maxDp3[cur].resize(3);

        dp[cur] = maxDp3[cur][1] + 1;
    };
    setupDp(setupDp, 1);

    int maxDp = 0;
    auto rerooting = [&](auto &&self, int cur) -> void {
        maxDp = max(maxDp, dp[cur]);

        for (int child : childs[cur]) {
            if (child > limit) continue;

            if (dp[child] != maxDp3[cur][2]) dp[cur] = maxDp3[cur][2] + 1;
            else dp[cur] = maxDp3[cur][1] + 1;

            maxDp3[child].push_back(dp[cur]);
            sort(all(maxDp3[child]), greater<>());
            maxDp3[child].resize(3);
            dp[child] = maxDp3[child][1] + 1;

            self(self, child);
        }
    };
    rerooting(rerooting, 1);

    return maxDp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    for (int i = 1; i <= q; i++) childs[i].clear();
    for (int v = 2; v <= q + 1; v++) {
        int p;
        cin >> p;

        childs[p].push_back(v);
    }

    int last = 2;
    for (int i = 1; i <= 17; i++) {
        int lo = last;
        int hi = q + 2;

        while (lo < hi) {
            int m = (lo + hi) / 2;

            if (calc(m) <= i) lo = m + 1;
            else hi = m;
        }

        for (int k = 0; k < (lo - last); k++) cout << i << ' ';
        last = lo;
    }

    return 0;
}
