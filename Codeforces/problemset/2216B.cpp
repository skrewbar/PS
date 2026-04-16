#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll t, h, u;
    cin >> t >> h >> u;
    
    ll ans = 0;

    ll cnt = min(t, u);
    t -= cnt, u -= cnt;
    ans += cnt * 4;

    cnt = min(t / 2, h);
    t -= cnt * 2, h -= cnt;
    ans += cnt * 7;

    if (t > 0 and h > 0) {
        --t, --h;
        ans += 5;
    }

    if (t)
        ans += 2*t + 1;
    ans += h * 3;
    ans += u * 3;

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}