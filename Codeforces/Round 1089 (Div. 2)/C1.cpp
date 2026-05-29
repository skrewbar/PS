#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }

    return a;
}

ll a[202020], b[202020];

void solve() {
    int n;
    cin >> n;

    a[0] = a[n + 1] = 1;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        ll lg = gcd(a[i - 1], a[i]);
        ll rg = gcd(a[i], a[i + 1]);

        if (a[i] > lg*rg / gcd(lg, rg))
            answer++;
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
