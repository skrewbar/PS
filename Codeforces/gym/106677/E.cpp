#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

using ll = long long;

void solve(int n) {
    vector<vector<ll>> cost(n + 1);

    for (int i = 1; i <= n; i++) {
        ll a, b;
        cin >> a >> b;

        cost[b].push_back(a);
    }

    for (int i = 0; i <= n; i++) sort(all(cost[i]));

    int minGemIdx = -1;
    for (int i = 1; i <= n; i++) {
        if (cost[i].empty()) continue;

        if (minGemIdx == -1) minGemIdx = i;
        else if (cost[minGemIdx][0] > cost[i][0]) minGemIdx = i;
    }

    ll gemSum = minGemIdx == -1 ? 0 : 1;
    for (int i = 1; i <= n; i++) gemSum += (i - 1) * cost[i].size();

    multiset<ll> cart;

    for (int j = 0; j < (int)cost[0].size() - gemSum; j++)
        cart.insert(cost[0][j]);

    for (int i = 1; i <= n; i++) {
        for (int j = 0 + (minGemIdx == i); j < cost[i].size(); j++) {
            if (cart.empty()) break;

            if (*(--cart.end()) <= cost[i][j]) break;
            cart.erase(--cart.end());

            cart.insert(cost[i][j]);
        }
    }

    ll ans = 0;
    if (minGemIdx != -1) ans += cost[minGemIdx][0];

    for (ll x : cart) ans += x;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;

        if (n == 0) break;

        solve(n);
    }

    return 0;
}
