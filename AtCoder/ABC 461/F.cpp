#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

using ll = long long;

constexpr ll MOD = 998244353;

ll factorial[22];
ll dpCnt[2][22][3030], dpSum[2][22][3030];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    factorial[1] = 1;
    for (int i = 2; i <= 14; i++) factorial[i] = factorial[i - 1] * i % MOD;

    ll N;
    cin >> N;

    vector<ll> factors;
    for (ll i = 1; i * i <= N; i++) {
        if (N % i != 0) continue;

        factors.push_back(i);
        if (i != N / i) factors.push_back(N / i);
    }
    factors.push_back(0); // padding
    sort(all(factors));

    dpCnt[0][0][1] = dpCnt[1][0][1] = 1;

    int factorCnt = factors.size() - 1;
    for (int i = 1; i <= factorCnt; i++) {
        for (int j = 1; j <= 14; j++) {
            for (int k = 1; k <= factorCnt; k++) {
                dpCnt[i & 1][j][k] = dpCnt[(i - 1) & 1][j][k];
                dpCnt[i & 1][j][k] %= MOD;

                dpSum[i & 1][j][k] = dpSum[(i - 1) & 1][j][k];
                dpSum[i & 1][j][k] %= MOD;

                if (factors[k] % factors[i] == 0) {
                    int l = lower_bound(all(factors), factors[k] / factors[i]) - factors.begin();

                    dpCnt[i & 1][j][k] += dpCnt[(i - 1) & 1][j - 1][l];
                    dpCnt[i & 1][j][k] %= MOD;

                    dpSum[i & 1][j][k] += dpSum[(i - 1) & 1][j - 1][l];
                    dpSum[i & 1][j][k] %= MOD;
                    dpSum[i & 1][j][k] += dpCnt[(i - 1) & 1][j - 1][l] * factors[i];
                    dpSum[i & 1][j][k] %= MOD;
                }
            }
        }
    }

    ll answer = 0;
    for (int j = 1; j <= 14; j++) {
        answer += dpSum[factorCnt & 1][j][factorCnt] * factorial[j] % MOD;
        answer %= MOD;
    }

    cout << answer;

    return 0;
}
