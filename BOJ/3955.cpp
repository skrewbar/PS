#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll getInverse(ll a, ll mod) {
    ll r0 = a, r1 = mod;
    ll s0 = 1, s1 = 0;
    ll t0 = 0, t1 = 1;

    while (r1 != 0) {
        ll q = r0 / r1;

        ll temp = t1;
        t1 = t0 - t1 * q;
        t0 = temp;

        temp = s1;
        s1 = s0 - s1 * q;
        s0 = temp;

        temp = r1;
        r1 = r0 % r1;
        r0 = temp;
    }

    return s0;
}

constexpr ll INF = 1e9;

void solve() {
    ll K, C;
    cin >> K >> C;

    if (K == 1) {
        println("{}", C != 1 ? 1 : 2);
        return;
    }
    if (C == 1) {
        if (K + 1 > INF)
            println("IMPOSSIBLE");
        else
            println("{}", K + 1);
        return;
    }

    ll ans = (getInverse(C, K) % K + K) % K;

    if (gcd(K, C) != 1 or ans > INF)
        println("IMPOSSIBLE");
    else
        println("{}", ans);
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