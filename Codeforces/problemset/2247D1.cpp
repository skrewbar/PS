#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> sorted(a);
    sort(all(sorted));

    vector<int> nextPos(n);
    iota(all(nextPos), 0);

    if (a == sorted) {
        cout << 0 << '\n';
        return;
    }

    int k = 1;
    for (int i = 0; i < n; i++) {
        int lb = lower_bound(all(sorted), a[i]) - sorted.begin();
        lb = nextPos[lb]++;

        while (i / (2 * k) != lb / (2 * k)) k <<= 1;
    }

    cout << k << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
