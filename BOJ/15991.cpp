#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int MOD = 1e9 + 9;

constexpr int MAX_HALF = 100'000 >> 1;

int cases[50505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cases[0] = cases[1] = 1;
    cases[2] = cases[0] + cases[1];
    cases[3] = cases[0] + cases[1] + cases[2];
    for (int i = 4; i <= MAX_HALF; i++)
        cases[i] = ((cases[i - 1] + cases[i - 2]) % MOD + cases[i - 3]) % MOD;

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        if (n & 1) {
            if (n == 1)
                cout << 1 << '\n';
            else
                cout << (cases[(n - 1) >> 1] + cases[(n - 3) >> 1]) % MOD << '\n';
        } else
            cout << (cases[n >> 1] + cases[(n - 2) >> 1]) % MOD << '\n';
    }

    return 0;
}