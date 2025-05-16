#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mmul(ll a, ll b, ll mod) {
    ll ret = 0;
    a %= mod;
    while (b) {
        if (b & 1) ret = (ret + a) % mod;

        a = (a << 1) % mod;
        b >>= 1;
    }
    return ret;
}

ll pow(ll base, ll exp) {
    ll ret = 1;
    while (exp) {
        if (exp & 1)
            ret *= base;
        base *= base;
        exp >>= 1;
    }
    return ret;
}
ll pow(ll base, ll exp, ll mod) {
    ll ret = 1;
    while (exp) {
        if (exp & 1)
            ret = mmul(ret, base, mod);
        base = mmul(base, base, mod);
        exp >>= 1;
    }
    return ret;
}

ll gcd(ll a, ll b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// returns whether n seems to be prime number
bool millerRabinTest(ll n, ll a) {
    ll k = n - 1;

    for (;; k >>= 1) {
        ll r = pow(a, k, n);
        if (k & 1)
            return r == 1 or r == n - 1;
        if (r == n - 1)
            return true;
    }
}

ll testNums[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool isPrime(ll n) {
    for (ll a : testNums) {
        if (n == a)
            return true;
        if (n % a == 0)
            return false;
        if (not millerRabinTest(n, a))
            return false;
    }
    return true;
}

ll getFactor(ll n) {
    auto g = [n](ll x) -> ll { return (mmul(x, x, n) + 1) % n; };

    ll x = 2, y = 2, d = 1;
    while (d == 1) {
        x = g(x), y = g(g(y));
        d = gcd(abs(x - y), n);
    }
    return d;
}

// build up (prime, count) pairs
void factorize(ll n, map<ll, ll>& primeCnt) {
    if (~n & 1)
        primeCnt.emplace(2, 0);
    while (~n & 1) {
        n >>= 1;
        primeCnt[2]++;
    }

    if (n == 1)
        return;

    if (isPrime(n)) {
        primeCnt.emplace(n, 0);
        primeCnt[n]++;
        return;
    }

    ll factor = getFactor(n);
    if (factor == n) {
        for (ll i = 3; n != 1; i++) {
            if (n % i == 0)
                primeCnt.emplace(i, 0);
            for (; n % i == 0; n /= i) {
                primeCnt[i]++;
            }
        }
        return;
    }

    factorize(factor, primeCnt);
    factorize(n / factor, primeCnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<ll, ll> primeCnt;
    ll n;
    cin >> n;

    factorize(n, primeCnt);

    ll answer = 1;
    for (auto [prime, cnt] : primeCnt) {
        answer *= pow(prime, cnt) - pow(prime, cnt - 1);
    }

    cout << answer;
}