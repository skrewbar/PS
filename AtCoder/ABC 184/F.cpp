#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

using ll = long long;

ll A[44];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll T;
    cin >> N >> T;

    for (int i = 0; i < N; i++) cin >> A[i];

    vector<ll> v;
    for (int b = 0; b < 1 << 20; b++) {
        ll sum = 0;

        for (int i = 0; i < 20; i++) {
            if (b & (1 << i)) sum += A[i];
        }

        v.push_back(sum);
    }

    ll answer = 0;
    sort(all(v));
    for (int b = 0; b < 1 << 20; b++) {
        ll sum = 0;

        for (int i = 0; i < 20; i++) {
            if (b & (1 << i)) sum += A[i + 20];
        }

        if (sum > T) continue;

        auto it = upper_bound(all(v), T - sum) - 1;
        answer = max(answer, sum + *it);
    }

    cout << answer;

    return 0;
}
