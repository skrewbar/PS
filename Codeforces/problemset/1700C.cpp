#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a[202020];

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];

    ll ans = 0;
    for (int i = 2; i <= n; i++) {
        ll diff = a[i] - a[i - 1];

        ans += abs(diff);

        if (diff < 0) a[1] += diff;
    }

    ans += abs(a[1]);

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
