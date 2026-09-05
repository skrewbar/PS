#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), cnt(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    vector<int> cntSum(cnt);
    for (int i = m - 1; i >= 1; i--) cntSum[i] += cntSum[i + 1];

    int ans = 0;
    for (int l = 1; l <= m; l++) {
        int c = cntSum[l];
        if (2*l <= m) c += cnt[2*l];

        ans = max(ans, c);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
