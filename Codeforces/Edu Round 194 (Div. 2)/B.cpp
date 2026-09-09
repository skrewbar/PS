#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll x, y, k;
    cin >> x >> y >> k;

    ll ans = 0;

    int i = 0;
    while (x <= y - x and i < k) {
        ans += y % x;
        x++, y++, i++;
    }

    ans += (k - i) * (y % x);
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
