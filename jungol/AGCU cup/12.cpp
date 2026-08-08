#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;

    ll lo = 1, hi = 1e9;
    while (lo < hi) {
        ll m = (lo + hi) / 2;

        if (m * m + m <= 2 * K / N) lo = m + 1;
        else hi = m;
    }

    ll scar = lo * (lo - 1) / 2 * N;
    ll i = (K - scar) / lo;

    cout << min(N * lo + i, M) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    while (Q--) solve();

    return 0;
}