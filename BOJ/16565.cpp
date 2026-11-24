#include <bits/stdc++.h>
using namespace std;


int pow(int base, int exp, int MOD) {
    int ret = 1;
    while (exp) {
        if (exp & 1) ret = ret * base % MOD;
        exp >>= 1;
        base = base * base % MOD;
    }
    return ret;
}

// MOD must be an prime number
int combination(int n, int r, int MOD) {
    int nemerator = 1;
    for (int i = n; i > n-r; i--) {
        nemerator *= i;
        nemerator %= MOD;
    }

    int denominator = 1;
    for (int i = r; i > 0; i--) {
        denominator *= i;
        denominator %= MOD;
    }
    return nemerator * pow(denominator, MOD-2, MOD) % MOD;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int ans = 0;
    int MOD = 10007;

    for (int i = 1; 4*i <= n; i++) {
        ans += (i & 1 ? 1 : -1) * combination(13, i, MOD) * combination(52 - 4 * i, n - 4 * i, MOD);
        ans = ((ans % MOD) + MOD) % MOD;
    }
    cout << ans;
}