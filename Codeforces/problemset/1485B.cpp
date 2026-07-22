#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int a[101010], cnt[101010];

int rangeSum(int l, int r) {
    if (l > r) return 0;
    return cnt[r] - cnt[l - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, k;
    cin >> n >> q >> k;

    for (int i = 1; i <= n; i++) cin >> a[i];
    a[n + 1] = k + 1;

    for (int i = 1; i <= n; i++) {
        cnt[i] = a[i + 1] - a[i - 1] - 2;
        cnt[i] += cnt[i - 1];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        if (l == r) cout << k - 1 << '\n';
        else
            cout << (a[l + 1] - 2) + (k - a[r - 1] - 1) + rangeSum(l + 1, r - 1)
                 << '\n';
    }

    return 0;
}
