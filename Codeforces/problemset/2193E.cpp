#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

constexpr int INF = 1e9;

int cnt[303030];

void solve() {
    int n;
    cin >> n;
    fill(cnt, cnt + n + 1, INF);

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        cnt[a] = 1;
    }
    
    for (ll i = 1; i <= n; i++) {
        if (cnt[i] != INF) {
            cout << cnt[i] << ' ';
            continue;
        }

        for (ll j = 2; j*j <= i; j++) {
            if (i % j != 0)
                continue;
            
            minimize(cnt[i], cnt[i / j] + cnt[j]);
        }
        
        cout << (cnt[i] == INF ? -1 : cnt[i]) << ' ';
    }
    cout << '\n';
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