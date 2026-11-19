#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int MAX_a = 1e6;

int spf[1010101];

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<int>> factors(n + 1);
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        int prod = 1;

        int j = a[i];
        while (spf[j] > 1) {
            if (not factors[i].empty() and factors[i].back() == spf[j]) {
                prod /= spf[j];
                factors[i].pop_back();
            } else {
                prod *= spf[j];
                factors[i].push_back(spf[j]);
            }

            j /= spf[j];
        }

        cnt[prod]++;
    }

    ll ans = 0;
    set<int> cum = {};
    for (int i = 1; i <= n; i++) {
        for (int factor : factors[i]) {
            if (cum.contains(factor)) cum.erase(factor);
            else cum.insert(factor);
        }

        int prod = 1;
        for (int factor : cum) {
            if (prod > MAX_a / factor) {
                prod = MAX_a + 1;
                break;
            }

            prod *= factor;
        }

        ans += cnt[prod];
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    iota(spf, spf + MAX_a + 1, 0);
    for (int i = 2; i <= MAX_a / i; i++) {
        if (spf[i] != i) continue;

        for (int j = i * i; j <= MAX_a; j += i) {
            if (spf[j] == j)
                spf[j] = i;
        }
    }

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
