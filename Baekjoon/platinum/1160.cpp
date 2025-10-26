#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;
using i128 = __int128;

vector<vector<i128>> mul(const vector<vector<i128>>& a,
                         const vector<vector<i128>>& b,
                         ll mod) {
    ASSERT(a[0].size() == b.size());

    vector<vector<i128>> ret(a.size(), vector<i128>(b[0].size()));

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                ret[i][j] += (a[i][k] * b[k][j]) % mod;
                ret[i][j] %= mod;
            }
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll m, a, c, X_0, n, g;
    cin >> m >> a >> c >> X_0 >> n >> g;

    vector<vector<i128>> base =
                             {
                                 {a, 1},
                                 {0, 1},
                             },
                         target = {
                             {X_0},
                             {c},
                         };

    while (n) {
        if (n & 1)
            target = mul(base, target, m);

        base = mul(base, base, m);
        n >>= 1;
    }

    cout << (ll)(target[0][0] % g);

    return 0;
}