#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;
map<pair<ll, ll>, int> dp = {{{0, 0}, 0}};

int getDP(ll left, ll right) {
    if (dp.contains(pair(left, right)))
        return dp[pair(left, right)];

    int ret = 0;
    for (int i = 1; i <= 40; i++) {
        ll start = (1LL << i) - 1, end = (1LL << (i + 1)) - 2;
        start = max(left, start), end = min(right, end);

        if (start <= end)
            ret = max(ret,
                      getDP(start - (1LL << i) + 1, end - (1LL << i) + 1) + i);
    }

    return dp[pair(left, right)] = ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll x, y;
        cin >> x >> y;
        cout << getDP(x, y) << '\n';
    }

    return 0;
}