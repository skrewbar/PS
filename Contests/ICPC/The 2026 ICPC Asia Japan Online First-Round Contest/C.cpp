#include <bits/stdc++.h>
using namespace std;

void solve(int n) {
    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++) cin >> d[i];

    int ans = 0;
    for (int dep = 1000; dep >= 1; dep--) {
        int prv = -1;
        for (int i = 1; i <= n; i++) {
            if (prv < 0 and dep <= d[i]) continue;
            if (d[i] < dep) {
                if (prv > 0) ans += i - prv - 1;
                prv = i;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n;
        cin >> n;

        if (n == 0) break;

        solve(n);
    }

    return 0;
}
