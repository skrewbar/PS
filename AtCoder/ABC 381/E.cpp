#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int cnt[101010][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    string S;
    cin >> S;
    S = "#" + S;

    vector<int> slashes;

    for (int i = 1; i <= N; i++) {
        cnt[i][0] = cnt[i - 1][0];
        cnt[i][1] = cnt[i - 1][1];

        if (S[i] == '/') {
            slashes.push_back(i);
            continue;
        }

        int num = S[i] - '1';
        cnt[i][num] += 1;
    }

    for (int q = 0; q < Q; q++) {
        int L, R;
        cin >> L >> R;

        int l = lower_bound(all(slashes), L) - slashes.begin();
        int r = upper_bound(all(slashes), R) - slashes.begin() - 1;

        if (r < l) {
            cout << 0 << '\n';
            continue;
        }

        int lo = l, hi = r;
        while (lo < hi) {
            int m = (lo + hi) / 2;

            int i = slashes[m];

            if (cnt[i][0] - cnt[L - 1][0] < cnt[R][1] - cnt[i][1]) lo = m + 1;
            else hi = m;
        }

        int i = slashes[lo];
        int half = min(cnt[i][0] - cnt[L - 1][0], cnt[R][1] - cnt[i][1]);

        if (l <= lo - 1) {
            i = slashes[lo - 1];
            half = max(half, min(cnt[i][0] - cnt[L - 1][0], cnt[R][1] - cnt[i][1]));
        }

        cout << 2*half + 1 << '\n';
    }

    return 0;
}
