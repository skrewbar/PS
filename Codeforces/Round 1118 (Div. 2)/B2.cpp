#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int power(int base, int exp) {
    int ret = 1;
    while (exp--) ret *= base;
    return ret;
}

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

    vector<ll> ans(m + 1);
    for (int t = 1; t <= m; t++) {
        ll s = 0;
        int k = 1;

        for (int j = 1; j <= m / t; j++) {
            s += cntSum[j * t];

            if (j == power(2, k) - 1) {
                ll c = s;
                if (t * power(2, k) <= m) c += cnt[t * power(2, k)];
                ans[k] = max(ans[k], c);

                k++;
            }
        }

        ans[k] = max(ans[k], s);
    }

    for (int k = 1; k <= m; k++)
        cout << (ans[k] = max(ans[k - 1], ans[k])) << ' ';

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
