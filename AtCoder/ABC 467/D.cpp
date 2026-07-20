#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define x first
#define y second

struct Fraction {
    ll numer, denom;

    Fraction(ll _n, ll _d) : numer(_n), denom(_d) {
        if (denom == 0) {
            numer = 1;
            return;
        }

        if (denom < 0) {
            numer = -numer;
            denom = -denom;
        }

        bool neg = false;
        if (numer < 0) {
            neg = true;
            numer = -numer;
        }

        ll g = gcd(numer, denom);

        numer /= g;
        denom /= g;

        if (neg) numer = -numer;
    }

    bool operator==(const Fraction& f) const {
        return numer == f.numer and denom == f.denom;
    }
};

const Fraction INF(1, 0);

Fraction getGrad(pair<ll, ll> p1, pair<ll, ll> p2) {
    ll numer = 2 * (p2.x - p1.x);
    ll denom = 2 * (p2.y - p1.y);

    return {numer, denom};
}

Fraction getYInter(pair<ll, ll> p1, pair<ll, ll> p2) {
    ll numer = -p1.x * p1.x - p1.y * p1.y + p2.x * p2.x + p2.y * p2.y;
    ll denom = 2 * (p2.y - p1.y);

    return {numer, denom};
}

void solve() {
    pair<ll, ll> P, Q, R, S;
    cin >> P.x >> P.y >> Q.x >> Q.y >> R.x >> R.y >> S.x >> S.y;

    if (getGrad(P, Q) == getGrad(R, S)) {
        if (getGrad(P, Q) == INF) {
            cout << (P.x + Q.x == R.x + S.x ? "Yes" : "No") << '\n';
            return;
        }

        cout << (getYInter(P, Q) == getYInter(R, S) ? "Yes" : "No") << '\n';
        return;
    }
    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
