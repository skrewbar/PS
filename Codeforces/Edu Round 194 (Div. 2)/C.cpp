#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y;
    cin >> x >> y;

    int ans = 0;
    for (int i = 28; i >= 0; i--) {
        if (x & (1 << i)) {
            x -= 1 << i;
            y += 1 << i;
            ans += 1 << i;
        }
    }

    for (int i = 28; i >= 0; i--) {
        if (ans >= (1 << i) and y & (1 << i) and ~x & (1 << i)) {
            x += 1 << i;
            y -= 1 << i;
            ans -= 1 << i;
        }
    }

    cout << (x ^ y) << ' ' << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
