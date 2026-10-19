#include <bits/stdc++.h>
using namespace std;

void solve(int n, int d) {
    int lastPos = -2*d;
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        if (abs(x - lastPos) > d) {
            ans++;
            lastPos = x + d;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n, d;
        cin >> n >> d;

        if (n == 0 and d == 0) break;

        solve(n, d);
    }

    return 0;
}
