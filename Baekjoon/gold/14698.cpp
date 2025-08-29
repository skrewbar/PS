#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

void solve() {
    ll answer = 1;

    MinHeap<ll> energies;
    int N;
    cin >> N;
    while (N--) {
        ll energy;
        cin >> energy;
        energies.emplace(energy);
    }

    while (energies.size() >= 2) {
        ll e1 = energies.top();
        energies.pop();
        ll e2 = energies.top();
        energies.pop();

        answer *= (e1 * e2) % MOD;
        answer %= MOD;
        energies.emplace(e1 * e2);
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}