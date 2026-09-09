#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int s, e;
    cin >> s;

    int easy = 0;
    for (int i = 2; i <= n - 1; i++) {
        int a;
        cin >> a;

        if (a == 0) easy++;
    }

    cin >> e;

    int swapCnt = (s == 1) + (e == 1);
    if (easy < swapCnt) {
        cout << -1 << '\n';
    } else {
        cout << swapCnt << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
