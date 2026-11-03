#include <bits/stdc++.h>
using namespace std;

int prior[14];

void solve(int n) {
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;

        if (prior[c] > prior[ans]) ans = c;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    prior[2] = 13;
    prior[1] = 12;
    prior[13] = 11;
    prior[12] = 10;
    prior[11] = 9;
    for (int i = 10; i > 2; i--) prior[i] = i - 2;

    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;
        solve(n);
    }

    return 0;
}
