#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;
using ll = long long;

int N;
ll M;
ll P[202020];

pair<ll, ll> buyUntil(ll limit) {
    ll cost = 0;
    ll cnt = 0;

    for (int i = 1; i <= N; i++) {
        ll k = (limit + P[i]) / (2 * P[i]);

        if (k != 0 and k > M / P[i] / k) return {M + 1, 0};

        cost += k * k * P[i];
        cnt += k;

        if (cost > M) return {M + 1, 0};
    }

    for (int i = 1; i <= N; i++) {
        ll k = (limit + 1 + P[i]) / (2 * P[i]);

        if (2*k - 1 > M / P[i]) continue;
        ll c = (2*k - 1) * P[i];

        if (c != limit + 1) continue;
        if (cost + c > M) continue;

        cost += c;
        cnt++;
    }

    return {cost, cnt};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> P[i];

    ll lo = 1, hi = M + 1;
    while (lo < hi) {
        ll m = (lo + hi) / 2;

        if (buyUntil(m).first <= M) lo = m + 1;
        else hi = m;
    }

    cout << buyUntil(lo - 1).second;

    return 0;
}
