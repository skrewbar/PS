#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> v;

void solve() {
    ll x;
    cin >> x;

    int lb = lower_bound(v.begin(), v.end(), x) - v.begin();

    ll ans = LLONG_MAX;
    ans = min(ans, abs(x - v[lb]));

    if (lb - 1 >= 0) ans = min(ans, abs(x - v[lb - 1]));

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i <= 60; i++) {
        for (int j = 0; j <= 60; j++) {
            v.push_back((1LL << i) + (1LL << j));
        }
    }
    sort(v.begin(), v.end());

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}

