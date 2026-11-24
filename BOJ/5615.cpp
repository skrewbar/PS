#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

ll power(ull base, ll exp, ll mod) {
    ull ret = 1;
    while (exp) {
        if (exp & 1)
            ret = ret * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return ret;
}

bool millerRabinTest(ll n, int a) {
    for (ll k = n - 1;; k >>= 1) {
        ll res = power(a, k, n);
        if (k & 1)
            return res == 1 or res == n - 1;
        if (res == n - 1)
            return true;
    }
}

bool isPrime(ll n) {
    for (int a : {2, 3, 5, 7, 11}) {
        if (n == a)
            return true;
        if (not millerRabinTest(n, a))
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int answer = 0;
    while (n--) {
        ll s;
        cin >> s;
        answer += isPrime(s << 1 | 1);
    }
    cout << answer;
}