#include <bits/stdc++.h>
using namespace std;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

using ll = long long;

void solve() {
    int n;
    ll x;
    cin >> n >> x;

    vector<int> m(n + 1);
    vector<vector<ll>> a(n + 1), b(n + 1);

    MinHeap<tuple<ll, ll, int, int>> pq;

    auto pushNext = [&](int i, int j) {
        ll cost = 0, profit = 0;
        for (j++; j <= m[i]; j++) {
            profit -= a[i][j];
            if (profit < 0) {
                cost -= profit;
                profit = 0;
            }
            profit += b[i][j];

            if (cost < profit) {
                pq.emplace(cost, profit, i, j);
                return;
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        cin >> m[i];

        a[i].resize(m[i] + 1);
        for (int j = 1; j <= m[i]; j++) cin >> a[i][j];

        b[i].resize(m[i] + 1);
        for (int j = 1; j <= m[i]; j++) cin >> b[i][j];

        pushNext(i, 0);
    }

    vector<int> floor(n + 1);
    while (not pq.empty()) {
        auto [cost, profit, i, j] = pq.top();
        pq.pop();

        if (x < cost) break;
        x += profit - cost;
        floor[i] = j;

        pushNext(i, j);
    }

    pair<int, int> ans = {floor[1], 1};
    for (int i = 1; i <= n; i++) {
        if (ans.first < floor[i]) ans = {floor[i], i};

        ll cost = 0;
        for (int j = floor[i] + 1; j <= m[i]; j++) {
            cost += a[i][j];
            if (cost > x) break;
            if (ans.first < j) ans = {j, i};
            cost -= b[i][j];
        }
    }

    cout << ans.first << ' ' << ans.second << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
