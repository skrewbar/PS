#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

ll power(ll base, ll exp) {
    ll ret = 1;

    while (exp) {
        if (exp & 1) ret = ret * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }

    return ret;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a.begin() + 1, a.end());

    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (a[n - i] == a[n - i + 1]) break;

        ans += power(a[n - i + 1] - 1, i);
        ans %= MOD;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
