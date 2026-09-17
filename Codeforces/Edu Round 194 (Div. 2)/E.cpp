#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;
    s = '#' + s;

    vector<vector<int>> cnt(n + 1, vector<int>(4));
    for (int i = 2; i <= n; i++) {
        int x = (s[i - 1] - '0') * 2 + s[i] - '0';
        cnt[i][x]++;

        for (int j = 0; j < 4; j++) cnt[i][j] += cnt[i - 1][j];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        vector<int> rngCnt(4);
        for (int j = 0; j < 4; j++) rngCnt[j] = cnt[r][j] - cnt[l][j];

        int x = (s[r] - '0') * 2 + s[l] - '0';
        rngCnt[x]++;

        int lo = 0, hi = 4*n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;

            if (rngCnt[0b01] + max(0, rngCnt[0b00] - mid) + max(0, rngCnt[0b11] - mid) <= mid) hi = mid;
            else lo = mid + 1;
        }

        cout << 4*lo - (r - l + 1) << '\n';
    }

    return 0;
}
