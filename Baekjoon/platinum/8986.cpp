#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll pos[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if (N == 1) {
        cout << 0;
        return 0;
    }

    for (int i = 0; i < N; i++)
        cin >> pos[i];

    auto getCost = [N](ll x) -> ll {
        ll ret = 0;
        for (int i = 0; i < N; i++)
            ret += abs(i*x - pos[i]);
        return ret;
    };

    ll lo = 1, hi = pos[N - 1];
    while (lo + 2 < hi) {
        int m = (lo + hi) / 2;
        
        if (getCost(m) > getCost(m + 1))
            lo = m;
        else
            hi = m + 1;
    }

    ll ans = LLONG_MAX;
    for (int i = lo; i <= hi; i++)
        ans = min(ans, getCost(i));

    cout << ans;

    return 0;
}