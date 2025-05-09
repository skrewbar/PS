#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll l;
    int n, k;
    cin >> l >> n >> k;

    queue<pair<ll, ll>> q;
    set<ll> visited;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        q.push(pair{a, 0});
        visited.insert(a);
    }

    while (k--) {
        auto [now, darkness] = q.front();
        q.pop();
        cout << darkness << '\n';

        for (ll next = now-1; next <= now+1; next++) {
            if (0 <= next and next <= l and not visited.contains(next)) {
                q.push(pair{next, darkness + 1});
                visited.insert(next);
            }
        }
    }
}