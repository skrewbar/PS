#include <bits/stdc++.h>
using namespace std;

void solve() {
    int c, h, o;
    cin >> c >> h >> o;

    if (h == 2*c - 4) cout << "Saturated\n";
    else cout << "Unsaturated\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
