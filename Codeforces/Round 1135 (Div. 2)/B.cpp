#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    ll cnt[2] = {};
    for (int i = 0; i < n; i++) { cnt[s[i] - '0']++; }

    if (cnt[0] > cnt[1]) swap(cnt[0], cnt[1]);
    ll toggle = min(cnt[0], k);
    cnt[0] -= toggle;
    cnt[1] += toggle;

    cout << cnt[0] * (cnt[0] + 1) / 2 + cnt[1] * (cnt[1] + 1) / 2 + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
