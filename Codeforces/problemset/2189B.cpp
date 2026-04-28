#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a[101010], b[101010], c[101010];

ll jump(int i) {
    return a[i] * b[i] - c[i];
}

void solve() {
    ll n, x;
    cin >> n >> x;

    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i] >> c[i];

    ll pos = 0;
    for (int i = 1; i <= n; i++) {
        pos += (b[i] - 1) * a[i];
        if (pos >= x) {
            cout << 0 << '\n';
            return;
        }
    }

    int best = 1;
    for (int i = 2; i <= n; i++) {
        if (jump(best) < jump(i))
            best = i;
    }

    if (jump(best) <= 0) {
        cout << -1 << '\n';
        return;
    }

    ll j = jump(best);
    cout << ((x - pos) + j - 1) / j << '\n';
    return;
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