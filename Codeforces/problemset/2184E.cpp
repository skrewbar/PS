#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int a[101010];
ll answer[101010];

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    auto dnc = [&](int l, int r, auto&& dnc) {
        if (l >= r)
            return;

        int m = (l + r) / 2;

        ll lo = m, hi = m;
        int k = n;
        while (lo != l or hi != r) {
            while (lo > l and abs(a[lo] - a[lo - 1]) >= k)
                lo--;
            while (hi < r and abs(a[hi + 1] - a[hi]) >= k)
                hi++;
            
            int nxtK = 0;
            if (lo > l)
                nxtK = max(nxtK, abs(a[lo] - a[lo - 1]));
            if (hi < r)
                nxtK = max(nxtK, abs(a[hi + 1] - a[hi]));

            ll cases = (m - lo + 1) * (hi - m + 1) - 1;
            answer[nxtK + 1] += cases;
            answer[k + 1] -= cases;
            k = nxtK;
        }

        dnc(l, m - 1, dnc);
        dnc(m + 1, r, dnc);
    };

    fill(answer, answer + n, 0);
    dnc(1, n, dnc);

    for (int k = 1; k <= n - 1; k++) {
        answer[k] += answer[k - 1];
        cout << answer[k] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}