#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int LIMIT = 2e5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> b(n + 2);
    for (int i = 1; i <= n; i++) cin >> b[i];

    ll M = b[1];
    ll D = max(0LL, b[1] - b[n]);
    for (int i = 2; i <= n; i++) {
        M = max(M, b[i]);
        D += max(0LL, b[i] - b[i - 1]);
    }

    ll m = max(M, D);
    cout << m << '\n';
    if (m > LIMIT) return 0;

    queue<int> entry;
    vector<pair<int, int>> ans = {{0, 0}};
    for (int i = 1; i <= n + 1; i++) {
        if (b[i] > b[i - 1]) {
            for (int j = 0; j < b[i] - b[i - 1]; j++) entry.push(i);
        } else {
            for (int j = 0; j < b[i - 1] - b[i]; j++) {
                int f = entry.front();
                entry.pop();

                ans.emplace_back(f, i - 1);
            }
        }
    }

    int L = ans.size() - 1;
    int k = min({b[1], b[n], L - M});

    for (int i = k; i >= 1; i--) {
        ans[i].first = ans.back().first;
        ans.pop_back();
    }

    for (int i = 1; i <= L - k; i++) {
        auto [s, t] = ans[i];
        cout << s << ' ' << t << '\n';
    }

    return 0;
}
