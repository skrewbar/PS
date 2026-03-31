#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;

// returns whether h can be represented as
// the sum of a subset of odd numbers in the range [1, 2n - 1]
bool canRepresentWithOdds(ll n, ll h) {
    return h >= 0 and h <= n * n and h != 2 and h != n * n - 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, h;
    cin >> n >> h;

    if (h < 2 * n - 1 or h > n * n) {
        print("impossible");
        return 0;
    }

    vector<ll> stk, rest;

    if (not canRepresentWithOdds(n - 1, h - (2 * n - 1))) {
        if (not canRepresentWithOdds(n - 1, h - 1)) {
            print("impossible");
            return 0;
        }

        print("{} ", 2 * n - 1);
        h--;
    } else {
        stk.push_back(2 * n - 1);
        h -= 2 * n - 1;
    }

    for (ll i = n - 1; i > 0; i--) {
        if (canRepresentWithOdds(i - 1, h - (2 * i - 1))) {
            h -= 2 * i - 1;
            stk.push_back(2 * i - 1);
        } else {
            rest.push_back(2 * i - 1);
        }
    }

    if (h != 0) {
        print("impossible");
        return 0;
    }

    while (not stk.empty()) {
        print("{} ", stk.back());
        stk.pop_back();
    }

    for (ll i : rest)
        print("{} ", i);

    return 0;
}