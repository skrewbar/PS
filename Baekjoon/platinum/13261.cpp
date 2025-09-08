#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

ll DP[808][8080], C[8080];

ll getRisk(int l, int r) {
    return (C[r] - C[l - 1]) * (r - l + 1);
}

void find(int cnt, int s, int e, int l, int r) {
    if (s > e)
        return;

    int m = (s + e) >> 1;
    int opt = l;

    DP[cnt][m] = DP[cnt - 1][opt - 1] + getRisk(opt, m);
    for (int i = opt + 1; i <= r; i++) {
        if (DP[cnt - 1][i - 1] + getRisk(i, m) < DP[cnt][m]) {
            DP[cnt][m] = DP[cnt - 1][i - 1] + getRisk(i, m);
            opt = i;
        }
    }

    find(cnt, s, m - 1, l, opt);
    find(cnt, m + 1, e, opt, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, G;
    cin >> L >> G;

    for (int i = 1; i <= L; i++) {
        cin >> C[i];
        C[i] += C[i - 1];
        DP[1][i] = getRisk(1, i);
    }

    for (int cnt = 2; cnt <= G; cnt++)
        find(cnt, 1, L, 1, L);

    cout << DP[G][L];
    return 0;
}