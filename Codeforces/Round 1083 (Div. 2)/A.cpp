#include <bits/stdc++.h>
using namespace std;

int p[555];

void solve() {
    int n;
    cin >> n;

    int nIdx = 0;

    for (int i = 1; i <= n; i++) {
        cin >> p[i];

        if (p[i] == n) nIdx = i;
    }

    int mIdx = 0;
    for (int i = 1; i <= n; i++) {
        if (p[mIdx] < p[i]) mIdx = i;

        if (p[mIdx] == i) {
            swap(p[mIdx], p[nIdx]);
            break;
        }
    }

    for (int i = 1; i <= n; i++) cout << p[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
