#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int MOD = 1e9 + 7;

int a[1010101], pos[1010101];
vector<int> valuesOfPos[1010101], cntPrefSum[1010101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> lis;
    for (int i = 0; i < N; i++) {
        cin >> a[i];

        pos[i] = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
        if (pos[i] == lis.size())
            lis.push_back(a[i]);
        else
            lis[pos[i]] = a[i];
    }

    fill(cntPrefSum, cntPrefSum + N, vector<int>(1));
    for (int i = N - 1; i >= 0; i--) {
        int len = pos[i];

        if (len == lis.size() - 1) {
            cntPrefSum[len].push_back((cntPrefSum[len].back() + 1) % MOD);
        } else {
            int upper = upper_bound(valuesOfPos[len + 1].begin(),
                                    valuesOfPos[len + 1].end(), a[i]) -
                        valuesOfPos[len + 1].begin();
            int cnt = (cntPrefSum[len + 1].back() - cntPrefSum[len + 1][upper]) % MOD;
            cntPrefSum[len].push_back((cntPrefSum[len].back() + cnt) % MOD);
        }
        valuesOfPos[len].push_back(a[i]);
    }

    cout << lis.size() << ' ' << (cntPrefSum[0].back() + MOD) % MOD << '\n';

    return 0;
}